// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"

#include "MachineObject.h"
#include <GameFramework\SpringArmComponent.h>
#include <Camera\CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include <Engine.h>
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Styling/SlateBrush.h"
#include "TriggerButton.h"
#include "Activator.h"
#include "Mover.h"
// Sets default values
APC::APC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.0f; 

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	MoveIMG = CreateDefaultSubobject<UPaperSpriteComponent>("Move Button?");
	MoveIMG->SetVisibility(false);
	MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoveIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);
	
	LiftIMG = CreateDefaultSubobject<UPaperSpriteComponent>("Lift Button");
	LiftIMG->SetVisibility(false);
	LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LiftIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	RotCIMG = CreateDefaultSubobject<UPaperSpriteComponent>("Rot Clockwise Button");
	RotCIMG->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	RotCIMG->SetVisibility(false);
	RotCIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotCIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	RotACIMG = CreateDefaultSubobject<UPaperSpriteComponent>("Rot Anti-Clockwise Button");
	RotACIMG->AttachToComponent(Camera,FAttachmentTransformRules::KeepRelativeTransform);
	RotACIMG->SetVisibility(false);
	RotACIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotACIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	Speed = 1;
	StickSensitivity = 1;
	StartingOffset = 0.5;
	minPitch = 16;
	minArmLenght = 100;
	maxArmLenght = 700;
	maxFixedArmLenght = 1000;
	zoomDif = 20;
}

// Called when the game starts or when spawned
void APC::BeginPlay()
{
	Super::BeginPlay();
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	controller = Cast<APlayerController>(GetController());
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	AddControllerPitchInput(StartingOffset);
	Selected = false;
	lifting = false;
	moving = false;
	Fixed = false;
	ObjectMenuOpen = false;
	following = false;
	tracked = 0;
	playing = false;
	pickerOpen = false;
}

// Called every frame
void APC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    controller->GetInputTouchState(ETouchIndex::Touch1, NewTouch.X, NewTouch.Y, clicked);

	VectorRight = Camera->GetRightVector();
	VectorUp = Camera->GetUpVector();

	if (clicked)
	{
		if (Selected && (moving || lifting))
		{
			if (SelectedObject != NULL)
			{
				if (moving)
				{
					FHitResult* hit = new FHitResult();
					controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel2, false, *hit);
					if (hit != nullptr)
					{
						FVector newloc = hit->Location - moveOffset;
						SelectedObject->Move(newloc);
					}
					else
					{
						SelectedObject->Move(FVector(0,0,0));
					}
				}
				else if (lifting)
				{
					FVector2D Delta = NewTouch - LastTouch;
					SelectedObject->Lift(Delta.Y);
					LastTouch = NewTouch;
				}
			}
		}
		else
		{
			if (!following || !playing || ActiveObjects[tracked] != NULL)
			{
				FVector2D Delta = NewTouch - LastTouch;
				FVector Xoffset = GetActorRightVector() * -Delta.X; //FVector(DeltaTouch.X, 0.0f, 0.0f);
				AddActorWorldOffset(Xoffset);
				FVector Yoffset = GetActorForwardVector() * Delta.Y; //FVector(DeltaTouch.X, 0.0f, 0.0f);
				AddActorWorldOffset(Yoffset);
			}
			LastTouch = NewTouch;
		}
		FHitResult Hit(ForceInit);
		//Dont make this an 'if' 
		controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel3, false, Hit);
		SelectedTemp2 = Cast<AMachineObject>(Hit.GetActor());
	}
	if (SelectedObject != NULL)
	{
		SelectedPos = SelectedObject->position;
		MoveIMG->SetVisibility(true);
		MoveIMG->SetWorldLocation(FVector(SelectedPos.X, SelectedPos.Y, 21));//21 is just above current floor height
		if (GetControlRotation().Pitch < 285 && GetControlRotation().Pitch > 255)
		{
			LiftIMG->SetVisibility(false);
		}
		else
		{
			LiftIMG->SetVisibility(true);
		}
		LiftIMG->SetWorldLocation(FVector(SelectedPos.X, SelectedPos.Y, SelectedPos.Z + SelectedObject->height));
		FVector diff = Camera->GetComponentLocation() - SelectedPos;
		diff *= FVector(1.0, 1.0, 0.0);
		diff.Normalize();
		FRotator temp = UKismetMathLibrary::MakeRotFromX(diff);
		LiftIMG->SetWorldRotation(FRotator(temp.Pitch, temp.Yaw + 90, temp.Roll));
		RotCIMG->SetVisibility(true);
		RotCIMG->SetWorldLocation(SelectedPos + (VectorRight * 70));
		RotACIMG->SetVisibility(true);
		RotACIMG->SetWorldLocation(SelectedPos + (VectorRight * -70));
	}
	else
	{
		//SelectedPos = FVector(0, 0, 0);
		MoveIMG->SetVisibility(false);
		LiftIMG->SetVisibility(false);
		RotCIMG->SetVisibility(false);
		RotACIMG->SetVisibility(false);
	}
	if (playing)
	{
		if (following)
		{
			if (ActiveObjects.Num() > tracked)
			{
				if (ActiveObjects[tracked] != NULL)
				{
					if (ActiveObjects[tracked]->Tracking)
					{
						SetActorLocation(ActiveObjects[tracked]->Mesh->GetComponentLocation());
					}
					else
					{
						nextTarget();
					}
				}
			}
			else
			{
				tracked = 0;
			}
		}
		ObjectMenuOpen = false;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1,0.03f,FColor::Orange, FString::Printf(TEXT("Angle %f"), GetControlRotation().Pitch));

}

// Called to bind functionality to input
void APC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Player Controls
	PlayerInputComponent->BindAxis("MouseX", this, &APC::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APC::MouseY);

	//Object Controls

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &APC::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APC::TouchStopped);
}


void APC::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		touchLoc = Location;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("X %f"), Location.X));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Y %f"), Location.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Z %f"), Location.Z));
		clicked = true;
		controller->GetInputTouchState(ETouchIndex::Touch1,LastTouch.X,LastTouch.Y,clicked);
		FHitResult Hit(ForceInit);
		if (playing)
		{
			Selected = false;
		}
		else
		{
			if (SelectedObject != NULL && controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel4, false, Hit))
			{
				Selected = true;
				if (Hit.Component == MoveIMG)
				{
					if (SelectedObject != NULL)
					{
						moveOffset = (Hit.Location - SelectedObject->GetActorLocation());
					}
					else
					{
						moveOffset = FVector(0, 0, 0);
					}
					moving = true;
				}
				else if (Hit.Component == LiftIMG)
				{
					lifting = true;
				}
				else if (Hit.Component == RotCIMG)
				{
					RotateClockwise();
				}
				else if (Hit.Component == RotACIMG)
				{
					RotateAntiClockwise();
				}
				touchLoc = FVector(-100,-100,-100);
			}
			else if (controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel3, false, Hit))
			{
				SelectedTemp = Cast<AMachineObject>(Hit.GetActor());
			}
			else
			{
				Selected = false;
			}
		}
	}
}


void APC::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	clicked = false;
	moving = false;
	lifting = false;
	if ((SelectedTemp2 == SelectedTemp) && (SelectedTemp != NULL))
	{
		if (SelectedObject != SelectedTemp)
		{
			if (SelectedObject != NULL)
			{
				SelectedObject->Select(false);
				SelectedObject = NULL;
				objSelected = false;
				Selected = false;
			}
			SelectedObject = SelectedTemp;
			if (SelectedObject != NULL)
			{
				SelectedObject->Select(true);
				SelectedPos = SelectedObject->position;
				objSelected = true;
				Selected = true;
			}
		}
	}
	else
	{
		if (FVector::Dist(touchLoc, Location) < deselectDist)
		{
			//Deselect current object
			if (SelectedObject != NULL)
			{
				SelectedObject->Select(false);
				SelectedObject = NULL;
				objSelected = false;
				Selected = false;
			}
		}
	}
	SelectedTemp = nullptr;SelectedTemp2 = nullptr;
	//if not moved
	
}


void APC::MouseX(float value)
{
	if(!Fixed)
	AddControllerYawInput(value * StickSensitivity);
}

void APC::MouseY(float value)
{
	if (!Fixed)
	AddControllerPitchInput(value * StickSensitivity);
}

//Set player height
void APC::SetHeight(float newHeight)
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y,newHeight));
}

float APC::GetHeight()
{
	return GetActorLocation().Z;
}

//Toggle fixed camera
void APC::SetFixed()
{
	Fixed = !Fixed;
	//if in fixed camera mode
	if (Fixed)
	{
		//snap to closest diagonal view
		//Extend camera arm length
		CameraBoom->TargetArmLength = 800;//45 135 225 315
		float Yaw = GetControlRotation().Yaw;
		while(Yaw > 360)
		{
			Yaw -= 360;
		}
		while (Yaw < 0)
		{
			Yaw += 360;
		}
		if (Yaw >= 0 && Yaw < 90)
		{
			Yaw = 45;
		}
		else if(Yaw >= 90 && Yaw < 180)
		{
			Yaw = 135;
		}
		else if (Yaw >= 180 && Yaw < 270)
		{
			Yaw = 225;
		}
		else if (Yaw >= 270 && Yaw <= 360)
		{
			Yaw = 315;
		}
		controller->SetControlRotation(FRotator(310, Yaw, GetControlRotation().Roll));
	}
	else
	{
		//in free mode
		//reduce camera arm length
		if(CameraBoom->TargetArmLength > 300)
		CameraBoom->TargetArmLength = 300;
		controller->SetControlRotation(FRotator(335, GetControlRotation().Yaw, GetControlRotation().Roll));
	}
}

//In fixed mode, rotate camera 90 degrees clockwise
void APC::RotatePlayerClockwise()
{
	if(Fixed)
	controller->SetControlRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw + 90, GetControlRotation().Roll));
}

//In fixed mode, rotate camera 90 degrees anticlockwise
void APC::RotatePlayerAntiClockwise()
{
	if(Fixed)
	controller->SetControlRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw - 90, GetControlRotation().Roll));
}

//zoom in camera
void APC::ZoomIn()
{
	//if not at closest zoom, zoom out
	if (CameraBoom->TargetArmLength - zoomDif >= minArmLenght)
	{
		CameraBoom->TargetArmLength -= zoomDif;
	}
}

//zoom out camera
void APC::ZoomOut()
{
	//if not at furthest zoom, zoom out
	if (Fixed)
	{
		if (CameraBoom->TargetArmLength + zoomDif <= maxFixedArmLenght)
		{
			CameraBoom->TargetArmLength += zoomDif;
		}
	}
	else
	{
		if (CameraBoom->TargetArmLength + zoomDif <= maxArmLenght)
		{
			CameraBoom->TargetArmLength += zoomDif;
		}
	}
}

//get image of each object
UTexture2D* APC::getImg(int Index)
{
	AMachineObject* a = Cast<AMachineObject>(GetWorld()->SpawnActor(GameObjects[Index]));
	if (a == NULL)
	{
		//a->Destroy();
		return DefaultIMG;
	}
	else
	{
		UTexture2D* tempTex = a->OBJIMG;
		a->Destroy();
		return tempTex;
	}
}

int APC::getObjectChannel()
{
	return SelectedObject->linkChannel;
}

void APC::setObjectChannel(int Channel)
{
	if (SelectedObject != NULL)
	{
		SelectedObject->linkChannel = Channel;
		if (Channel == 0)
		{
			SelectedObject->linked = false;
		}
		else
		{
			SelectedObject->linked = true;
		}
	}
}

//Spawn object
void APC::Spawn(int index)
{
	//deselect current object
	if (SelectedObject != NULL)
	{
		SelectedObject->Select(false);
		SelectedObject = NULL;
		objSelected = false;
		Selected = false;
	}
	//Spawn selected object
	SelectedObject = Cast<AMachineObject>(GetWorld()->SpawnActor(GameObjects[index]));
	if (SelectedObject != NULL)
	{
		pickerOpen = false;
		SelectedObject->ObjectTypeIndex = index;
		SelectedObject->Select(true);
		SelectedPos = SelectedObject->position;
		objSelected = true;
		Selected = true;
		moving = true;
		FHitResult* hit = new FHitResult();
		controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel2, false, *hit);
		if (hit != nullptr)
		{
			SelectedObject->Move(hit->Location);
		}
		SelectedObject->Spawn();
		if (SelectedObject->Active == true)
		{
			AActivator* temp = Cast<AActivator>(SelectedObject);
			if (temp != NULL)
			{
				Activators.Add(temp);
			}
			else
			{
				ActiveObjects.Add(SelectedObject);
			}
		}
		else
		{
			StaticObjects.Add(SelectedObject);
		}
	}
}

void APC::Spawn(UObjectSave* inputObject) {

	//Spawn input object
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("object x:%f"), inputObject->objectPosition.X));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("object y:%f"), inputObject->objectPosition.Y));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("object z:%f"), inputObject->objectPosition.Z));

	AMachineObject* newObject = Cast<AMachineObject>(GetWorld()->SpawnActor(GameObjects[inputObject->objectIndex]));
	if (newObject != NULL)
	{
		//newObject->Spawn();
		newObject->SetActorLocation(inputObject->objectPosition);


		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("object x:%f"), newObject->GetActorLocation().X));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("object y:%f"), newObject->GetActorLocation().Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("object z:%f"), newObject->GetActorLocation().Z));

		newObject->SetActorRotation(inputObject->objectRotation);
		newObject->ObjectTypeIndex = inputObject->objectIndex;



		if (newObject->Active == true) {
			AActivator* temp = Cast<AActivator>(newObject);
			if (temp != NULL)
			{
				Activators.Add(temp);
			}
			else
			{
				ActiveObjects.Add(newObject);
			}
		}
		else {
			StaticObjects.Add(newObject);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("object x:%f"), newObject->GetActorLocation().X));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("object y:%f"), newObject->GetActorLocation().Y));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("object z:%f"), newObject->GetActorLocation().Z));
}

void APC::Load(int index) {
	class UWorldSave* loadingSave = SaveGames[index];

	StaticObjects.Empty();
	ActiveObjects.Empty();
	Activators.Empty();

	SelectedObject = NULL;

	if (loadingSave != nullptr) {
		for (int i = 0; i < loadingSave->SavedObjects.Num(); i++) {
			Spawn(loadingSave->SavedObjects[i]);
		}
		currentSave = index;
	}//if there is a save to load, take all saved objects and spawn objects in their postiion
	else {
		//error
	}
}

void APC::ClearObjects() {

	SelectedObject = NULL;
	objSelected = false;
	Selected = false;
	//need to reset selected obeject

	for (int i = 0; i < ActiveObjects.Num(); i++) {
		AMover* temp = Cast<AMover>(ActiveObjects[i]);
		if (temp != NULL)
		{
			temp->DestroyVehicle();
		}
		ActiveObjects[i]->Destroy();
		ActiveObjects[i] = NULL;
	}
	ActiveObjects.Empty();

	for (int i = 0; i < StaticObjects.Num(); i++) {
		StaticObjects[i]->Destroy();
		StaticObjects[i] = NULL;
	}
	StaticObjects.Empty();

	for (int i = 0; i < Activators.Num(); i++) {
		Activators[i]->Destroy();
		Activators[i] = NULL;
	}
	Activators.Empty();

}

void APC::Save() {
	UObjectSave* objPtr;

	SaveGames[currentSave]->SavedObjects.Empty();

	for (int i = 0; i < StaticObjects.Num(); i++) {
		objPtr = NewObject<class UObjectSave>();

		objPtr->objectPosition = StaticObjects[i]->GetActorLocation();
		objPtr->objectRotation = StaticObjects[i]->GetActorRotation();
		objPtr->objectIndex = StaticObjects[i]->ObjectTypeIndex;

		SaveGames[currentSave]->SavedObjects.Push(objPtr);
	}

	for (int i = 0; i < ActiveObjects.Num(); i++) {
		objPtr = NewObject<class UObjectSave>();

		objPtr->objectPosition = ActiveObjects[i]->GetActorLocation();
		objPtr->objectRotation = ActiveObjects[i]->GetActorRotation();
		objPtr->objectIndex = ActiveObjects[i]->ObjectTypeIndex;

		SaveGames[currentSave]->SavedObjects.Push(objPtr);
	}

	for (int i = 0; i < Activators.Num(); i++) {
		objPtr = NewObject<class UObjectSave>();

		objPtr->objectPosition = Activators[i]->GetActorLocation();
		objPtr->objectRotation = Activators[i]->GetActorRotation();
		objPtr->objectIndex = Activators[i]->ObjectTypeIndex;

		SaveGames[currentSave]->SavedObjects.Push(objPtr);
	}
}

void APC::NewSave() {

	SaveGames.Push(Cast<UWorldSave>(UGameplayStatics::CreateSaveGameObject(UWorldSave::StaticClass())));
	SaveGames.Last()->SaveName = FString::Printf(TEXT("save : %f"), SaveGames.Num());
	Load(SaveGames.Num() - 1);
}

void APC::NewSave(FString NewSaveName) {
	UWorldSave* tempSave = Cast<UWorldSave>(UGameplayStatics::CreateSaveGameObject(UWorldSave::StaticClass()));
	SaveGames.Add(tempSave);
	tempSave->SaveName = NewSaveName;
	Load(SaveGames.Num() - 1);
}

//Rotate object 90 degrees clockwise
void APC::RotateClockwise()
{
	if (SelectedObject != NULL)
	{
		SelectedObject->Rotate(true);
	}
}

//Rotate object 90 degrees anticlockwise
void APC::RotateAntiClockwise()
{
	if (SelectedObject != NULL)
	{
		SelectedObject->Rotate(false);
	}
}

//Delete currently selected object
void APC::DeleteObject()
{
	if (SelectedObject != NULL)
	{
		//Remove object from list
		for (int i = 0; i < ActiveObjects.Num(); i++)
		{
			if (SelectedObject == ActiveObjects[i])
			{
				ActiveObjects.RemoveAt(i,1,true);
			}
		}
		for (int i = 0; i < Activators.Num(); i++)
		{
			if (SelectedObject == Activators[i])
			{
				Activators.RemoveAt(i, 1, true);
			}
		}
		for (int i = 0; i < StaticObjects.Num(); i++)
		{
			if (SelectedObject == StaticObjects[i])
			{
				StaticObjects.RemoveAt(i, 1, true);
			}
		}
		//Delete object
		AMover* temp = Cast<AMover>(SelectedObject);
		if (temp != NULL)
		{
			temp->DestroyVehicle();
		}
		SelectedObject->Destroy();
		SelectedObject = NULL;
		objSelected = false;
		Selected = false;
	}
}

//Delete all objects in scene
void APC::ClearScene()
{
	if (!playing)
	{
		if (SelectedObject != NULL)
		{
			SelectedObject = NULL;
			objSelected = false;
			Selected = false;

		}
		for (int i = 0; i < ActiveObjects.Num(); i++)
		{
			ActiveObjects[i]->Destroy();
		}
		ActiveObjects.Empty();
		for (int i = 0; i < StaticObjects.Num(); i++)
		{
			StaticObjects[i]->Destroy();
		}
		StaticObjects.Empty();
	}
}

//Begin play mode
void APC::Play()
{
	for (int i = 0; i < Activators.Num(); i++)
	{
		if (Activators[i] != NULL)
		{
			if (Activators[i]->GetActorLocation().Y < -10000)
			{
				Activators[i]->Destroy();
				Activators.RemoveAt(i, 1, true);
			}
			else
			{
				Activators[i]->Activate();
				if (Activators[i]->linked)
				{
					Activators[i]->ControlledObjects.Empty();
					for (int j = 0; j < ActiveObjects.Num(); j++)
					{
						if (ActiveObjects[j]->linkChannel == Activators[i]->linkChannel)
						{
							Activators[i]->ControlledObjects.Add(ActiveObjects[j]);
						}
					}
				}
			}
		}
	}
	//Activate all non static objects
	for (int i = 0; i < ActiveObjects.Num(); i++)
	{
		if (ActiveObjects[i] != NULL)
		{
			if (ActiveObjects[i]->GetActorLocation().Y < -10000)
			{
				ActiveObjects[i]->Destroy();
				ActiveObjects.RemoveAt(i, 1, true);
			}
			else
			{
				ActiveObjects[i]->Activate();
			}
		}
	}
	//Deselect current object
	if (SelectedObject != NULL)
	{
		SelectedObject->Select(false);
		SelectedObject = NULL;
		objSelected = false;
		Selected = false;
	}
	playing = true;
	//Close object menu
	ObjectMenuOpen = false;
}

//Stop play mode
void APC::Stop()
{
	for (int i = 0; i < Activators.Num(); i++)
	{
		Activators[i]->Reset();
	}

	//Reset all active components
	for (int i = 0; i < ActiveObjects.Num(); i++)
	{
		ActiveObjects[i]->Reset();
	}
	playing = false;
}

//Toggle following active object in play mode
void APC::Follow()
{
	following = !following;
}

//
void APC::nextTarget()
{
	if (ActiveObjects.Num() > (tracked+1))
	{
		tracked++;
	}
	else
	{
		tracked = 0;
	}
}