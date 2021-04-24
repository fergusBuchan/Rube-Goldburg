// Fill out your copyright notice in the Description page of Project Settings.


#include "Volcano.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

AVolcano::AVolcano()
{
	Volcano = CreateDefaultSubobject<USkeletalMeshComponent>("Mountian");
	Volcano->AttachTo(RootComponent);
	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Activator");
	ActivatorBox->SetNotifyRigidBodyCollision(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ActivatorBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	ActivatorBox->AttachTo(Volcano);
	ActivatorBox->OnComponentHit.AddDynamic(this, &AVolcano::OnHit);
}

void AVolcano::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (launched)
	{
		if (timer > 0)
		{
			timer -= DeltaTime;
		}
		if (timer <= 0 && !playing)
		{
			playing = true;
		}
	}
}

void AVolcano::Activate()
{
}

void AVolcano::Launch()
{
	launched = true;
	timer = LifeTime;
}

void AVolcano::Reset()
{
	launched = false;
	timer = LifeTime;
	playing = false;
}

void AVolcano::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		launched = true;
		timer = LifeTime;
	}
}
