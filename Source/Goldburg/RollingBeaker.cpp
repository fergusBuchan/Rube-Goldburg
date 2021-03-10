// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBeaker.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Math/Vector.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

ARollingBeaker::ARollingBeaker()
{
	//////////////

	/////////////


	////need to replace with custom cylinder collision
	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Activator");
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	ActivatorBox->AttachTo(Mesh);
	ActivatorBox->OnComponentHit.AddDynamic(this, &ARollingBeaker::OnHit);
}

void ARollingBeaker::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FVector b = OtherComp->ComponentVelocity;
		if (b.X > b.Y)
		{
			b.Y = 0;
		}
		else if (b.Y > b.X)
		{
			b.X = 0;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Hit")));
		Mesh->SetPhysicsLinearVelocity(b * Velocity);
		//OtherComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		/*FVector a = Mesh->GetComponentLocation() - OtherComp->GetComponentLocation();
		if (a.X > a.Y)
		{
			a.Y = 0;
		}
		else if (a.Y > a.X)
		{
			a.X = 0;
		}
		a.Normalize(1.0f);
		Mesh->AddImpulseAtLocation(a * Velocity, OtherComp->GetComponentLocation());
		
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//Launch();
		*/
	}
}

void ARollingBeaker::Launch()
{
	//Mesh->AddImpulseAtLocation();
}

void ARollingBeaker::Activate()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->SetSimulatePhysics(true);
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
}

void ARollingBeaker::Reset()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(false);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
