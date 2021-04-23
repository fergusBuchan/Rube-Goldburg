// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserReceiver.h"

ALaserReceiver::ALaserReceiver()
{
	fired = false;
}

void ALaserReceiver::Rotate(bool clockwise)
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

void ALaserReceiver::Trigger()
{
	if (fired == false)
	{
		Press();
		fired = true;

		// for sound
		IsActivated = true;
	}
}

void ALaserReceiver::Activate()
{
	fired = false;
}

void ALaserReceiver::Reset()
{
	fired = false;
}
