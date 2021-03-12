// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GoldburgGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AGoldburgGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void newGame();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> MenuHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
		class UUserWidget* MenuHUDPointer;
	UPROPERTY()
		class UUserWidget* PlayerHUDPointer;
};
