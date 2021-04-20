// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "TypeCar.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ATypeCar : public AMachineObject
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel1;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel2;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel3;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel4;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel5;
    UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Wheel6;

    ATypeCar();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;
    void Activate() override;
    void Launch() override;
    void Reset() override;
    bool running;
    UPROPERTY(EditAnywhere)
        float velocity;
    UPROPERTY(EditAnywhere)
        float driftOffset;
    UPROPERTY(EditAnywhere)
        float RotSpeed;

    UPROPERTY(EditAnywhere)
        float RayLenght;

    UPROPERTY(EditAnywhere)
        float RayOffset;

    UPROPERTY(EditAnywhere)
        float SpeedLimit;
    UPROPERTY(EditAnywhere)
        int type;

    UPROPERTY(EditAnywhere)
        float StopTime;

    float StopCounter;
    float bestVel;
};
