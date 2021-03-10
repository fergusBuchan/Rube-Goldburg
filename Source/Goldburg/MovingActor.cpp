// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"
#include "Components/SkeletalMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Vehicle Body");
	RootComponent = Body;
	/*BumperBox = CreateDefaultSubobject<UBoxComponent>("Bumper");
	BumperBox->SetNotifyRigidBodyCollision(true);
	BumperBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BumperBox->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	BumperBox->SetAllMassScale(0.0f);
	BumperBox->AttachTo(RootComponent);
	BumperBox->OnComponentHit.AddDynamic(this, &AMovingActor::OnHit);*/
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (running)
	{
		if (Type == 0)
		{
			FVector rayStart = Body->GetSocketLocation(FName("Front"));
			FVector rayEnd = rayStart + (GetActorRightVector() * frontRay);
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			FHitResult* hit = new FHitResult();
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			if(GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
			{
				running = false;
			}
			rayStart = Body->GetSocketLocation(FName("Front"));
			rayEnd = rayStart + (GetActorUpVector() * Down);
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			bool frontDown = GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility);
			rayStart = Body->GetSocketLocation(FName("Back"));
			rayEnd = rayStart + (GetActorUpVector() * Down);
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			bool backDown = GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility);

			if (frontDown || backDown)
			{
				if (abs(this->GetVelocity().Y + this->GetVelocity().X) < 100)
				{
					Body->SetPhysicsLinearVelocity(direction * 100);
				}
				VelSave = this->GetVelocity();
				Body->SetSimulatePhysics(false);
				//Body->SetWorldRotation(FRotator(this->GetActorRotation().Pitch, 0, 0));
				if (abs(direction.Y) > abs(direction.X))
				{
					Body->SetWorldLocation(FVector(Position.X, Body->GetComponentLocation().Y, Body->GetComponentLocation().Z));
				}
				else
				{
					Body->SetWorldLocation(FVector(Body->GetComponentLocation().X, Position.Y, Body->GetComponentLocation().Z));
				}
				Body->SetSimulatePhysics(true);
				Body->SetPhysicsLinearVelocity(VelSave);
				Body->AddForce(direction * velocity);
			}
			else
			{
				VelSave = this->GetVelocity();
				Body->SetSimulatePhysics(false);
				//Body->SetWorldRotation(FRotator(this->GetActorRotation().Pitch, 0, 0));
				Body->SetWorldLocation(FVector(Position.X, Body->GetComponentLocation().Y, Body->GetComponentLocation().Z));
				Body->SetSimulatePhysics(true);
				Body->SetPhysicsLinearVelocity(VelSave);
			}
		}
		else if (Type == 1)
		{
			FVector rayStart = Body->GetSocketLocation(FName("Front"));
			FVector rayEnd = rayStart + (GetActorRightVector() * frontRay);
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			FHitResult* hit = new FHitResult();
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			if(GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
			{
				running = false;
			}
			rayStart = Body->GetSocketLocation(FName("Back"));
			rayEnd = rayStart + (GetActorUpVector() * Down);
			//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
			hit = new FHitResult();
			bool BackDown = GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility);
			if (!BackDown)
			{
				Body->SetPhysicsLinearVelocity((direction * velocity) + (FVector(0, 0, -1) * gravity));
			}
		}
		else if (Type == 2)
		{
			Body->AddForce(Body->GetUpVector() * velocity);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), VelSave.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("X: %f"), GetActorLocation().X));
	}
}

void AMovingActor::Launch(FVector dir, FRotator Rot, FVector pos)
{
	direction = dir;
	Rotation = Rot;
	Position = pos;
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->SetSimulatePhysics(true);
	running = true;
}

void AMovingActor::Reset()
{
	Body->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Body->SetSimulatePhysics(false);
	running = false;
}

void AMovingActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		running = false;
	}
}

