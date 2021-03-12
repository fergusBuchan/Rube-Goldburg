// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"
#include "GameFramework/MovementComponent.h"
#include "MovingActor.h"

AMover::AMover()
{

}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
}


void AMover::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		running = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Collided")));
	}
}

void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (!running)
	{

	}
//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("DT: %f"), DeltaTime));
}

void AMover::Launch()
{
	running = true;
	CommandPointer->Launch(GetActorRightVector(),GetActorRotation(), GetActorLocation());
	GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Launch")));
}

void AMover::Activate()
{
	if (!linked)
	{
		Launch();
	}
	CommandPointer->Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AMover::Reset()
{
	if (running == true)
	{
		CommandPointer->Reset();
		CommandPointer->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		CommandPointer->AddActorLocalOffset(ResetPosition);
		running = false;
	}
}

//Spawn object
void AMover::Spawn()
{
	//Because of tick delay with UMG buttons, must be spawned out of sight, otherwise it would spawn at 0,0,0
	//Object then snaps to finger at next tick, or when finget drags from button to floor
	//space outside of scene
	SetActorLocation(FVector(-1000000, -10000000000, -10000));
	LastValidPos = FVector(-1000000, -10000000000, -10000);

	if (Car != NULL)
	{
		//AActor* temp = Cast<AActor>(GetWorld()->SpawnActor(Car));
		CommandPointer = Cast<AMovingActor>(GetWorld()->SpawnActor(Car));
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Spawn")));
		if (CommandPointer != NULL)
		{
			CommandPointer->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			CommandPointer->AddActorLocalOffset(ResetPosition);
		}
	}
}

void AMover::DestroyVehicle()
{
	CommandPointer->Destroy();
}
