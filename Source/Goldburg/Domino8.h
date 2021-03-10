// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Domino8.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ADomino8 : public AMachineObject
{
	GENERATED_BODY()
public:
	ADomino8();
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
		class UStaticMeshComponent* Domino6;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino7;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino8;

	UPROPERTY(EditAnywhere)
		FVector DominoPositions[8];
	UPROPERTY(EditAnywhere)
		FRotator DominoRotations[8];
};
