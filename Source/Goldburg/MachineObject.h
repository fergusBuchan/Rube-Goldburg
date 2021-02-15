// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MachineObject.generated.h"

UCLASS()
class GOLDBURG_API AMachineObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMachineObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* SelectBase;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	void Select(bool);
	void Move(FVector);
	void Rotate(bool);
	void Lift(float);
	void Activate();
	void Reset();
	void Spawn();

	UPROPERTY(EditAnywhere)
		bool Active;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MinHeight;
	UPROPERTY(EditAnywhere)
		UTexture2D* OBJIMG;
	
	float heightDelta;
	FVector LastValidPos;
	FVector center;
};
