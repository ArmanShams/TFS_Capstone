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
	FString GetAmmoValue();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My New User Widget")
		FString UIWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player UI")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player UI")
		float Rage;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player UI")
		uint16 AmmoCount;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player UI")
		uint16 MagazineCount;

	ACharacterController* Player;
	AWeapon_Ranged* PlayerWeapon;

	friend class ACharacterController;
	friend class AWeapon_Ranged;
};
