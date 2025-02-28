// Copyright Frinky


#include "FC_AI_Optimizer.h"

#include "FrinkysComponents/General/FC_Functions.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <DrawDebugHelpers.h>


UFC_AI_Optimizer::UFC_AI_Optimizer()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UFC_AI_Optimizer::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = dynamic_cast<ACharacter*>(GetOwner());
	CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	if(!OwningCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, TEXT("AI Optimizer not attached to Character!"));
	}
	
	
}


void UFC_AI_Optimizer::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DistanceFromMainCamera = GetDistanceFromMainCamera();
	bIsInCameraView = IsInCameraView();

	

	if(!OwningCharacter)
	{
		return;
	}

	float TickRate = 0.0f;

	if(DistanceFromMainCamera > DontOptimizeDistance)
	{
		// Lerp tick rate based on distance
		TickRate = FMath::Lerp(0.0f, 0.1f, DistanceFromMainCamera / MaxRenderDistance);
		
		if(!bIsInCameraView)
		{
			TickRate = TickRate * 4;
		}

		if(TickRate < 0.01)
		{
			TickRate = 0.0;
		}
	}
	
	
	OwningCharacter->GetCharacterMovement()->SetComponentTickInterval(TickRate);
	OwningCharacter->GetMesh()->SetComponentTickInterval(TickRate);

	if(DistanceFromMainCamera < MotionBlurDistance)
	{
		OwningCharacter->GetMesh()->bPerBoneMotionBlur = true;
	}
	else
	{
		OwningCharacter->GetMesh()->bPerBoneMotionBlur = false;

	}



	if(bDebug)
	{
		
		// Blend color based on distance
		FColor Color = FColor::MakeRedToGreenColorFromScalar(DistanceFromMainCamera / MaxRenderDistance);
		if(DistanceFromMainCamera < DontOptimizeDistance)
		{
			Color = FColor::White;
		}
		// 
		DrawDebugBox(GetWorld(), OwningCharacter->GetActorLocation(), FVector(50, 50, 50), Color ,false, DeltaTime);

		GEngine->AddOnScreenDebugMessage(-1, DeltaTime, Color, FString::SanitizeFloat(TickRate));

	}
	

}

float UFC_AI_Optimizer::GetDistanceFromMainCamera()
{
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector OurLocation = GetOwner()->GetActorLocation();

	return FVector::Dist(CameraLocation, OurLocation);
}

bool UFC_AI_Optimizer::IsInCameraView()
{
	return UFC_Functions::IsInFrustum(OwningCharacter);
}

void UFC_AI_Optimizer::ForceUpdate()
{
	TickComponent(0, ELevelTick::LEVELTICK_All, nullptr);
}
