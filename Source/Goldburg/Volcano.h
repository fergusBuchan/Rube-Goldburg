// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Volcano.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AVolcano : public AMachineObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Volcano;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;

	UPROPERTY(BlueprintReadWrite)
		bool playing;
	UPROPERTY(EditAnywhere)
	float LifeTime;
	float timer;
	bool launched;
	AVolcano();
	void Tick(float DeltaTime) override;
	void Activate() override;
	void Launch() override;
	void Reset() override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
