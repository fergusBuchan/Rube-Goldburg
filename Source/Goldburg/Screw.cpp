// Fill out your copyright notice in the Description page of Project Settings.


#include "Screw.h"
#include "Engine/StaticMesh.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

void AScrew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	
	if (running)
	{
		FRotator NewRotation;
		NewRotation = FRotator(0, RotSpeed * DeltaTime, 0);
		Mesh->AddWorldRotation(NewRotation);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("DT: %f"), DeltaTime));

}

void AScrew::Activate()
{
	running = true;
}

void AScrew::Reset()
{
	running = false;
}
