// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, category = "Player UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, category = "Player UI")
	float GetRagePercent();

	UFUNCTION(BlueprintCallable, category = "Player UI")
	FText GetAmmoValue();

	UFUNCTION(BlueprintCallable, category = "Player UI")
	FVector2D GetMousePosition();

	// The speed at which the progress bars on screen smoothly 'slide'
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player UI")
	float InterpolationSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	float Health;
	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	float Rage;
	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	int32 AmmoCount;
	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	int32 MagazineCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player UI")
	TransformationState CurrentForm;

	class ACharacterController* Player;
	class AWeapon_Ranged* PlayerWeapon;

	friend class ACharacterController;
	friend class AWeapon_Ranged;
};
