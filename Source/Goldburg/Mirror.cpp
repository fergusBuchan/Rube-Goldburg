// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror.h"

void AMirror::Rotate(bool clockwise)
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
