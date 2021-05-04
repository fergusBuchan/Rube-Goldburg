// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperPlane.h"
#include "Components/SkeletalMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

APaperPlane::APaperPlane()
{
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->AttachTo(RootComponent);
}

void APaperPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (running)
	{
		FVector rayStart1 = Body->GetSocketLocation(FName("Front"));
		FVector rayEnd1 = rayStart1 + (Body->GetRightVector() * frontRay);
		FVector rayStart2 = Body->GetSocketLocation(FName("Back"));
		FVector rayEnd2 = rayStart2 + (Body->GetUpVector() * Down);
		//DrawDebugLine(GetWorld(), rayEnd1, rayEnd2, FColor::Red, false, 5.0f);
		FHitResult* hit = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hit, rayEnd1, rayEnd2, ECollisionChannel::ECC_Visibility))
		{
			running = false;
			GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Stop")));
		}
		Body->SetPhysicsLinearVelocity((Body->GetRightVector() * ForwardVelocity) + (FVector(0, 0, -1) * gravity));
		if (Body->GetComponentLocation().X < BoundsXMinus)
		{
			running = false;
		}
		if (Body->GetComponentLocation().X > BoundsXPlus)
		{
			running = false;
		}
		if (Body->GetComponentLocation().Y < BoundsYMinus)
		{
			running = false;
		}
		if (Body->GetComponentLocation().Y > BoundsYPlus)
		{
			running = false;
		}
		velocity = Mesh->GetComponentVelocity().Size();
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), VelSave.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("X: %f"), GetActorLocation().X));
	}
	else
	{
		velocity = 0;
	}
}

void APaperPlane::Launch()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->SetSimulatePhysics(true);
	running = true;
	IsActivated = true;
}

void APaperPlane::Activate()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if (!linked)
	{
		Launch();
	}
}

void APaperPlane::Reset()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Body->SetSimulatePhysics(false);
	running = false;
	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Body->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}

