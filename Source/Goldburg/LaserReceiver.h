// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activator.h"
#include "LaserReceiver.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ALaserReceiver : public AActivator
{
	GENERATED_BODY()
public:
    ALaserReceiver();
    void Rotate(bool) override;
    bool fired;
    void Trigger();
    void Activate() override;
    void Reset() override;
};
