// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "PaperPlane.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API APaperPlane : public AMachineObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Body;


	APaperPlane();
	void Tick(float DeltaTime) override;
	void Launch() override;
	void Activate() override;
	void Reset() override;
	

	bool running;
	UPROPERTY(EditAnywhere)
		float frontRay;
	UPROPERTY(EditAnywhere)
		float Down;
	FVector direction;
	UPROPERTY(EditAnywhere)
		float ForwardVelocity;
	UPROPERTY(EditAnywhere)
		float gravity;
};
