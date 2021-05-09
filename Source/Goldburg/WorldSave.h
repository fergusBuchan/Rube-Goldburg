// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WorldSave.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FSaveStruct
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int objectIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector objectPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator objectRotation;

};

UCLASS()
class GOLDBURG_API UWorldSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FSaveStruct> SavedObjects;
	UPROPERTY(BlueprintReadWrite)
		FString SaveName;
};
