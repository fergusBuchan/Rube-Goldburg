// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "GoldburgGameModeBase.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGoldburgGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APC* player = Cast<APC>(UGameplayStatics::GetPlayerPawn(this, 0));
	onScreen = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	onScreen->AddToViewport();
	if (PlayerHUDClass != nullptr)
	{
		if (onScreen != nullptr)
		{
		}
	}
}