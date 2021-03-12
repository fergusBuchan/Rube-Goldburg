// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "GoldburgGameModeBase.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGoldburgGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	MenuHUDPointer = CreateWidget<UUserWidget>(GetWorld(), MenuHUDClass);
	PlayerHUDPointer = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	MenuHUDPointer->AddToViewport();

	if (PlayerHUDClass != nullptr)
	{
		if (MenuHUDPointer != nullptr)
		{
		}
	}

}

void AGoldburgGameModeBase::newGame() {

	
	MenuHUDPointer->RemoveFromViewport();
	PlayerHUDPointer->AddToViewport();

	if (PlayerHUDClass != nullptr)
	{

		if (PlayerHUDPointer != nullptr)
		{

		}
	}

	APC* player = Cast<APC>(UGameplayStatics::GetPlayerPawn(this, 0));
}
