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
		FVector rayStart = Body->GetSocketLocation(FName("Front"));
		FVector rayEnd = rayStart + (Body->GetRightVector() * frontRay);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
		FHitResult* hit = new FHitResult();
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
		if (GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
		{
			running = false;
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Stop")));
		}
		rayStart = Body->GetSocketLocation(FName("Back"));
		rayEnd = rayStart + (Body->GetUpVector() * Down);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
		hit = new FHitResult();
		bool BackDown = GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility);
		if (!BackDown)
		{
			Body->SetPhysicsLinearVelocity((Body->GetRightVector() * velocity) + (FVector(0, 0, -1) * gravity));
		}
		if (Body->GetComponentLocation().X > BoundsXPlus || Body->GetComponentLocation().X < BoundsXMinus || Body->GetComponentLocation().Y > BoundsYPlus || Body->GetComponentLocation().Y < BoundsYMinus)
		{
			running = false;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), VelSave.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("X: %f"), GetActorLocation().X));
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
