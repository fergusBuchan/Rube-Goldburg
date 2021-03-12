// Fill out your copyright notice in the Description page of Project Settings.


#include "Domino8.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"


ADomino8::ADomino8()
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
	Domino6 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 6");
	Domino6->AttachTo(RootComponent);
	Domino7 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 7");
	Domino7->AttachTo(RootComponent);
	Domino8 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 8");
	Domino8->AttachTo(RootComponent);
}




void ADomino8::Activate()
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
	Domino6->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino6->SetSimulatePhysics(true);
	Domino7->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino7->SetSimulatePhysics(true);
	Domino8->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino8->SetSimulatePhysics(true);

}

void ADomino8::Reset()
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

	Domino6->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino6->SetSimulatePhysics(false);
	Domino6->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino6->SetRelativeLocationAndRotation(DominoPositions[5], DominoRotations[5]);

	Domino7->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino7->SetSimulatePhysics(false);
	Domino7->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino7->SetRelativeLocationAndRotation(DominoPositions[6], DominoRotations[6]);

	Domino8->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino8->SetSimulatePhysics(false);
	Domino8->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino8->SetRelativeLocationAndRotation(DominoPositions[7], DominoRotations[7]);
}


