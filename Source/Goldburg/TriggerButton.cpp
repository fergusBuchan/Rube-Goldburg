// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerButton.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"
#include "MovingActor.h"

ATriggerButton::ATriggerButton()
{
	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Activator");
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	ActivatorBox->AttachTo(Mesh);
	ActivatorBox->OnComponentHit.AddDynamic(this, &ATriggerButton::OnHit);
}

void ATriggerButton::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	    AMovingActor* t = Cast<AMovingActor>(OtherActor);
		if (t != NULL)
		{
			t->running = false;
		}
		Press();
}

void ATriggerButton::Press()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Butotn Pressed")));
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	for (int i = 0; i < ControlledObjects.Num(); i++)
	{
		if (ControlledObjects[i] != NULL)
		{
			ControlledObjects[i]->Launch();
		}
	}

}

void ATriggerButton::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
}

void ATriggerButton::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
