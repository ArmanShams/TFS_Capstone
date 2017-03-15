// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Melee.h"




AWeapon_Melee::AWeapon_Melee()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));
	CapsuleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AWeapon_Melee::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastFire = 0.f;
	RateOfFire = 1.3f;
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

void AWeapon_Melee::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, DamagePerAttack, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
}

