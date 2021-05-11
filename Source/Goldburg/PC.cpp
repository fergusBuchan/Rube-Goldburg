// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"

#include "MachineObject.h"
#include <GameFramework\SpringArmComponent.h>
#include "Components/StaticMeshComponent.h"
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
#include "Misc/App.h"
#include "Volcano.h"
#include "DominoSet.h"
// Sets default values
APC::APC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.0f; 

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	MoveIMG = CreateDefaultSubobject<UStaticMeshComponent>("Move Button?");
	MoveIMG->SetVisibility(false);
	MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoveIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	LargeMoveIMG = CreateDefaultSubobject<UStaticMeshComponent>("Large Move Button?");
	LargeMoveIMG->SetVisibility(false);
	LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LargeMoveIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);
	
	LiftIMG = CreateDefaultSubobject<UStaticMeshComponent>("Lift Button");
	LiftIMG->SetVisibility(false);
	LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LiftIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	RotCIMG = CreateDefaultSubobject<UStaticMeshComponent>("Rot Clockwise Button");
	RotCIMG->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	RotCIMG->SetVisibility(false);
	RotCIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotCIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	RotACIMG = CreateDefaultSubobject<UStaticMeshComponent>("Rot Anti-Clockwise Button");
	RotACIMG->AttachToComponent(Camera,FAttachmentTransformRules::KeepRelativeTransform);
	RotACIMG->SetVisibility(false);
	RotACIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotACIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

	DuplicateIMG = CreateDefaultSubobject<UStaticMeshComponent>("dUPLICATE Button");
	DuplicateIMG->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	DuplicateIMG->SetVisibility(false);
	DuplicateIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DuplicateIMG->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

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

	TArray<AActor*> tempObjArray;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AMachineObject::StaticClass(), tempObjArray);
	for (int i = 0; i < tempObjArray.Num(); i++) {
		AddObject(Cast<AMachineObject>(tempObjArray[i]));
	}
	if (GetWorld()->GetName() == "DefaultSave1") {
		currentSave = "save 1";
	}
	if (GetWorld()->GetName() == "DefaultSave2") {
		currentSave = "save 2";
	}
	if (GetWorld()->GetName() == "DefaultSave3") {
		currentSave = "save 3";
	}
}

// Called every frame
void APC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    controller->GetInputTouchState(ETouchIndex::Touch1, NewTouch.X, NewTouch.Y, clicked);
	controller->GetInputTouchState(ETouchIndex::Touch2, NewTouch2.X, NewTouch2.Y, clicked2);

	VectorRight = Camera->GetRightVector();
	VectorUp = Camera->GetUpVector();
	if (SelectedObject != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("Z: %f"), SelectedObject->GetActorLocation().Z));
		SelectedZ = SelectedObject->GetActorLocation().Z;
	}
	if (clicked)
	{
		if (Selected && ((moving || lifting)||duplicating))
		{
			if (SelectedObject != NULL)
			{
				if (moving)
				{
					FHitResult* hit = new FHitResult();
					controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel2, false, *hit);
					if (hit != nullptr && hit->Normal == FVector(0, 0, 1))
					{
						FVector newloc = hit->Location - moveOffset;
						SelectedObject->Move(newloc);
					}
					else
					{
						SelectedObject->Move(SelectedObject->LastValidPos);
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
				if (clicked2) {//if the player has two fingers on the screen

					GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("crazy diamond")));

					FVector2D Delta1 = NewTouch - LastTouch;
					FVector2D Delta2 = NewTouch2 - LastTouch2;

					FVector2D TotalDelta = Delta1 + Delta2;

					if (TotalDelta.Size()*DeltaTime > 0.05) {
						if (TotalDelta.Size() < Delta1.Size()) {// if adding the vectors makes the resultant vector smaller, the vectors must be oppiste each other
							FVector2D NewDelta = NewTouch - NewTouch2;
							FVector2D LastDelta = LastTouch - LastTouch2;
							if (NewDelta.Size() > LastDelta.Size()) { // if the distance between the fingers is increaceing
								Zoom(TotalDelta.Size() * -2.0 * DeltaTime);
							}
							else { // the distance is decreacing
								Zoom(TotalDelta.Size() * 2.0 * DeltaTime);
							}
							GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("zoom")));

						}
						else {//otherwise we assume they want to move up/down
							FVector Xoffset = GetActorUpVector() * (TotalDelta.Y / 2);
							GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Orange, FString::Printf(TEXT("up/down")));
							SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + (DeltaTime * (TotalDelta.Y * 25))));
						}
					}
					LastTouch2 = NewTouch2;
				}
				else {
					FVector2D Delta = NewTouch - LastTouch;
					FVector Xoffset = GetActorRightVector() * -Delta.X; //FVector(DeltaTouch.X, 0.0f, 0.0f);
					AddActorWorldOffset(Xoffset);
					FVector Yoffset = GetActorForwardVector() * Delta.Y; //FVector(DeltaTouch.X, 0.0f, 0.0f);
					AddActorWorldOffset(Yoffset);

					if (GetActorLocation().X < minX)
					{
						SetActorLocation(FVector(minX, GetActorLocation().Y, GetActorLocation().Z));
					}
					if (GetActorLocation().X > maxX)
					{
						SetActorLocation(FVector(maxX, GetActorLocation().Y, GetActorLocation().Z));
					}
					if (GetActorLocation().Y < minY)
					{
						SetActorLocation(FVector(GetActorLocation().X, minY, GetActorLocation().Z));
					}
					if (GetActorLocation().Y > maxY)
					{
						SetActorLocation(FVector(GetActorLocation().X, maxY, GetActorLocation().Z));
					}
				}
			}
			LastTouch = NewTouch;
		}
		FHitResult Hit(ForceInit);
		//Dont make this an 'if' 
		controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel3, false, Hit);
		SelectedTemp2 = Cast<AMachineObject>(Hit.GetActor());
	}
	if (SelectedObject != NULL && !HideUI && !(SelectedObject->GetActorLocation().Z < 1000))
	{
		SelectedPos = SelectedObject->position;
		AVolcano* vol = Cast<AVolcano>(SelectedObject);
		if (vol != NULL)
		{
			LargeMoveIMG->SetVisibility(true);
			LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			LargeMoveIMG->SetWorldLocation(FVector(SelectedPos.X, SelectedPos.Y, 1021));//21 is just above current floor height
			MoveIMG->SetVisibility(false);
			MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else
		{
			MoveIMG->SetVisibility(true);
			MoveIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			MoveIMG->SetWorldLocation(FVector(SelectedPos.X, SelectedPos.Y, 1021));//21 is just above current floor height
			LargeMoveIMG->SetVisibility(false);
			LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		if (GetControlRotation().Pitch < 285 && GetControlRotation().Pitch > 255)
		{
			LiftIMG->SetVisibility(false);
			LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else
		{
			LiftIMG->SetVisibility(true);
			LiftIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		LiftIMG->SetWorldLocation(FVector(SelectedPos.X, SelectedPos.Y, SelectedPos.Z + SelectedObject->height));
		FVector diff = Camera->GetComponentLocation() - SelectedPos;
		diff *= FVector(1.0, 1.0, 0.0);
		diff.Normalize();
		FRotator temp = UKismetMathLibrary::MakeRotFromX(diff);
		LiftIMG->SetWorldRotation(FRotator(temp.Pitch, temp.Yaw + 90, temp.Roll));
		RotCIMG->SetVisibility(true);
		RotCIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		RotCIMG->SetWorldLocation(SelectedPos + (VectorRight * 70));
		RotACIMG->SetVisibility(true);
		RotACIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		RotACIMG->SetWorldLocation(SelectedPos + (VectorRight * -70));
		DuplicateIMG->SetVisibility(true); 
		DuplicateIMG->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		DuplicateIMG->SetWorldLocation(SelectedPos + (VectorRight * -70) + (VectorUp * SelectedObject->height));
		if (SelectedObject->Active)
		{
			isActive = true;
		}
		else
		{
			isActive = false;
		}
	}
	else
	{
		//SelectedPos = FVector(0, 0, 0);
		MoveIMG->SetVisibility(false);
		MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LargeMoveIMG->SetVisibility(false);
		LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LiftIMG->SetVisibility(false);
		LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RotCIMG->SetVisibility(false);
		RotCIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RotACIMG->SetVisibility(false);
		RotACIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DuplicateIMG->SetVisibility(false);
		DuplicateIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HideUI = false;
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
				if (Hit.Component == MoveIMG || Hit.Component == LargeMoveIMG)
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
					touchLoc = FVector(-100, -100, -100);
				}
				else if (Hit.Component == LiftIMG)
				{
					lifting = true;
					touchLoc = FVector(-100, -100, -100);
				}
				else if (Hit.Component == RotCIMG)
				{
					RotateClockwise();
					touchLoc = FVector(-100, -100, -100);
				}
				else if (Hit.Component == RotACIMG)
				{
					RotateAntiClockwise(); 
					touchLoc = FVector(-100, -100, -100);
				}
				else if (Hit.Component == DuplicateIMG)
				{
					duplicating = true;
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Duplicating start")));
				}
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
	if (FingerIndex == ETouchIndex::Touch2) {
		controller->GetInputTouchState(ETouchIndex::Touch2, LastTouch2.X, LastTouch2.Y, clicked2);
	}
}


void APC::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	clicked = false;
	moving = false;
	lifting = false;
	if (duplicating)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Duplicating stop")));
		if ((FVector::Dist(touchLoc, Location) < deselectDist))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Duplicating spawn")));
			Duplicate();
			duplicating = false;
		}
	}
	else
	{
		if ((SelectedTemp2 == SelectedTemp) && (SelectedTemp != NULL))
		{
			if (SelectedObject != SelectedTemp)
			{
				DeselectObject();
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
				DeselectObject();
			}
		}
	}
	SelectedTemp = nullptr;SelectedTemp2 = nullptr;
	//if not moved
	
}

void APC::DeselectObject()
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


void APC::MouseX(float value)
{
	if(!Fixed)
	AddControllerYawInput(value * StickSensitivity * GetWorld()->DeltaTimeSeconds);
}

void APC::MouseY(float value)
{
	if (!Fixed)
	AddControllerPitchInput(value * StickSensitivity * GetWorld()->DeltaTimeSeconds);
}

//Set player height
void APC::IncreaseHeight(bool rising)
{
	if (rising)
	{
		if ((GetActorLocation().Z + heightDelta) < maxHeight)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + heightDelta));
		}
		else
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, maxHeight));
		}
	}
	else
	{
		if ((GetActorLocation().Z - heightDelta) > minHeight)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - heightDelta));
		}
		else
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, minHeight));
		}
		
	}
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

void APC::Zoom(float zoomDist)
{
	if (Fixed) {
		if ((CameraBoom->TargetArmLength + zoomDist < maxFixedArmLenght) && (CameraBoom->TargetArmLength + zoomDist > minArmLenght)) {
			CameraBoom->TargetArmLength += zoomDist;
		}
	}
	else {
		if ((CameraBoom->TargetArmLength + zoomDist < maxArmLenght) && (CameraBoom->TargetArmLength + zoomDist > minArmLenght)) {
			CameraBoom->TargetArmLength += zoomDist;
		}
	}
	//zoom for use by pinch functions, allowing the player to zoom in more incrimental ammounts
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

int APC::getTabNumber(int Index)
{
	AMachineObject* a = Cast<AMachineObject>(GetWorld()->SpawnActor(GameObjects[Index]));
	if (a == NULL)
	{
		a->Destroy();
		return -1;
	}
	else
	{
		int number = a->TabNum;
		a->Destroy();
		return number;
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
	HideUI = true;

	MoveIMG->SetVisibility(false);
	MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LargeMoveIMG->SetVisibility(false);
	LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LiftIMG->SetVisibility(false);
	LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotCIMG->SetVisibility(false);
	RotCIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotACIMG->SetVisibility(false);
	RotACIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DuplicateIMG->SetVisibility(false);
	DuplicateIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DeselectObject();
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
	HideUI = true;
}

void APC::Duplicate()
{
	HideUI = true;
	
	MoveIMG->SetVisibility(false);
	MoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LargeMoveIMG->SetVisibility(false);
	LargeMoveIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LiftIMG->SetVisibility(false);
	LiftIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotCIMG->SetVisibility(false);
	RotCIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RotACIMG->SetVisibility(false);
	RotACIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DuplicateIMG->SetVisibility(false);
	DuplicateIMG->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	int index = SelectedObject->ObjectTypeIndex;
	FVector pos = SelectedObject->GetActorLocation();
	FRotator rot = SelectedObject->GetActorRotation();
	DeselectObject();

	
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
		//moving = true;
		//FHitResult* hit = new FHitResult();
		//controller->GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_GameTraceChannel2, false, *hit);
		//if (hit != nullptr)
		//{
		//	SelectedObject->Move(hit->Location);
		//}
		SelectedObject->Spawn();
		SelectedObject->SetActorLocation(pos);
		SelectedObject->SetActorRotation(rot);
		SelectedObject->LastValidPos = pos;
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
	HideUI = true;
}

void APC::Spawn(FSaveStruct inputObject) {

	//Spawn input object

	AMachineObject* newObject = Cast<AMachineObject>(GetWorld()->SpawnActor(GameObjects[inputObject.objectIndex]));
	if (newObject != NULL)
	{


		newObject->Spawn();
		newObject->SetActorLocation(inputObject.objectPosition);

		newObject->SetActorRotation(inputObject.objectRotation);
		newObject->ObjectTypeIndex = inputObject.objectIndex;
		newObject->linked = inputObject.linked;
		newObject->linkChannel = inputObject.linkChannel;


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
	// a spawn function for use by the load function 
}

void APC::AddObject(AMachineObject* InputPointer) {

	UClass* inputClass = InputPointer->GetClass();



	//Spawn input object

	if (InputPointer != NULL)
	{
		for (int i = 0; i < GameObjects.Num(); i++) {
			if (GameObjects[i] == inputClass) {
				InputPointer->ObjectTypeIndex = i;
			}
		}


		if (InputPointer->Active == true) {
			AActivator* temp = Cast<AActivator>(InputPointer);
			if (temp != NULL)
			{
				Activators.Add(temp);
			}
			else
			{
				ActiveObjects.Add(InputPointer);
				ADominoSet* temp2 = Cast<ADominoSet>(InputPointer);
				if (temp2 != NULL)
				{
					
					temp2->Spawn();
				}
			}
		}
		else {
			StaticObjects.Add(InputPointer);
		}
	}

	//function to add objects to the PC arrays. This is most helpful for the objects in pre - made saves
}

bool APC::Load(FString saveName) {

	SelectedObject->Select(false);
	//some weird bugs happen with the seleceted object
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Test")));
	ClearScene();
	if (UWorldSave* loadingSave = Cast<UWorldSave>(UGameplayStatics::LoadGameFromSlot(saveName, 0)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("load sucsessful")));

		loadingSave->SaveName = saveName;
		for (int i = 0; i < loadingSave->SavedObjects.Num(); i++) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("load object")));
			loadingSave->SaveName = saveName;
			Spawn(loadingSave->SavedObjects[i]);
		}
		// we go through the objects in the save and add them to the scene
		currentSave = saveName;
		return true;

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("load unsucsessful")));
		currentSave = saveName;
		return false;
	}

}
void APC::Save(FString saveName) {

	SelectedObject->Select(false);
	//some weird bugs happen with the seleceted object

	UWorldSave* savePtr = NewObject<class UWorldSave>();



	FSaveStruct objPtr;

	for (int i = 0; i < StaticObjects.Num(); i++) {

		objPtr.objectPosition = StaticObjects[i]->GetActorLocation();
		objPtr.objectRotation = StaticObjects[i]->GetActorRotation();
		objPtr.objectIndex = StaticObjects[i]->ObjectTypeIndex;
		objPtr.linked = StaticObjects[i]->linked;
		objPtr.linkChannel = StaticObjects[i]->linkChannel;

		savePtr->SavedObjects.Push(objPtr);
	}

	for (int i = 0; i < ActiveObjects.Num(); i++) {

		objPtr.objectPosition = ActiveObjects[i]->GetActorLocation();
		objPtr.objectRotation = ActiveObjects[i]->GetActorRotation();
		objPtr.objectIndex = ActiveObjects[i]->ObjectTypeIndex;
		objPtr.linked = ActiveObjects[i]->linked;
		objPtr.linkChannel = ActiveObjects[i]->linkChannel;

		savePtr->SavedObjects.Push(objPtr);
	}

	for (int i = 0; i < Activators.Num(); i++) {

		objPtr.objectPosition = Activators[i]->GetActorLocation();
		objPtr.objectRotation = Activators[i]->GetActorRotation();
		objPtr.objectIndex = Activators[i]->ObjectTypeIndex;
		objPtr.linked = Activators[i]->linked;
		objPtr.linkChannel = Activators[i]->linkChannel;

		savePtr->SavedObjects.Push(objPtr);
	}

	//get the poisions of the objects in the scene and add them to a save object

	if (UGameplayStatics::SaveGameToSlot(savePtr, saveName, 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("save sucsessful")));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("save failed")));
	}

	//create a save on the player's computer
	
}


void APC::DeleteSave(FString saveName) {
	UGameplayStatics::DeleteGameInSlot(saveName,0);
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
		ADominoSet* temp = Cast<ADominoSet>(SelectedObject);
		if (temp != NULL)
		{
			temp->DestroyDominoes();
		}
		SelectedObject->Destroy();
		DeselectObject();
	}
}

//Delete all objects in scene
void APC::ClearScene()
{
	if (!playing)
	{
		DeselectObject();
		for (int i = 0; i < Activators.Num(); i++)
		{
			Activators[i]->Destroy();
		}
		Activators.Empty();
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
	DeselectObject();
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