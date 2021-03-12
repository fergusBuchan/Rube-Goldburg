// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "TriggerButton.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ATriggerButton : public AMachineObject
{
	GENERATED_BODY()
public:
	ATriggerButton();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;

	UPROPERTY(EditAnywhere, Transient)
		TArray<class AMachineObject*> ControlledObjects;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Press();
	void Activate() override;
	void Reset() override;
};
