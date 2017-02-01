// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Ranged.h"

void AWeapon_Ranged::Fire()
{
	Super::Fire();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = Instigator;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorLocation(), GetActorRotation(),SpawnParameters);
}


