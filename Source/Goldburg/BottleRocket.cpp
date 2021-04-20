// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleRocket.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ABottleRocket::ABottleRocket()
{
	Lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	Lid->AttachTo(Mesh);
	Lid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Lid->SetSimulatePhysics(false);
}

void ABottleRocket::BeginPlay()
{
	Super::BeginPlay();
	reacting = false;
	launched = false;
}

void ABottleRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	
	if (!reacting && !launched && active)
	{
		angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(-Mesh->GetUpVector(), FVector(0, 0, 1))));
		if (angle >= reactionAngle)
		{
			reacting = true;
			reactionTimer = reactionTime;
		}
	}
	if (reacting)
	{
		reactionTimer -= DeltaTime;
		if (reactionTimer <= 0)
		{
			Launch();
			reacting = false;
		}
	}
	if (launched)
	{
		if (launchTimer > 0)
		{
			launchTimer -= DeltaTime;
			Mesh->AddImpulse(-Mesh->GetUpVector() * launchForce);
			//add random offset aswell
		}
		
	}
}

void ABottleRocket::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	active = true;
}

void ABottleRocket::Launch()
{
	launched = true;
	launchTimer = launchTime;
	Lid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Lid->SetSimulatePhysics(true);
	Mesh->AddImpulse(-Mesh->GetUpVector()*launchImpulse);
	Lid->AddImpulse(Mesh->GetUpVector() * (launchImpulse/2));
}

void ABottleRocket::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(false);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);

	Lid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Lid->SetSimulatePhysics(false);
	Lid->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Lid->SetRelativeLocationAndRotation(LidPosition, LidRotation);

	reacting = false;
	launched = false;
	active = false;
}
