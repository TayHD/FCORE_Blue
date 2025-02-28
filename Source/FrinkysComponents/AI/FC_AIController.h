// Copyright Frinky 2022

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "FC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class FRINKYSCOMPONENTS_API AFC_AIController : public AAIController
{
	GENERATED_BODY()

	
	
public:
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RemoveFromCrowd();

	virtual FVector GetFocalPointOnActor(const AActor* Actor) const override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	FVector GetFocalPointOnActorBP(const AActor* Actor) const { return GetFocalPointOnActor(Actor); }

	AFC_AIController(const FObjectInitializer& ObjectInitializer);

	// PROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|FComp")
	float AimInterp = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|FComp")
	FName AimAt = "head";
	

	
};
