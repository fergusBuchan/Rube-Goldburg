// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "GoldburgGameModeBase.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGoldburgGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APC* player = Cast<APC>(UGameplayStatics::GetPlayerPawn(this, 0));

	menuHUD = CreateWidget<UUserWidget>(GetWorld(), MenuHUDClass);
	playerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	if (menuHUD != nullptr)
	{
		menuHUD->AddToViewport();
	}
	else
	{
		playerHUD->AddToViewport();
	}

	if (PlayerHUDClass != nullptr)
	{
		if (playerHUD != nullptr)
		{
		}
	}
}

void AGoldburgGameModeBase::MenuUI(bool uiOn) {
	if (uiOn) {
		menuHUD->AddToViewport();
		playerHUD->RemoveFromViewport();
	}
	else {
		playerHUD->AddToViewport();
		menuHUD->RemoveFromViewport();
	}
}