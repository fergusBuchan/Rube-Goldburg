// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "LightBulb.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ALightBulb : public AMachineObject
{
	GENERATED_BODY()

public:
		ALightBulb(); 
        void BeginPlay() override;
        //void Tick(float DeltaTime) override;
        void Launch() override;
        void Reset() override;
        UPROPERTY(EditAnywhere)
        class UPointLightComponent* light;
};
