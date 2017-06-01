// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "LoneWolfViewportClient.h"
#include "Blueprint/UserWidget.h"


void ULoneWolfViewportClient::LostFocus(FViewport * InViewport)
{
	Super::LostFocus(InViewport);

	if (OnFocusLost.IsBound())
	{
		OnFocusLost.Broadcast();
	}

	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	//wPauseHud = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/PauseMenuWidget.PauseMenuWidget_C'"), NULL, LOAD_None, NULL);

	/*if (wPauseHud)
	{
		PauseHud = CreateWidget<UUserWidget>(GetWorld(), wPauseHud);
		if (!PauseHud->GetIsVisible())
		{
			PauseHud->AddToViewport(80);
			if (APlayerController* RecastController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
			{
				PauseHud->SetUserFocus(RecastController);
			}
		}
	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("FOCUS LOST")));
}
