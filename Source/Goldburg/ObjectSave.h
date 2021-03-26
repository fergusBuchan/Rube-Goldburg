// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectSave.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API UObjectSave : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
		int objectIndex;
	UPROPERTY()
		FVector objectPosition;
	UPROPERTY()
		FRotator objectRotation;
};
