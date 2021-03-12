// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Domino.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ADomino : public AMachineObject
{
	GENERATED_BODY()

public:
		ADomino();
	void Activate() override;
	void Reset() override;

	UPROPERTY(EditAnywhere)
		int dominoNum = 5;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino1;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino2;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino3;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino4;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino5;

	UPROPERTY(EditAnywhere)
		FVector DominoPositions[5];
	UPROPERTY(EditAnywhere)
		FRotator DominoRotations[5];
};
