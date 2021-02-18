// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Screw.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AScrew : public AMachineObject
{
	GENERATED_BODY()
	

public:
	void Tick(float DeltaTime) override;
	void Activate() override;
	void Reset() override;

	UPROPERTY(EditAnywhere)
		float RotSpeed;
	bool running = false;
};
