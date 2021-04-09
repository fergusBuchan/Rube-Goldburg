// Fill out your copyright notice in the Description page of Project Settings.


#include "Domino15.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ADomino15::ADomino15()
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
	Domino9 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 9");
	Domino9->AttachTo(RootComponent);
	Domino10 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 10");
	Domino10->AttachTo(RootComponent);
	Domino11 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 11");
	Domino11->AttachTo(RootComponent);
	Domino12 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 12");
	Domino12->AttachTo(RootComponent);
	Domino13 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 13");
	Domino13->AttachTo(RootComponent);
	Domino14 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 14");
	Domino14->AttachTo(RootComponent);
	Domino15 = CreateDefaultSubobject<UStaticMeshComponent>("Domino 15");
	Domino15->AttachTo(RootComponent);
}

void ADomino15::Activate()
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
	Domino9->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino9->SetSimulatePhysics(true);
	Domino10->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino10->SetSimulatePhysics(true);
	Domino11->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino11->SetSimulatePhysics(true);
	Domino12->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino12->SetSimulatePhysics(true);
	Domino13->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino13->SetSimulatePhysics(true);
	Domino14->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino14->SetSimulatePhysics(true);
	Domino15->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Domino15->SetSimulatePhysics(true);
}

void ADomino15::Reset()
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

	Domino9->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino9->SetSimulatePhysics(false);
	Domino9->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino9->SetRelativeLocationAndRotation(DominoPositions[8], DominoRotations[8]);

	Domino10->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino10->SetSimulatePhysics(false);
	Domino10->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino10->SetRelativeLocationAndRotation(DominoPositions[9], DominoRotations[9]);

	Domino11->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino11->SetSimulatePhysics(false);
	Domino11->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino11->SetRelativeLocationAndRotation(DominoPositions[10], DominoRotations[10]);

	Domino12->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino12->SetSimulatePhysics(false);
	Domino12->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino12->SetRelativeLocationAndRotation(DominoPositions[11], DominoRotations[11]);

	Domino13->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino13->SetSimulatePhysics(false);
	Domino13->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino13->SetRelativeLocationAndRotation(DominoPositions[12], DominoRotations[12]);

	Domino14->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino14->SetSimulatePhysics(false);
	Domino14->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino14->SetRelativeLocationAndRotation(DominoPositions[13], DominoRotations[13]);

	Domino15->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Domino15->SetSimulatePhysics(false);
	Domino15->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Domino15->SetRelativeLocationAndRotation(DominoPositions[14], DominoRotations[14]);
}
