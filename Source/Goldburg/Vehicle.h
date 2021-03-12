// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Vehicle.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AVehicle : public AMachineObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* body;
		//class USkeletalMeshComponent* body;

	AVehicle();
	void Tick(float DeltaTime) override;
	void Launch() override;
	void Activate() override;
	void Reset() override;

	UPROPERTY(EditAnywhere)
		float Velocity;
	bool running = false;
};
