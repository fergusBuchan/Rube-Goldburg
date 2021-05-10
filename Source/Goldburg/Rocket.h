// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Rocket.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ARocket : public AMachineObject
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Body;

	ARocket();
	void Tick(float DeltaTime) override;
	void Launch() override;
	void Activate() override;
	void Reset() override;
	UPROPERTY(BlueprintReadOnly)
	bool running;
	UPROPERTY(EditAnywhere)
		float ForwardVelocity;
	UPROPERTY(EditAnywhere)
	float lifeTime;
	float lifeTimer;
};
