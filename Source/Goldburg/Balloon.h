

#pragma once

#include "CoreMinimal.h"
#include "MachineObject.h"
#include "Balloon.generated.h"

/**
 * 
 */
UCLASS()
class GOLDBURG_API ABalloon : public AMachineObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Balloon;



	//UPROPERTY(EditAnywhere)
		//class UBoxComponent* ActivatorBox;

	UPROPERTY(BlueprintReadWrite)
		bool playing;
	UPROPERTY(BlueprintReadWrite)
		float animSpeed;
	UPROPERTY(EditAnywhere)
		float LifeTime;
	float timer;
	bool launched;

	ABalloon();
	void Tick(float DeltaTime) override;
	void Launch() override;
	void Reset() override;
	//UFUNCTION()
		//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		class USphereComponent* BalloonBall;
	UPROPERTY(EditAnywhere)
		float ScaleRate;
	UPROPERTY(EditAnywhere)
		float LiftRate;

	UPROPERTY(EditAnywhere)
		float MaxScale;
	UPROPERTY(EditAnywhere)
		float MaxLift;

	UPROPERTY(EditAnywhere)
		float sphereResetScale;


	UPROPERTY(EditAnywhere)
		float rayUp;
};
