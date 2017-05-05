// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Weapon_Melee.h"




AWeapon_Melee::AWeapon_Melee()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));	

}

void AWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->SetRelativeLocation(FVector::ZeroVector);
	CapsuleComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeleeWeaponOverlapBegin);

	TimeSinceLastFire = 0.f;
	RateOfFire = 1.3f;
	CollisionProfileName = CapsuleComponent->GetCollisionProfileName();
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	bCollisionEnabled = false;
}

void AWeapon_Melee::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AWeapon_Melee::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

bool AWeapon_Melee::Fire()
{
	if (Super::Fire())
	{
		return true;
	}
	return false;
}

bool AWeapon_Melee::Fire(AttackTypes::MeleeAttackType NewAttackType)
{
	if (Fire())
	{
		AttackType = NewAttackType;
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

bool AWeapon_Melee::AltFire(AttackTypes::MeleeAttackType NewAttackType)
{
	if (AltFire())
	{
		AttackType = NewAttackType;
		return true;
	}
	return false;
}

void AWeapon_Melee::SetAttackType(AttackTypes::MeleeAttackType NewAttackType)
{
	AttackType = NewAttackType;
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
		CapsuleComponent->SetCollisionProfileName(CollisionProfileName);
		UE_LOG(LogTemp, Display, TEXT("Collision profile: %s"), *CapsuleComponent->GetCollisionProfileName().ToString());
	}
	bCollisionEnabled = !bCollisionEnabled;
	//CapsuleComponent->ToggleActive();
}

void AWeapon_Melee::OnMeleeWeaponOverlapBegin(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	float DamageToDeal = DamagePerAttack;
	switch (AttackType)
	{
	case AttackTypes::NONE:
		break;
	case AttackTypes::SWIFT:
		break;
	case AttackTypes::LIGHT:
		break;
	case AttackTypes::HEAVY:
		UE_LOG(LogTemp, Display, TEXT("I AM HEAVY"));
		DamageToDeal *= 1.5f;
		break;
	default:
		break;
	}
	if (APawn* ReCastedOwningActor = Cast<APawn>(OwningActor))
	{
		if (bMultiTap)
		{
			UE_LOG(LogTemp, Display, TEXT("OverlappingAComponent %s"), *HitComponent->GetName());
			UGameplayStatics::ApplyDamage(OtherActor, DamageToDeal, ReCastedOwningActor->GetController(), OwningActor, TSubclassOf<UDamageType>());
		}
		else if (!bHasHit && !bMultiTap)
		{
			UE_LOG(LogTemp, Display, TEXT("OverlappingAComponent %s"), *HitComponent->GetName());
			UGameplayStatics::ApplyDamage(OtherActor, DamageToDeal, ReCastedOwningActor->GetController(), OwningActor, TSubclassOf<UDamageType>());
			bHasHit = true;
		}
	}
}


