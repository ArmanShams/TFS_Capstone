// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Character/CharacterController.h"
#include "Weapons/Weapon_PlayerRevolver.h"
#include "UIWidget.h"


void UUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bCanEverTick = true;
	if (Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Player = Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	if (Player != NULL)
	{
		PlayerWeapon = Cast<AWeapon_Ranged>(Player->CurrentlyEquippedWeapon);
	}

}

void UUIWidget::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry, DeltaSeconds);

}

float UUIWidget::GetHealthPercent()
{
	return Player->Health / Player->MAXHEALTH;
}

float UUIWidget::GetRagePercent()
{
	return Player->Rage / Player->MAXRAGE;;
}

FString UUIWidget::GetAmmoValue()
{
	FString AmmoValue = FString::Printf(TEXT("Ammo: %i/%i"), PlayerWeapon->CurrentAmmo, PlayerWeapon->MagazineCapacity);
	if (PlayerWeapon->MAXIMUM_TOTAL_AMMO > 0)
	{
		//AmmoValue = FString::Printf(TEXT("%s %i"), AmmoValue, PlayerWeapon->TotalAmmo);
	}
	return AmmoValue;
}
