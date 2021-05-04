// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Mover.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AMover : public AMachineObject 
{
	GENERATED_BODY()

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
public:

	UPROPERTY(EditAnywhere)		
		TSubclassOf<AActor> Car;
	UPROPERTY(EditAnywhere)
		class AMovingActor* CommandPointer;

	AMover();
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BumperBox;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Tick(float DeltaTime) override;
	void Launch() override;
	void Activate() override;
	void Reset() override;
	void Spawn() override;
	void DestroyVehicle();
	UPROPERTY(EditAnywhere)
		float Gravity;
	bool running = false;
	UPROPERTY(EditAnywhere)
	int Type = 0;

	UPROPERTY(EditAnywhere)
	FVector Front;
	UPROPERTY(EditAnywhere)
		float frontRange;

	UPROPERTY(EditAnywhere)
		float downRange;
};
