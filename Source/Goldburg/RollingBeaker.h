// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "RollingBeaker.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ARollingBeaker : public AMachineObject
{
	GENERATED_BODY()
public:

	ARollingBeaker();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Launch() override;
	void Activate() override;
	void Reset() override;

	UPROPERTY(EditAnywhere)
		float Velocity;
	bool running = false;
};
