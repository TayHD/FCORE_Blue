// Copyright Frinky 2022

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/Object.h"
#include "FC_Seat.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSit, APawn*, Pawn);

// Multicast for movement inputs
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMove, float, Input);

UCLASS(ClassGroup=(FRINKYCORE), meta=(BlueprintSpawnableComponent))
class FRINKYSCOMPONENTS_API UFC_Seat : public USceneComponent
{
	GENERATED_BODY()

public:
	UFC_Seat();

protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeComponent() override;

	virtual void OnComponentCreated() override;


public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//variables
	UPROPERTY()
	USkeletalMeshComponent* DebugMeshComponent;

	UPROPERTY()
	USkeletalMeshComponent* PreviewEjectMeshComponent;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	UAnimSequence* Pose;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	USkeletalMesh* PreviewMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	FRotator PreviewRotation = FRotator(0.f, -90, 0.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	FVector PreviewLocation = FVector(0.f, 0.f, -96.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	bool bEnablePreviews = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	FVector ExitPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	FVector PawnOffset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	float MaxViewPitch = 90.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	float MinViewPitch = -90.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	float MaxViewYaw = 90.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	float MinViewYaw = -90.f;

	UPROPERTY()
	float SavedMaxViewPitch = 90.f;

	UPROPERTY()
	float SavedMinViewPitch = -90.f;

	UPROPERTY()
	float SavedMaxViewYaw = 90.f;

	UPROPERTY()
	float SavedMinViewYaw = -90.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Settings")
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttachedPawn)
	APawn* AttachedPawn;

	// FUNCTIONS

	UFUNCTION()
	virtual void OnRep_AttachedPawn();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category="Seat")
	virtual void Sit(APawn* Pawn);

	UFUNCTION(NetMulticast, Reliable, Category="Seat")
	virtual void SitMulti(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category="Seat")
	virtual  void Eject();
	
	UFUNCTION(NetMulticast, Reliable, Category="Seat")
	virtual  void EjectMulti();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Seat")
	bool IsPawnSeated();

	UFUNCTION(BlueprintCallable, Category="Seat")
	void AddForwardInput(float Value);

	UFUNCTION(BlueprintCallable, Category="Seat")
	void AddRightInput(float Value);

	UPROPERTY(BlueprintAssignable, meta=(ToolTip="When something attaches to any slot"))
	FOnSit OnSit;

	UPROPERTY(BlueprintAssignable, meta=(ToolTip="When something attaches to any slot"))
	FOnSit OnEject;

	UPROPERTY(BlueprintAssignable, meta=(ToolTip="When you apply a right movement input"))
	FOnMove OnRightInput;

	UPROPERTY(BlueprintAssignable, meta=(ToolTip="When you apply a forward movement input"))
	FOnMove OnForwardInput;
	
	

};
