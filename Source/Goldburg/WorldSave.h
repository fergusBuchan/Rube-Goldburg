// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WorldSave.generated.h"

/**
 * simple class to contain obejcts when they are saved
 */
USTRUCT()
struct FSaveStruct
{
    GENERATED_BODY()
public:
	UPROPERTY()
		int objectIndex;
	UPROPERTY()
		FVector objectPosition;
	UPROPERTY()
		FRotator objectRotation;
	UPROPERTY()
		bool linked;
	UPROPERTY()
		int linkChannel;

};

UCLASS()
class GOLDBURG_API UWorldSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FSaveStruct> SavedObjects;
	UPROPERTY(BlueprintReadWrite)
		FString SaveName;
};
