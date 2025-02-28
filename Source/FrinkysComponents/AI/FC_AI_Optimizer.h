// Copyright Frinky

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FC_AI_Optimizer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FRINKYSCOMPONENTS_API UFC_AI_Optimizer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFC_AI_Optimizer();

	virtual void BeginPlay() override;
	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	

	float GetDistanceFromMainCamera();
	bool IsInCameraView();



	UFUNCTION(BlueprintCallable, Category = "AI")
	void ForceUpdate();

	// PROPERTYS

	UPROPERTY()
	ACharacter* OwningCharacter;

	UPROPERTY()
	APlayerCameraManager* CameraManager;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	float DistanceFromMainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxRenderDistance = 16000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MotionBlurDistance = 4000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DontOptimizeDistance = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bIsInCameraView = false;
};
