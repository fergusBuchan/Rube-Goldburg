// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserEmitter.h"
#include <Engine.h>
#include "Mirror.h"
#include "LaserReceiver.h"

void ALaserEmitter::Tick(float DeltaTime)
{
	position = GetActorLocation();
	if (firing)
	{
		int lockout = reflectionLimit;
		bool end = false;
		FVector rayStart = Mesh->GetSocketLocation(FName("Emitter"));
		FVector rayEnd = rayStart + (GetActorForwardVector() * 5000);
		FHitResult* hit = new FHitResult();
		while (!end)
		{
			lockout--;
			if (lockout == 0)
			{
				end = true;
			}
			if (GetWorld()->LineTraceSingleByChannel(*hit, rayStart, rayEnd, ECollisionChannel::ECC_GameTraceChannel5))
			{
				GetWorld()->LineBatcher->DrawLine(rayStart, hit->Location, FColor::Red, SDPG_World, laserThickness, 1);
				//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, hit->GetActor()->GetName());
				//CommandPointer = Cast<AMovingActor>(GetWorld()->SpawnActor(Car));
				AMirror* mirror = Cast<AMirror>(hit->GetActor());
				if (mirror != NULL)
				{
					if (hit->GetComponent() == mirror->Mesh)
					{
						if (type == 0 || (type == 1 && ((currentMirror <= Mirrors))))
						{
							rayStart = hit->Location;
							FVector in, out;
							in = (rayStart - rayEnd);
							in.Normalize();
							float dn = 2 * FVector::DotProduct(in, hit->ImpactNormal);
							out = in - (hit->ImpactNormal * dn);
							out *= -1;
							rayEnd = rayStart + (out * 5000);
							if (type == 1)
							{
								currentMirror++;
								if (currentMirror > Mirrors && newMirrorTimer <= 0)
								{
									newMirrorTimer = mirrorInterval;
									Mirrors = currentMirror;
									end = true;
								}
							}
						}
						else
						{
							end = true;
						}
						
					}
					else
					{
						end = true;
					}
				}
				else
				{
					ALaserReceiver* receiver = Cast<ALaserReceiver>(hit->GetActor());
					if (receiver != NULL)
					{
						if (hit->GetComponent() == receiver->Mesh)
						{
							receiver->Trigger();
						}
					}
					end = true;
				}
			}
			else
			{
				GetWorld()->LineBatcher->DrawLine(rayStart, rayEnd, FColor::Red, SDPG_World, laserThickness, 1);
				end = true;
			}
		}
		if (newMirrorTimer > 0)
		{
			newMirrorTimer -= DeltaTime;
		}
		currentMirror = 0;
	}
}

void ALaserEmitter::Rotate(bool clockwise)
{
	FRotator NewRotation;
	if (clockwise)
	{
		NewRotation = FRotator(0, 45, 0);
	}
	else
	{
		NewRotation = FRotator(0, -45, 0);
	}
	AddActorWorldRotation(NewRotation);
}

void ALaserEmitter::Launch()
{
	firing = true;
	Mirrors = 0;
	currentMirror = 0;
}

void ALaserEmitter::Reset()
{
	firing = false;
}
