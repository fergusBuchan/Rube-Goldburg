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
		FVector rayStart2 = Body->GetSocketLocation(FName("Back"));
		FVector rayEnd2 = rayStart2 + (Body->GetUpVector() * Down);
		//DrawDebugLine(GetWorld(), rayStart2, rayEnd2, FColor::Red, false, 5.0f);
		FHitResult* hit = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hit, (rayStart2), rayEnd2, ECollisionChannel::ECC_Visibility))
		{
			running = false;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Stop")));
		}
		FVector rayStart1 = Body->GetSocketLocation(FName("Front"));
		FVector rayEnd1 = rayStart1+ (Body->GetRightVector() * frontRay);
		//DrawDebugLine(GetWorld(), rayStart1, rayEnd1, FColor::Red, false, 5.0f);
		FHitResult* frontHit = new FHitResult();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Ray2")));
		if (GetWorld()->LineTraceSingleByChannel(*frontHit, (rayStart1), rayEnd1, ECollisionChannel::ECC_Visibility))
		{
			//DrawDebugLine(GetWorld(), rayStart1, frontHit->Location, FColor::Red, false, 5.0f);
			running = false;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Stop")));
		}
		Body->SetPhysicsLinearVelocity((Body->GetRightVector() * ForwardVelocity) + (FVector(0, 0, -1) * gravity));
		
		velocity = Mesh->GetComponentVelocity().Size();
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
