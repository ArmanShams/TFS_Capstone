// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemyMelee.h"

AEnemyMelee::AEnemyMelee()
{
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeleeWeaponOverlapBegin);

}


bool AEnemyMelee::Fire()
{
	return Super::Fire();
}

void AEnemyMelee::OnMeleeWeaponOverlapBegin(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsSwinging && OtherActor != this && OtherActor != Instigator)
	{
		OnMeleeWeaponHit(OtherActor);
	}
}

void AEnemyMelee::OnMeleeWeaponHit(AActor * HitActor)
{
	UGameplayStatics::ApplyDamage(HitActor, Damage, Instigator->GetController(), this, UDamageType::StaticClass());
}

