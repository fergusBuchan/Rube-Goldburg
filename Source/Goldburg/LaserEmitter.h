// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "LaserEmitter.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ALaserEmitter : public AMachineObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	float laserThickness;
	void Tick(float DeltaTime) override;
	void Rotate(bool) override;
	void Launch() override;
	void Reset() override;
	bool firing = false;
	UPROPERTY(EditAnywhere)
	int reflectionLimit = 100;
	UPROPERTY(EditAnywhere)
		int type;
	int Mirrors = 0;
	int currentMirror = 0;
	float newMirrorTimer;
	UPROPERTY(EditAnywhere)
		float mirrorInterval;
};
