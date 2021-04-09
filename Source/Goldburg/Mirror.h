// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Mirror.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AMirror : public AMachineObject
{
	GENERATED_BODY()
public:
    void Rotate(bool) override;
};
