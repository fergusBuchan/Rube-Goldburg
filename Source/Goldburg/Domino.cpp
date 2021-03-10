// Fill out your copyright notice in the Description page of Project Settings.


#include "Domino.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"


ADomino::ADomino()
{
	Domino1 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 1");
	Domino1->AttachTo(RootComponent);
	Domino2 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 2");
	Domino2->AttachTo(RootComponent);
	Domino3 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 3");
	Domino3->AttachTo(RootComponent);
	Domino4 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 4");
	Domino4->AttachTo(RootComponent);
	Domino5 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 5");
	Domino5->AttachTo(RootComponent);
}




void ADomino::Activate()
{
	Domino1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino1->SetSimulatePhysics(true);
	Domino2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino2->SetSimulatePhysics(true);
	Domino3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino3->SetSimulatePhysics(true);
	Domino4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino4->SetSimulatePhysics(true);
	Domino5->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino5->SetSimulatePhysics(true);
}

void ADomino::Reset()
{
	Domino1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino1->SetSimulatePhysics(false);
	Domino1->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino1->SetRelativeLocationAndRotation(DominoPositions[0], DominoRotations[0]);

	Domino2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino2->SetSimulatePhysics(false);
	Domino2->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino2->SetRelativeLocationAndRotation(DominoPositions[1], DominoRotations[1]);

	Domino3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino3->SetSimulatePhysics(false);
	Domino3->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino3->SetRelativeLocationAndRotation(DominoPositions[2], DominoRotations[2]);

	Domino4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino4->SetSimulatePhysics(false);
	Domino4->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino4->SetRelativeLocationAndRotation(DominoPositions[3], DominoRotations[3]);

	Domino5->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino5->SetSimulatePhysics(false);
	Domino5->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino5->SetRelativeLocationAndRotation(DominoPositions[4], DominoRotations[4]);
}

