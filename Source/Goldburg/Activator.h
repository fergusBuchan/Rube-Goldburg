// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Activator.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AActivator : public AMachineObject
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, Transient)
		TArray<class AMachineObject*> ControlledObjects;

	void Press();
};
