// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "SeeSaw.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ASeeSaw : public AMachineObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Bar; 
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* ThrowBlock;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;
	ASeeSaw();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void Activate() override;
	void Reset() override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
		FVector barReset;
	UPROPERTY(EditAnywhere)
	float attachtime;
	float launchTimer;
	bool launching;

	UPROPERTY(EditAnywhere)
		float launchImpulse;
};
