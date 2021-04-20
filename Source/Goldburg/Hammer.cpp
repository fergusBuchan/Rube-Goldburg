// Fill out your copyright notice in the Description page of Project Settings.


#include "Hammer.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

AHammer::AHammer()
{
	Joint1 = CreateDefaultSubobject<UStaticMeshComponent>("Joint 1");
	Joint1->AttachTo(RootComponent);
	Joint2 = CreateDefaultSubobject<UStaticMeshComponent>("Joint 2");
	Joint2->AttachTo(RootComponent);
	Joint3 = CreateDefaultSubobject<UStaticMeshComponent>("Joint 3");
	Joint3->AttachTo(RootComponent);
	Joint4 = CreateDefaultSubobject<UStaticMeshComponent>("Joint 4");
	Joint4->AttachTo(RootComponent);
}

void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	float a;
	a = Mesh->GetComponentVelocity().Size();
	if (a <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Velocity x:%f"), a));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("Velocity x:%f"), a));
	}
	
}

void AHammer::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AHammer::Launch()
{
	Mesh->AddImpulse(Mesh->GetRightVector()*force);
}

void AHammer::Activate()
{
	Joint1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Joint1->SetSimulatePhysics(true);
	Joint2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Joint2->SetSimulatePhysics(true);
	Joint3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Joint3->SetSimulatePhysics(true);
	Joint4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Joint4->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	if (!linked)
	{
		Launch();
	}
}

void AHammer::Reset()
{
	Joint1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Joint1->SetSimulatePhysics(false);
	Joint1->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Joint1->SetRelativeLocationAndRotation(JointPositions[0], FRotator(0, 0, 0));
	Joint2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Joint2->SetSimulatePhysics(false);
	Joint2->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Joint2->SetRelativeLocationAndRotation(JointPositions[1], FRotator(0, 0, 0));
	Joint3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Joint3->SetSimulatePhysics(false);
	Joint3->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Joint3->SetRelativeLocationAndRotation(JointPositions[2], FRotator(0, 0, 0));
	Joint4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Joint4->SetSimulatePhysics(false);
	Joint4->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Joint4->SetRelativeLocationAndRotation(JointPositions[3], FRotator(0,0,0));


	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(false);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}
