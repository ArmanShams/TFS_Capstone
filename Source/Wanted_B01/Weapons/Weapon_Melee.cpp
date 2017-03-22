// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Melee.h"




AWeapon_Melee::AWeapon_Melee()
{
	RootComponent = MeshComponent;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));	

}

void AWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->SetRelativeLocation(FVector::ZeroVector);
	CapsuleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeleeWeaponOverlapBegin);

	TimeSinceLastFire = 0.f;
	RateOfFire = 1.3f;
	CollisionProfileString = CapsuleComponent->GetCollisionProfileName();
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));

	bCollisionEnabled = false;
}

void AWeapon_Melee::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

bool AWeapon_Melee::Fire()
{
	if (Super::Fire())
	{
		return true;
	}
	return false;
}

bool AWeapon_Melee::AltFire()
{
	if (Super::AltFire())
	{
		return true;
	}
	return false;
}

void AWeapon_Melee::ToggleCollider()
{
	if (bCollisionEnabled)
	{
		CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
		UE_LOG(LogTemp, Display, TEXT("Collision profile: %s"), *CapsuleComponent->GetCollisionProfileName().ToString());
		
	}
	else 
	{
		CapsuleComponent->SetCollisionProfileName(CollisionProfileString);
		UE_LOG(LogTemp, Display, TEXT("Collision profile: %s"), *CapsuleComponent->GetCollisionProfileName().ToString());
	}
	bCollisionEnabled = !bCollisionEnabled;
	//CapsuleComponent->ToggleActive();
}

void AWeapon_Melee::OnMeleeWeaponOverlapBegin(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bMultiTap)
	{
		UE_LOG(LogTemp, Display, TEXT("OverlappingAComponent %s"), *HitComponent->GetName());
		UGameplayStatics::ApplyDamage(OtherActor, DamagePerAttack, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
	}
	else if (!bHasHit && !bMultiTap)
	{
		UE_LOG(LogTemp, Display, TEXT("OverlappingAComponent %s"), *HitComponent->GetName());
		UGameplayStatics::ApplyDamage(OtherActor, DamagePerAttack, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
		bHasHit = true;
	}
	
}


