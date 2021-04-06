// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WorldSave.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API UWorldSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		TArray<class UObjectSave*> SavedObjects;
	UPROPERTY(BlueprintReadWrite)
		FString SaveName;
};
