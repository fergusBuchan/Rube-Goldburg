// Fill out your copyright notice in the Description page of Project Settings.


#include "SeeSaw.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ASeeSaw::ASeeSaw()
{
	Bar = CreateDefaultSubobject<UStaticMeshComponent>("Bar");
	Bar->AttachTo(RootComponent);
	Bar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Bar->SetSimulatePhysics(false);

	ThrowBlock = CreateDefaultSubobject<UStaticMeshComponent>("ThrowBar");
	ThrowBlock->AttachTo(Bar);
	ThrowBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThrowBlock->SetSimulatePhysics(false);
	ThrowBlock->SetHiddenInGame(true);

	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Activator");
	ActivatorBox->SetNotifyRigidBodyCollision(true); 
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	ActivatorBox->AttachTo(Bar);
	ActivatorBox->OnComponentHit.AddDynamic(this, &ASeeSaw::OnHit);

	launching = false;
}

void ASeeSaw::BeginPlay()
{
	Super::BeginPlay();
	Bar->SetAllMassScale(MassScale);
	Mesh->SetAllMassScale(MassScale);
	ThrowBlock->SetHiddenInGame(true);
}
void ASeeSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (launching)
	{
		
		launchTimer -= DeltaTime;
		if (launchTimer <= 0)
		{
			launching = false;
			ThrowBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ThrowBlock->SetHiddenInGame(true);
		}
	}
}

void ASeeSaw::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	Bar->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Bar->SetSimulatePhysics(true);

	ThrowBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThrowBlock->SetHiddenInGame(true);

	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
}

void ASeeSaw::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(false);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);

	Bar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Bar->SetSimulatePhysics(false);
	Bar->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Bar->SetRelativeLocation(barReset);

	ThrowBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThrowBlock->SetHiddenInGame(true);

	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	launching = false;
	Mesh->SetAllMassScale(MassScale);
	Bar->SetMassScale(NAME_None, MassScale);
}

void ASeeSaw::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Launched")));

	Mesh->SetAllMassScale(1.0);
	Bar->SetAllMassScale(1.0);
	launching = true;
	launchTimer = attachtime;
	ThrowBlock->SetHiddenInGame(true);
	ThrowBlock->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
