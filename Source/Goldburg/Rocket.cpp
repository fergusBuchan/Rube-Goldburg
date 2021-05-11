// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Components/SkeletalMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ARocket::ARocket()
{
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->AttachTo(RootComponent);
}

void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("time: %f"), lifeTimer));
	if (running)
	{
		
		lifeTimer -= DeltaTime;
		if (lifeTimer <= 0)
		{
			running = false;
		}
		//Body->SetPhysicsLinearVelocity(Body->GetUpVector() * Body->GetComponentVelocity().Size());
		Body->AddForce(Body->GetUpVector() * ForwardVelocity);
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Body->GetComponentLocation().Z));
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("X: %f"), GetActorLocation().X));
		velocity = Mesh->GetComponentVelocity().Size();
	}
	else
	{
		velocity = 0;
	}
}

void ARocket::Launch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Body->GetComponentLocation().Z));
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->SetSimulatePhysics(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Body->GetComponentLocation().Z));
	running = true;
	lifeTimer = lifeTime;
	IsActivated = true;
}

void ARocket::Activate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Body->GetComponentLocation().Z));
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Body->GetComponentLocation().Z));
	//Body->SetSimulatePhysics(true);
	if (!linked)
	{
		Launch();
	}
}

void ARocket::Reset()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Body->SetSimulatePhysics(false);
	running = false;
	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Body->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}
