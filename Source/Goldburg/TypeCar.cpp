// Fill out your copyright notice in the Description page of Project Settings.


#include "TypeCar.h"
#include "Components/StaticMeshComponent.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

ATypeCar::ATypeCar()
{
	Wheel1 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel1");
	Wheel1->AttachTo(Mesh);
	Wheel2 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel2");
	Wheel2->AttachTo(Mesh);
	Wheel3 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel3");
	Wheel3->AttachTo(Mesh);
	Wheel4 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel4");
	Wheel4->AttachTo(Mesh);
	Wheel5 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel5");
	Wheel5->AttachTo(Mesh);
	Wheel6 = CreateDefaultSubobject<UStaticMeshComponent>("Wheel6");
	Wheel6->AttachTo(Mesh);
}
void ATypeCar::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel3->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel4->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel5->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel6->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	running = false;
	StopCounter = StopTime;
	bestVel = 0;
}

void ATypeCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();
	if (running)
	{
		FVector rayStart = Mesh->GetComponentLocation() + (Mesh->GetUpVector() * RayOffset);
		FVector rayEnd = rayStart + (Mesh->GetUpVector() * RayLenght);
		//DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Red, false, 5.0f);
		FHitResult* hit = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Vel: %f"), Mesh->GetComponentVelocity().Size()));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelSize: %f"), Mesh->GetComponentVelocity().RightVector.Size()));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelX: %f"), Mesh->GetPhysicsLinearVelocity().X));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelY: %f"), Mesh->GetPhysicsLinearVelocity().Y));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelZ: %f"), Mesh->GetPhysicsLinearVelocity().Z));
			//FVector temp = FVector::Ro;
			FVector temp = Mesh->GetRelativeRotation().Quaternion().UnrotateVector(Mesh->GetComponentVelocity());
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelX: %f"), temp.X));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelY: %f"), temp.Y));
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("VelZ: %f"), temp.Z));
			//Mesh->GetComponentVelocity().RightVector;
			if (Mesh->GetComponentVelocity().Size() < 5)
			{
				StopCounter -= DeltaTime;
				if (StopCounter <= 0)
				{
					running = false;
				}
			}
			else
			{
				StopCounter = StopTime;
			}
			if (Mesh->GetComponentVelocity().Size() < SpeedLimit)
			{
				if (type == 2)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Green, FString::Printf(TEXT("Vel: %f"), Mesh->GetComponentVelocity().Size()));
					if (Mesh->GetComponentVelocity().Size() > bestVel)
					{
						bestVel = Mesh->GetComponentVelocity().Size();
					}
					else
					{
						Mesh->SetPhysicsLinearVelocity(Mesh->GetForwardVector() * bestVel);
					}
				}
				else
				{
					Mesh->SetPhysicsLinearVelocity((Mesh->GetForwardVector() * temp.X) + (Mesh->GetUpVector() * temp.Z), false);
				}
				Mesh->AddForce(Mesh->GetForwardVector() * ForwardVelocity);
				Mesh->AddForce(Mesh->GetUpVector() * -driftOffset);
				//Mesh->AddForce(Mesh->GetRightVector() * -temp.Y); 

				//Mesh->AddForce(Mesh->GetRightVector() * -driftOffset);
			}
			float wheelRot = Mesh->GetComponentVelocity().Size() * RotSpeed * DeltaTime;
			Wheel1->AddLocalRotation(FRotator(-wheelRot, 0, 0));
			Wheel2->AddLocalRotation(FRotator(wheelRot, 0, 0));
			Wheel3->AddLocalRotation(FRotator(-wheelRot, 0, 0));
			Wheel4->AddLocalRotation(FRotator(wheelRot, 0, 0));
			if (type == 2)
			{
				Wheel5->AddLocalRotation(FRotator(-wheelRot, 0, 0));
				Wheel6->AddLocalRotation(FRotator(wheelRot, 0, 0));
			}
		}
		velocity = Mesh->GetComponentVelocity().Size();
		
		if (Mesh->GetComponentLocation().Z < 1000)
		{
			running = false;
		}
		lastPos = Mesh->GetComponentLocation();
	}
	else
	{
		velocity = 0;
	}
}

void ATypeCar::Activate()
{
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Wheel1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Wheel2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Wheel3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Wheel4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if (type == 2)
	{
		Wheel5->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Wheel6->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	if (!linked)
	{
		Launch();
	}
}

void ATypeCar::Launch()
{
	running = true;
	IsActivated = true;
	
}

void ATypeCar::Reset()
{
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel3->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel4->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel5->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Wheel6->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	running = false;
	StopCounter = StopTime;
	bestVel = 0;
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetRelativeLocationAndRotation(ResetPosition, ResetRotation);
}
