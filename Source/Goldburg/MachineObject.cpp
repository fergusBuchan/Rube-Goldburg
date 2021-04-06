// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineObject.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"

#include "Styling/SlateBrush.h"
// Sets default values
AMachineObject::AMachineObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Box component
	SelectBase = CreateDefaultSubobject<UBoxComponent>("Base");
	//Set box collision 
	SelectBase->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SelectBase->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SelectBase->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
	RootComponent = SelectBase;
	//Create Static Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Object");
	Mesh->AttachTo(RootComponent);
	//Set Mesh Collision
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);

	height = 60;
}

// Called when the game starts or when spawned
void AMachineObject::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetAllMassScale(MassScale);
}

// Called every frame
void AMachineObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	position = GetActorLocation();
}

void AMachineObject::Select(bool select)
{
	
}

void AMachineObject::Move(FVector FingerLoc)
{
	//!!!!Make sure floor has correct tags checked!!!!
	//if player finger is not currently over the floor
	if (FingerLoc.X == 0)
	{
		//Default to last valid position
		SetActorLocation(LastValidPos);
	}
	else
	{
		float X, Y;
		//Get remainder of fingerX location divided by 100(grid size)
		X = abs(fmod(FingerLoc.X, 100)); // 100 is current grid size
		if (X > 50)
		{
			X = 100 - X;
		}
		if (fmod(FingerLoc.X - X, 100) == 0)
		{
			X = FingerLoc.X - X;
		}
		else
		{
			X = FingerLoc.X + X;
		}
		Y = abs(fmod(FingerLoc.Y, 100)); 
		if (Y > 50)
		{
			Y = 100 - Y;
		}
		if (fmod(FingerLoc.Y - Y, 100) == 0)
		{
			Y = FingerLoc.Y - Y;
		}
		else
		{
			Y = FingerLoc.Y + Y;
		}
		SetActorLocation(FVector(X, Y, GetActorLocation().Z));
		//If object height is below minimum height
		if (GetActorLocation().Z < MinHeight)
		{
			//set object to minimum height
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, MinHeight));
		}
		//need to do check to make sure there is room (not colliding with another object)
		//Set valid position
		LastValidPos = GetActorLocation();
	}
}
//Rotate object 90 degrees
void AMachineObject::Rotate(bool clockwise)
{
	FRotator NewRotation;
	if (clockwise)
	{
		NewRotation = FRotator(0, 90, 0);
	}
	else
	{
		NewRotation = FRotator(0, -90, 0);
	}
	AddActorWorldRotation(NewRotation);
}

void AMachineObject::Lift(float delta)
{
	heightDelta -= delta;
	if (heightDelta >= 10)
	{
		AddActorLocalOffset(FVector(0, 0, 10));
		heightDelta -= 10;
	}
	else if (heightDelta <= -10)
	{
		if (GetActorLocation().Z - 10 >= MinHeight)
		{
			AddActorLocalOffset(FVector(0, 0, -10));
			heightDelta += 10;
		}
		else
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, MinHeight));
			heightDelta = 0;
		}
	}
	LastValidPos = GetActorLocation();
}
void AMachineObject::Launch()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetSimulatePhysics(true);
}
//Activate object when scene is played (to be swapped for virtual function for children)
void AMachineObject::Activate()
{
	if (!linked)
	{
		Launch();
	}
		
}
//Reset object when play stops (to be swapped for virtual function for children)
void AMachineObject::Reset()
{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetSimulatePhysics(false);
		Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}
//Spawn object
void AMachineObject::Spawn()
{
	//Because of tick delay with UMG buttons, must be spawned out of sight, otherwise it would spawn at 0,0,0
	//Object then snaps to finger at next tick, or when finget drags from button to floor
	//space outside of scene
	SetActorLocation(FVector(-1000000, -10000000000, -10000));
	LastValidPos = FVector(-1000000, -10000000000, -10000);
	linkChannel = 0;
	linked = false;
}


