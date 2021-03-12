// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class GOLDBURG_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Body;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool running;
	UPROPERTY(EditAnywhere)
		float velocity;
	UPROPERTY(EditAnywhere)
	float gravity;
	void Launch(FVector dir, FRotator Rot, FVector pos);
	void Reset();

	UPROPERTY(EditAnywhere)
		float Down;
	FVector direction;
	FRotator Rotation;
	FVector Position;

	FVector VelSave;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* BumperBox;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	int Type;

	UPROPERTY(EditAnywhere)
		float frontRay;
};
