// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleDomino.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PC.h"

// Sets default values
ASingleDomino::ASingleDomino()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Domino");
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Body->SetSimulatePhysics(false);
	RootComponent = Body;

	ActivatorBox = CreateDefaultSubobject<UBoxComponent>("Collider");
	ActivatorBox->SetupAttachment(RootComponent);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ActivatorBox->OnComponentBeginOverlap.AddDynamic(this, &ASingleDomino::OnOverlap);  //->OnComponentHit.AddDynamic(this, &AVolcano::OnHit);

	AudioModifier = 1.0f;
}

// Called when the game starts or when spawned
void ASingleDomino::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleDomino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASingleDomino::Activate()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->SetSimulatePhysics(true);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASingleDomino::Reset()
{
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Body->SetSimulatePhysics(false);
	ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASingleDomino::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep , const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			if (Audio != NULL)
			{
				APC* a = Cast<APC>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				float volume = 1.0f * AudioModifier;
				if (a != NULL)
				{
					volume = (a->SFXVolume/100)* AudioModifier;
				}
				UGameplayStatics::PlaySoundAtLocation(this, Audio, Body->GetComponentLocation(),volume);
			}
			ActivatorBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

