// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activator.h"
#include "WeighingScales.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API AWeighingScales : public AActivator
{
	GENERATED_BODY()
        UPROPERTY(EditAnywhere)
        class UStaticMeshComponent* Hand;

    UPROPERTY(EditAnywhere)
        class UBoxComponent* ActivatorBox;

    UPROPERTY(EditAnywhere, Transient)
        TArray<class AActor*> ContainedObjects;

    UPROPERTY(EditAnywhere)
        FVector HandPosition;
    UPROPERTY(EditAnywhere)
        FRotator HandRotation;

    UPROPERTY(EditAnywhere)
        float rotateSpeed;
    UPROPERTY(EditAnywhere)
        float sinkSpeed;
        float AngleTurned;
    int containedItems;
    UPROPERTY(EditAnywhere)
        int itemTrigger;
    bool activated;
    AWeighingScales();
    void Tick(float DeltaTime) override;
    void Activate() override;
    void Reset() override;
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
