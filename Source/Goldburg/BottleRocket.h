// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "BottleRocket.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ABottleRocket : public AMachineObject
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Lid;

    UPROPERTY(EditAnywhere)
        FVector LidPosition;

    UPROPERTY(EditAnywhere)
        FRotator LidRotation;

    ABottleRocket();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;
    void Activate() override;
    void Launch() override;
    void Reset() override;

    bool reacting;
    UPROPERTY(EditAnywhere)
        float reactionTime;
    float reactionTimer;

    bool launching;
    UPROPERTY(EditAnywhere)
        float launchTime;
    float launchTimer;

    UPROPERTY(EditAnywhere)
        float launchImpulse;
    UPROPERTY(EditAnywhere)
        float launchForce;

    bool active;

    UPROPERTY(BlueprintReadOnly)
    float angle;

    UPROPERTY(EditAnywhere)
        float reactionAngle;
};
