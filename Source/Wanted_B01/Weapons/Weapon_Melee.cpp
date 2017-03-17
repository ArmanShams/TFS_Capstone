// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Melee.h"




AWeapon_Melee::AWeapon_Melee()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColliderComponent"));
	CapsuleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeleeWeaponOverlapBegin);
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

void AWeapon_Melee::OnMeleeWeaponOverlapBegin(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, DamagePerAttack, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
}


