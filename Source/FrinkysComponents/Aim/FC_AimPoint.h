
// Copyright Frinky 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FC_AimPoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAimPointSelected);


UCLASS(Blueprintable, ClassGroup=(FRINKYCORE), meta=(BlueprintSpawnableComponent))
class FRINKYSCOMPONENTS_API UFC_AimPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFC_AimPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ToolTip="The priority of this aim point. The higher the number, the higher the priority."));
	int Priority = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AimDistance = 12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FOVChange = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SensitivityMultiplier = 1.0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Enabled = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool OverridesGunAimDistance = false;

	// -- DELEGATES

	UPROPERTY(BlueprintAssignable)
	FOnAimPointSelected OnAimPointSelectedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAimPointSelected OnAimPointDeselectedDelegate;
	

	


	// -- FUNCTIONS

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAimPointSelected();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAimPointDeselected();

	
};
