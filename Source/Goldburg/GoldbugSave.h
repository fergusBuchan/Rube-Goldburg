// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GoldbugSave.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSavedObject {
	GENERATED_BODY()

	UPROPERTY()
		int objectIndex;
	UPROPERTY()
		FVector objectPosition;
	UPROPERTY()
		FRotator objectRotation;
};

UCLASS()
class GOLDBURG_API UGoldbugSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<struct FSavedObject> savedObjects;
	UPROPERTY(BlueprintReadWrite)
		FText saveName;
};
