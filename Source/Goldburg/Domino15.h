// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Domino15.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ADomino15 : public AMachineObject
{
	GENERATED_BODY()
public:
	ADomino15();
	void Activate() override;
	void Reset() override;

	UPROPERTY(EditAnywhere)
		int dominoNum = 15;
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
		class UStaticMeshComponent* Domino9;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino10;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino11;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino12;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino13;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino14;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Domino15;

	UPROPERTY(EditAnywhere)
		FVector DominoPositions[15];
	UPROPERTY(EditAnywhere)
		FRotator DominoRotations[15];
};
