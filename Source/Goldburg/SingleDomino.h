// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleDomino.generated.h"

UCLASS()
class GOLDBURG_API ASingleDomino : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleDomino();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* ActivatorBox;
	UPROPERTY(EditAnywhere)
		class USoundBase* Audio;

	UPROPERTY(EditAnywhere)
		float AudioModifier;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();
	void Reset();
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};
