// Fill out your copyright notice in the Description page of Project Settings.


#include "Balloon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ABalloon::ABalloon()
{
	Balloon = CreateDefaultSubobject<USkeletalMeshComponent>("Balloon");
	Balloon->AttachTo(RootComponent);
	BalloonBall = CreateDefaultSubobject<USphereComponent>("BalloonCollider");
	BalloonBall->AttachTo(RootComponent);
}

void ABalloon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (launched)
	{
		if (timer > 0)
		{
			timer -= DeltaTime;
		}
		if (timer <= 0 && !playing)
		{
			playing = true;
			animSpeed = 0.1;
		}
	}
	if (playing == true)
	{
		bool canGrow = true;
		FVector rayStart = Balloon->GetSocketLocation(FName("Top"));
		FVector rayEnd = rayStart + (GetActorUpVector() * rayUp);
		DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
		FHitResult* hit = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
		{
			if (!hit->Component.Get()->IsSimulatingPhysics())
			{
				canGrow = false;
			}
		}
		if ((BalloonBall->GetUnscaledSphereRadius() < MaxScale) && canGrow)
		{
			BalloonBall->SetSphereRadius(BalloonBall->GetUnscaledSphereRadius() + (ScaleRate * DeltaTime));
		}
		else
		{
			BalloonBall->SetSphereRadius(MaxScale);
			playing = false;

		}
		if ((Balloon->GetRelativeLocation().Z <= MaxLift) && canGrow)
		{
			BalloonBall->AddLocalOffset(FVector(0, 0, (LiftRate * DeltaTime)));
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Radius %f"),BalloonBall->GetScaledSphereRadius()));

}


void ABalloon::Launch()
{
	launched = true;
	timer = LifeTime;
	Balloon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABalloon::Reset()
{
	launched = false;
	timer = LifeTime;
	playing = false;
	Balloon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BalloonBall->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	BalloonBall->SetRelativeLocation(ResetPosition);
	BalloonBall->SetSphereRadius(sphereResetScale);
}
