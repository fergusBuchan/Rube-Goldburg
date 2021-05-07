// Fill out your copyright notice in the Description page of Project Settings.


#include "DominoSet.h"
#include "SingleDomino.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

void ADominoSet::Activate()
{
	for (int i = 0; i < dominoNum; i++)
	{
		if (Dominoes[i] != NULL)
		{
			Dominoes[i]->Activate();
		}
	}
}

void ADominoSet::Reset()
{
	for (int i = 0; i < dominoNum; i++)
	{
		if (Dominoes[i] != NULL)
		{
			Dominoes[i]->Reset(); 
			Dominoes[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Dominoes[i]->SetActorRelativeLocation(DominoPositions[i]);
			Dominoes[i]->SetActorRelativeRotation(DominoRotations[i]);
		}
	}
}

void ADominoSet::Spawn()
{
	if (DominoBase != NULL)
	{
		for (int i = 0; i < dominoNum; i++)
		{
			Dominoes[i] = Cast<ASingleDomino>(GetWorld()->SpawnActor(DominoBase));
			if (Dominoes[i] != NULL)
			{
				Dominoes[i]->Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Dominoes[i]->Body->SetSimulatePhysics(false);
				Dominoes[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Dominoes[i]->SetActorRelativeLocation(DominoPositions[i]);
				Dominoes[i]->SetActorRelativeRotation(DominoRotations[i]);
				GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Domino %i"),i));
			}
		}
	}
	Reset();
}

void ADominoSet::DestroyDominoes()
{
	for (int i = 0; i < dominoNum; i++)
	{
		if (Dominoes[i] != NULL)
		{
			Dominoes[i]->Destroy();
		}
	}
}
