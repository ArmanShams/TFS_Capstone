// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Weapons/Weapon_PlayerRevolver.h"
#include "UIWidget.h"

#define LOCTEXT_NAMESPACE "UINameSpace"


void UUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bCanEverTick = true;
	if (Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Player = Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player != NULL)
		{
			PlayerWeapon = Cast<AWeapon_Ranged>(Player->CurrentlyEquippedWeapon);
			Health = Player->Health;
			//Player->TakeDamage.AddDynamic(this, &ThisClass::PlayerWasHit);
		}
	}
	if (InterpolationSpeed == 0.f)
	{
		InterpolationSpeed = 2.0f;
	}

}

void UUIWidget::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry, DeltaSeconds);
	if (Player != NULL)
	{
		if (AWeapon_Ranged* RecastPlayerWeapon = Cast<AWeapon_Ranged>(Player->CurrentlyEquippedWeapon))
		{
			PlayerWeapon = Cast<AWeapon_Ranged>(Player->CurrentlyEquippedWeapon);
			
		}
		else
		{
			PlayerWeapon = NULL;
		}
		Health = FMath::FInterpTo(Health, Player->Health, DeltaSeconds, InterpolationSpeed);
		CurrentForm = Player->CurrentForm;
		Rage = FMath::FInterpTo(Rage, Player->Rage, DeltaSeconds, InterpolationSpeed);
	}
	if (PlayerWeapon != NULL)
	{
		AmmoCount = PlayerWeapon->CurrentAmmo;
	}
}

float UUIWidget::GetHealthPercent()
{
	return Health / Player->MAXHEALTH;
}

float UUIWidget::GetRagePercent()
{
	return Rage / Player->MAXRAGE;
}

FText UUIWidget::GetAmmoValue()
{
	// Old method, doesn't support localization
	//FString AmmoValue = FString::Printf(TEXT("Ammo: %i/%i"), PlayerWeapon->CurrentAmmo, PlayerWeapon->MagazineCapacity);
	// New method, supports localization.
	if (PlayerWeapon != NULL && Player->CurrentForm == TransformationState::HUMAN)
	{
		FFormatNamedArguments Arguments;
		Arguments.Add("CurrentAmmo", FText::AsNumber(PlayerWeapon->CurrentAmmo));
		Arguments.Add("MaxAmmo", FText::AsNumber(PlayerWeapon->MagazineCapacity));

		if (PlayerWeapon->MAXIMUM_TOTAL_AMMO > 0)
		{
			Arguments.Add("TotalAmmo", FText::AsNumber(PlayerWeapon->TotalAmmo));
			FText AmmoValue = FText::Format(NSLOCTEXT("UINameSpace", "Ammo", "Ammo: {CurrentAmmo}/{MaxAmmo} \n					{TotalAmmo}"), Arguments);
			return AmmoValue;
		}
		FText AmmoValue = FText::Format(NSLOCTEXT("UINameSpace", "Ammo", "Ammo: {CurrentAmmo}/{MaxAmmo}"), Arguments);
		return AmmoValue;
	}
	return FText();
}

FVector2D UUIWidget::GetMousePosition()
{
	if (Player != NULL)
	{
		if (GetWorld()->HasBegunPlay())
		{
			FVector2D MousePosition;
			if (APlayerController* RecastController = Cast<APlayerController>(Player->GetController()))
			{
				if (GetWorld()->GetGameViewport() && RecastController->GetMousePosition(MousePosition.X, MousePosition.Y))
				{
					return MousePosition;
				}
			}
		}
	}
	return FVector2D::ZeroVector;
}

#undef LOCTEXT_NAMESPACE 
