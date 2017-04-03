// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, category = "UI")
	float GetRagePercent();

	UFUNCTION(BlueprintCallable, category = "UI")
	FText GetAmmoValue();

	// The speed at which the progress bars on screen smoothly 'slide'
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player UI")
	float InterpolationSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "Player UI")
	float Rage;

	uint16 AmmoCount;

	uint16 MagazineCount;

	class ACharacterController* Player;
	class AWeapon_Ranged* PlayerWeapon;

	friend class ACharacterController;

	friend class AWeapon_Ranged;
};
