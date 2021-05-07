// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerButton.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"
#include "MovingActor.h"
#include "TypeCar.h"

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
	if (!pressed)
	{
		if (disableOther)
		{
			AMovingActor* t = Cast<AMovingActor>(OtherActor);
			if (t != NULL)
			{
				if (t->Type != 2)
					t->running = false;
			}
			ATypeCar* u = Cast<ATypeCar>(OtherActor);
			if (u != NULL)
			{
				u->running = false;
			}
		}

		//ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		Press();
		pressed = true;
	}
}


void ATriggerButton::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	pressed = false;
}

void ATriggerButton::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
