// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Hammer.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AHammer : public AMachineObject
{
	GENERATED_BODY()

public:

    AHammer();
    void Tick(float DeltaTime) override;
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    void Launch() override;
    void Activate() override;
    void Reset() override;

    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Joint1;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Joint2;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Joint3;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Joint4;

    UPROPERTY(EditAnywhere)
        class UBoxComponent* Front;
    UPROPERTY(EditAnywhere)
        class UBoxComponent* Rear;

    UPROPERTY(EditAnywhere)
        float force;


    UPROPERTY(EditAnywhere)
        FVector JointPositions[4];
};
