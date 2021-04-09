// Fill out your copyright notice in the Description page of Project Settings.


#include "Activator.h"

#include <Engine.h>

void AActivator::Press()
{
	for (int i = 0; i < ControlledObjects.Num(); i++)
	{
		if (ControlledObjects[i] != NULL)
		{
			ControlledObjects[i]->Launch();
		}
	}

}