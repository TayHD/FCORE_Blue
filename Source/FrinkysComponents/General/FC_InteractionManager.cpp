// Fill out your copyright notice in the Description page of Project Settings.


#include "FC_InteractionManager.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFC_InteractionManager::UFC_InteractionManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFC_InteractionManager::TraceForInteractionPoints()
{
	const TArray<AActor*> IgnoreActors = TArray<AActor*>() = {OwningController->GetPawn(), GetOwner()};
	
	
	//trace for an interaction point using the GetTraceDirection function
	FVector TraceDirection;
	FVector TraceLocation;
	GetTraceDirection(TraceDirection, TraceLocation);

	FHitResult HitOut;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceLocation,
	                                                  TraceDirection * TraceDistance + TraceLocation, TraceChannel,
	                                                  bTraceComplex,
	                                                  IgnoreActors,
	                                                  TraceDebug, HitOut, true, FLinearColor::Blue,
	                                                  FLinearColor::Green);

	//if we hit something, check if it is an interaction point
	if (bHit)
	{
		UFC_InteractionPoint* InteractionPointHit = dynamic_cast<UFC_InteractionPoint*>(
			HitOut.GetComponent());
		LookingAtInteractionPoint = InteractionPointHit;
		if (!IsValid(LookingAtInteractionPoint))
		{
			StopInteracting();
		}
	}
	else
	{
		LookingAtInteractionPoint = nullptr;
		StopInteracting();
	}
}

// Called every frame
void UFC_InteractionManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!OwningController->IsLocalController())
	{
		PrimaryComponentTick.bCanEverTick = false;

		return;
	}

	if(!bEnabled)
	{
		InteractionTimer = 0;
		InteractionPoint = nullptr;
		bIsInteractionTimerActive = false;
		return;
	}
	
	if (bHandleTrace)
	{
		TraceForInteractionPoints();
	}

	

	if (bIsInteractionTimerActive && IsValid(InteractionPoint))
	{
		InteractionTimer += DeltaTime;
		InteractionTimer = FMath::Clamp(InteractionTimer, 0.0f, InteractionTime);
		if (InteractionTimer >= InteractionTime)
		{
			UFC_InteractionPoint *InteractionPointToInteract = InteractionPoint;
			if(InteractionPoint->StopInteractionOnInteractComplete == true)
			{
				InteractionPoint = nullptr;
			}
			ServerCallInteract(OwningController->GetPawn(), InteractionPointToInteract);
			InteractionPointToInteract->Interact(OwningController->GetPawn());

			bIsInteractionTimerActive = false;
		}
	}
}

void UFC_InteractionManager::BeginPlay()
{
	OwningController = dynamic_cast<APlayerController*>(GetOwner());
	Super::BeginPlay();
	if (IsValid(OwningController))
	{
		SetComponentTickEnabled(true);
		
	}
	else
	{
		SetComponentTickEnabled(false);
		UE_LOG(LogTemp, Warning, TEXT("Interaction Manager: Owning Controller is not valid, interaction manager must be on a playercontroller"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Interaction Manager: Owning Controller is not valid, interaction manager must be on a playercontroller")));
		
		
	}
}


void UFC_InteractionManager::SetInteractionPoint(UFC_InteractionPoint* NewInteractionPoint, bool bStartInteracting)
{
	if (CanBeInteractedWith(NewInteractionPoint))
	{
		InteractionPoint = NewInteractionPoint;
		if (bStartInteracting)
		{
			StartInteracting();
		}
	}
}

void UFC_InteractionManager::ServerCallInteract_Implementation(APawn* Interactor,
                                                               UFC_InteractionPoint* InInteractionPoint)
{
	if (IsValid(InInteractionPoint))
	{
		InInteractionPoint->ServerInteract(Interactor); // Call the interact function on the server
	}
}

void UFC_InteractionManager::ServerCallStopInteract_Implementation(APawn* Interactor,
                                                                   UFC_InteractionPoint* InInteractionPoint)
{
	if (IsValid(InInteractionPoint))
	{
		InInteractionPoint->ServerStopInteract(Interactor);
	}
}

void UFC_InteractionManager::StartInteracting()
{
	if (CanBeInteractedWith(InteractionPoint))
	{
		bIsInteractionTimerActive = true;
		InteractionTimer = 0;
		InteractionTime = InteractionPoint->InteractionTime;
	}
	else
	{
		if (CanBeInteractedWith(LookingAtInteractionPoint))
		{
			InteractionPoint = LookingAtInteractionPoint;
			bIsInteractionTimerActive = true;
			InteractionTimer = 0;
			InteractionTime = InteractionPoint->InteractionTime;
		}
	}
}

void UFC_InteractionManager::StopInteracting()
{
	if (InteractionPoint && InteractionTimer >= InteractionTime)
	{
		InteractionPoint->StopInteract(OwningController->GetPawn());
		ServerCallStopInteract(OwningController->GetPawn(), InteractionPoint);
	}
	bIsInteractionTimerActive = false;
	InteractionTimer = 0;
	InteractionTime = 0;
	InteractionPoint = nullptr;
}

float UFC_InteractionManager::GetInteractionProgress()
{
	return InteractionTimer / InteractionTime;
}

bool UFC_InteractionManager::CanBeInteractedWith(UFC_InteractionPoint* InInteractionPoint)
{
	if (!bEnabled)
	{
		return false;
	}

	
	if (IsValid(InInteractionPoint))
	{
		return InInteractionPoint->isEnabled && !Tags.HasAny(InInteractionPoint->BlockedTags) && Tags.HasAll(InInteractionPoint->RequiredTags);
	}
	return false;
}

void UFC_InteractionManager::GetTraceDirection_Implementation(FVector& TraceDirection, FVector& TraceStart)
{
	// get direction from control rotation
	TraceDirection = OwningController->GetControlRotation().Vector();
	if (IsValid(OwningController))
	{
		TraceStart = OwningController->PlayerCameraManager->GetCameraLocation();
	}
	else
	{
		TraceStart = OwningController->GetPawn()->GetPawnViewLocation();
	}
	return;
}
