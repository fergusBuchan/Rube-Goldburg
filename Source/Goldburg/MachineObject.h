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
	virtual void Rotate(bool);
	void Lift(float);
	virtual void Launch();
	virtual void Activate();
	virtual void  Reset();
	virtual void Spawn();
	bool launched;
	UPROPERTY(EditAnywhere)
		bool Active;
	UPROPERTY(EditAnywhere)
		bool Tracking;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MinHeight;
	UPROPERTY(EditAnywhere)
	float height;
	UPROPERTY(EditAnywhere)
		UTexture2D* OBJIMG;

	UPROPERTY(EditAnywhere)
		FVector Offset;

	float heightDelta;
	FVector LastValidPos;
	FVector position;

	UPROPERTY(EditAnywhere)
		FVector ResetPosition;
	UPROPERTY(EditAnywhere)
		FRotator ResetRotation;

	UPROPERTY(EditAnywhere)
		float MassScale = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TabNum;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsActivated;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ObjectTypeIndex;

	UPROPERTY(EditAnywhere)
	bool linked;
	UPROPERTY(EditAnywhere)
	int linkChannel = 0;

	UPROPERTY(BlueprintReadOnly)
		float velocity;
};
