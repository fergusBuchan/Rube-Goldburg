// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "SingleDomino.h"
#include "DominoSet.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ADominoSet : public AMachineObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		int dominoNum = 5;
	UPROPERTY(EditAnywhere)
		FVector DominoPositions[15];
	UPROPERTY(EditAnywhere)
		FRotator DominoRotations[15];

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASingleDomino> DominoBase;
	UPROPERTY(EditAnywhere)
		class ASingleDomino* Dominoes[15];

	void Activate() override;
	void Reset() override;
	void Spawn() override;
	void DestroyDominoes();
};
