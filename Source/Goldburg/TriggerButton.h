// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activator.h"
#include "TriggerButton.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ATriggerButton : public AActivator
{
	GENERATED_BODY()
public:
	ATriggerButton();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;
	UPROPERTY(EditAnywhere)
		class USoundBase* Audio;

	UPROPERTY(EditAnywhere)
		float AudioModifier;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void Activate() override;
	void Reset() override;


	UPROPERTY(EditAnywhere)
		bool disableOther;

	bool pressed;
};
