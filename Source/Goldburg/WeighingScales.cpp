// Fill out your copyright notice in the Description page of Project Settings.


#include "WeighingScales.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

AWeighingScales::AWeighingScales()
{
	Hand = CreateDefaultSubobject<UStaticMeshComponent>("Bar");
	Hand->AttachTo(RootComponent);

	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Activator");
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	ActivatorBox->AttachTo(Mesh);
	ActivatorBox->OnComponentHit.AddDynamic(this, &AWeighingScales::OnHit);
}

void AWeighingScales::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	float targetAngle = (containedItems*(240/itemTrigger));
	
	if (AngleTurned < targetAngle)
	{
		Mesh->AddRelativeLocation(FVector(0, 0, -sinkSpeed * DeltaTime));
		Hand->AddLocalRotation(FRotator(-rotateSpeed * DeltaTime, 0, 0));
		AngleTurned += rotateSpeed * DeltaTime;
	}
}

void AWeighingScales::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeighingScales::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);

	Hand->SetRelativeRotation(HandRotation);
	activated = false;
	ContainedObjects.Empty();
	containedItems = 0;
	AngleTurned = 0;
}

void AWeighingScales::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bool newItem = true;
	for (int i = 0; i < ContainedObjects.Num(); i++)
	{
		if (ContainedObjects[i] == OtherActor)
		{
			newItem = false;
		}
	}
	if (newItem == true)
	{
		ContainedObjects.Add(OtherActor);
		if (containedItems < itemTrigger)
		{
			containedItems++;
			if (containedItems == itemTrigger && !activated)
			{
				activated = true;
				Press();
			}
		}
	}
}
