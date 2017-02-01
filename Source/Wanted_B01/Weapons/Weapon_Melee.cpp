// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Melee.h"

AWeapon_Melee::AWeapon_Melee()
{
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeleeWeaponOverlapBegin);
}

void AWeapon_Melee::Fire()
{
	Super::Fire();

}

void AWeapon_Melee::OnMeleeWeaponOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsSwinging && OtherActor != this && OtherActor != Instigator)
	{
		OnMeleeWeaponHit(OtherActor);
	}
}

void AWeapon_Melee::OnMeleeWeaponHit(AActor * HitActor)
{
	UGameplayStatics::ApplyDamage(HitActor, Damage, Instigator->GetController(), this, UDamageType::StaticClass());
}

