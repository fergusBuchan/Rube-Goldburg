// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulb.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"

ALightBulb::ALightBulb()
{
	light = CreateDefaultSubobject<UPointLightComponent>("Light");
	light->AttachTo(Mesh);
}

void ALightBulb::BeginPlay()
{
	Super::BeginPlay();
	light->Deactivate();
	light->SetVisibility(false);
}

void ALightBulb::Launch()
{
	light->Activate();
	light->SetVisibility(true);
}

void ALightBulb::Reset()
{
	light->Deactivate();
	light->SetVisibility(false);
}
