// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

AVehicle::AVehicle()
{
	body = CreateDefaultSubobject<UStaticMeshComponent>("VehicleBody");
	body->AttachTo(RootComponent);
}

void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();

	if (running)
	{
		body->SetPhysicsLinearVelocity(body->GetForwardVector() * Velocity);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("DT: %f"), DeltaTime));

}

void AVehicle::Launch()
{
	running = true;
}

void AVehicle::Activate()
{
	body->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	body->SetSimulatePhysics(true);
	if (!linked)
	{
		Launch();
	}
}

void AVehicle::Reset()
{
	running = false;
	body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	body->SetSimulatePhysics(false);
	body->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	body->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}
