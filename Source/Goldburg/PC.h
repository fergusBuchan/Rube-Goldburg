// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectSave.h"
#include "WorldSave.h"
#include "GameFramework/Character.h"
#include "PC.generated.h"

UCLASS()
class GOLDBURG_API APC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly)
	bool HideUI;

	UPROPERTY(BlueprintReadOnly)
		float SelectedZ;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MoveIMG;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* LargeMoveIMG;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* LiftIMG;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* RotCIMG;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* RotACIMG;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DuplicateIMG;
	
	APlayerController* controller;

	


	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION(BlueprintCallable)
		void DeselectObject();

	//Player Controls
	void MouseX(float value);
	void MouseY(float value);
	UFUNCTION(BlueprintCallable)
		void SetFixed();
	UFUNCTION(BlueprintCallable)
		void RotatePlayerClockwise();
	UFUNCTION(BlueprintCallable)
		void RotatePlayerAntiClockwise();
	UFUNCTION(BlueprintCallable)
		void ZoomIn();
	UFUNCTION(BlueprintCallable)
		void ZoomOut();
	UFUNCTION()
		void Zoom(float ZoomDist);

	UFUNCTION(BlueprintCallable)
		void IncreaseHeight(bool rising);
	UPROPERTY(EditAnywhere)
		float maxHeight;
	UPROPERTY(EditAnywhere)
		float minHeight;
	UPROPERTY(EditAnywhere)
		float heightDelta;
	
	UPROPERTY(EditAnywhere)
		float minX;
	UPROPERTY(EditAnywhere)
		float minY;
	UPROPERTY(EditAnywhere)
		float maxX;
	UPROPERTY(EditAnywhere)
		float maxY;



	UFUNCTION(BlueprintCallable)
		void Follow();
	UFUNCTION(BlueprintCallable)
		void nextTarget();
	UFUNCTION(BlueprintCallable)
		void Play();
	UFUNCTION(BlueprintCallable)
		void Stop();
	UFUNCTION(BlueprintCallable)
		void ClearScene();

	UFUNCTION(BlueprintCallable)
		void Spawn(int index);
	void Duplicate();
		void Spawn(FSaveStruct inputObject);



	UFUNCTION(BlueprintCallable)
		void RotateClockwise();
	UFUNCTION(BlueprintCallable)
		void RotateAntiClockwise();
	UFUNCTION(BlueprintCallable)
		void DeleteObject();


	UPROPERTY(EditAnywhere)
		float deselectDist;

	FVector touchLoc;

	UPROPERTY(EditAnywhere)
		float Speed;
	UPROPERTY(EditAnywhere)
		float StickSensitivity;
	UPROPERTY(EditAnywhere)
		float StartingOffset;
	UPROPERTY(EditAnywhere)
		float minPitch;
	UPROPERTY(EditAnywhere)
		float minArmLenght;
	UPROPERTY(EditAnywhere)
		float maxArmLenght;
	UPROPERTY(EditAnywhere)
		float maxFixedArmLenght;
	UPROPERTY(EditAnywhere)
		float zoomDif;

	

	bool clicked;
	bool clicked2;

	UPROPERTY(BlueprintReadWrite)
		bool ObjectMenuOpen;

	UPROPERTY(BlueprintReadOnly)
		bool Fixed;


	FVector2D LastTouch;
	FVector2D NewTouch;
	FVector2D LastTouch2;
	FVector2D NewTouch2;

	

	
	UPROPERTY(EditAnywhere)
		UTexture2D* DefaultIMG;
	UFUNCTION(BlueprintCallable)
		UTexture2D* getImg(int Index);
	UFUNCTION(BlueprintCallable)
		int getTabNumber(int index);

		void Spawn(UObjectSave inputObject);

	UFUNCTION(BlueprintCallable)
		int getObjectChannel();
	UFUNCTION(BlueprintCallable)
		void setObjectChannel(int Channel);
	
	UPROPERTY(BlueprintReadWrite)
		bool pickerOpen;
	

	
	//Pointer to currently selected object
	UPROPERTY(EditAnywhere, Transient)
		class AMachineObject* SelectedObject;
		class AMachineObject* SelectedTemp;
		class AMachineObject* SelectedTemp2;
		//Array of objects player can spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf< AMachineObject>> GameObjects;
	//Array of pointers to objects to be activated on play
	UPROPERTY(EditAnywhere, Transient)
		TArray<class AMachineObject*> ActiveObjects;
	UPROPERTY(EditAnywhere, Transient)
		TArray<class AActivator*> Activators;
	//Array of pointers to static objects in the scene
	UPROPERTY(EditAnywhere, Transient)
		TArray<class AMachineObject*> StaticObjects;

	

	
	
	UPROPERTY(BlueprintReadOnly)
		bool playing;
	bool follow;
	bool duplicating;
	
	UPROPERTY(BlueprintReadWrite)
		bool objSelected;
	UPROPERTY(BlueprintReadOnly)
		bool isActive;
	    bool Selected;

	bool lifting;
	bool moving;
	FVector moveOffset;

	UPROPERTY(BlueprintReadOnly)
		FVector SelectedPos;

	UPROPERTY(BlueprintReadOnly)
		FVector VectorRight;
	UPROPERTY(BlueprintReadOnly)
		FVector VectorUp;

	
	UPROPERTY(BlueprintReadOnly)
	bool following;
	int tracked;


	UPROPERTY(BlueprintReadWrite)
		FString currentSave;
	UFUNCTION(BlueprintCallable)
		void Load(FString saveName);
	UFUNCTION(BlueprintCallable)
		void Save(FString saveName);
	UFUNCTION(BlueprintCallable)
		void DeleteSave(FString saveName);
	


	UPROPERTY(BlueprintReadWrite)
		float musicVolume;
	UPROPERTY(BlueprintReadWrite)
		float SFXVolume;
};
