// Copyright Frinky 2022


#include "FC_Functions.h"

#include "EngineUtils.h"
#include "FC_GunComponent.h"
#include "FrinkysComponents/Inventory/FC_InventoryComponent.h"
#include "FrinkysComponents/Inventory/FC_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include <DrawDebugHelpers.h>

#include "AudioDevice.h"
#include "AudioMixerDevice.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/InputSettings.h"


UFC_HealthComponent* UFC_Functions::GetHealthComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_HealthComponent>();
	}
	return nullptr;}

UFC_ItemComponent* UFC_Functions::GetItemComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_ItemComponent>();
	}
	return nullptr;
}

UFC_InventoryComponent* UFC_Functions::GetInventoryComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_InventoryComponent>();
	}
	return nullptr;
}

UFC_GenericAttachable* UFC_Functions::GetGenericAttachable(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_GenericAttachable>();
	}
	return nullptr;
}

UFC_GenericAttachableHandler* UFC_Functions::GetGenericAttachableHandler(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_GenericAttachableHandler>();
	}
	return nullptr;
}

UFC_EquipmentComponent* UFC_Functions::GetEquipmentComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_EquipmentComponent>();
	}
	return nullptr;
}

UFC_EquipmentHandlerComponent* UFC_Functions::GetEquipmentHandler(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_EquipmentHandlerComponent>();
	}
	return nullptr;
}
UFC_GunComponent* UFC_Functions::GetGunComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_GunComponent>();
	}
	return nullptr;
}

UFC_ArmourComponent* UFC_Functions::GetArmourComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_ArmourComponent>();
	}
	return nullptr;
}

UFC_ArmourHandlerComponent* UFC_Functions::GetArmourHandlerComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_ArmourHandlerComponent>();
	}
	return nullptr;
}

UFC_InteractionManager* UFC_Functions::GetInteractionManagerComponent(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_InteractionManager>();
	}
	return nullptr;
}

UFC_Seat* UFC_Functions::GetActorSeat(AActor* Actor)
{
	if(!IsValid(Actor)) { return nullptr; }
	if(!IsValid(Actor->GetRootComponent())) { return nullptr; }
	
	UFC_Seat* Seat = dynamic_cast<UFC_Seat*>(Actor->GetRootComponent()->GetAttachParent());
	if(Seat)
	{
		return Seat;
		
	}
	return nullptr;
}



UFC_EquipmentComponent* UFC_Functions::GetHeld(AActor* Actor)
{
	if(!Actor)
	{
		return nullptr; // No Actor
	}
	UFC_EquipmentHandlerComponent* Handler =  Actor->FindComponentByClass<UFC_EquipmentHandlerComponent>();
	if(!Handler)
	{
		return nullptr; // No Handler
	}
	return Handler->GetHeld();
	
}

AActor* UFC_Functions::GetHeldActor(AActor* Actor)
{
	if(!Actor)
	{
		return nullptr; // No Actor
	}
	UFC_EquipmentHandlerComponent* Handler =  Actor->FindComponentByClass<UFC_EquipmentHandlerComponent>();
	if(!Handler)
	{
		return nullptr; // No Handler
	}
	return Handler->GetHeldActor();
	
	
}

UFC_GunComponent* UFC_Functions::GetHeldGunComponent(AActor* Actor)
{
	AActor* HeldActor;
	HeldActor = GetHeldActor(Actor);

	if(HeldActor)
	{
		return HeldActor->FindComponentByClass<UFC_GunComponent>();
	}
	return nullptr;
	

	
}

UFC_ActionManager* UFC_Functions::GetActionManager(AActor* Actor)
{
	if(!Actor)
	{
		return nullptr; // No Actor
	}

	return Actor->FindComponentByClass<UFC_ActionManager>();
}


UFC_AimHandler* UFC_Functions::GetAimHandler(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_AimHandler>();
	}
	return nullptr;
}

UFC_Barrel* UFC_Functions::GetBarrel(AActor* Actor)
{
	if(Actor)
	{
		return Actor->FindComponentByClass<UFC_Barrel>();
	}
	return nullptr;
}

float UFC_Functions::GetHealth(AActor* Actor)
{
	if(!Actor)
	{
		return -1; // No Actor
	}
	UFC_HealthComponent* HealthComp =  Actor->FindComponentByClass<UFC_HealthComponent>();
	if(!HealthComp)
	{
		return -1; // No Handler
	}
	return HealthComp->Health;
	
}

float UFC_Functions::Invert(float in)
{
	return in*-1;
}

float UFC_Functions::GetDirectionToTargetDotProduct(FVector Origin, FVector Direction, FVector Target)
{
	FVector ToTarget = Target - Origin;
	ToTarget.Normalize();

	// Calculate the dot product of the direction vector and the vector pointing to the target
	float DotProduct = FVector::DotProduct(Direction, ToTarget);

	// Return the dot product
	return DotProduct;
}

void UFC_Functions::GetNumberOfAliveOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> Class, TArray<AActor*>& OutActors)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World, Class); It; ++It)
		{
			AActor* AliveActor = *It;

			if (IsValid(AliveActor))
			{
				UFC_HealthComponent* HealthComponent = AliveActor->FindComponentByClass<UFC_HealthComponent>();
				if (IsValid(HealthComponent) && HealthComponent->IsAlive())
				{
					OutActors.Add(AliveActor);
				}
			}
		}
	}
}

int32 UFC_Functions::GetClosestRotationIndex(FRotator TargetRotation, const TArray<FRotator>& RotationsArray)
{
	int32 Index = 0;
	float DeltaAngle = FLT_MAX;

	for (int32 i = 0; i < RotationsArray.Num(); i++)
	{
		float TempDelta = FQuat::Error(TargetRotation.Quaternion(), RotationsArray[i].Quaternion());

		if (DeltaAngle > TempDelta)
		{
			DeltaAngle = TempDelta;
			Index = i;
		}
	}

	return Index;
}

float UFC_Functions::GetAngularDistanceBetweenRotators(FRotator Rotator1, FRotator Rotator2)
{
    float AngularDistance = FQuat::Error(Rotator1.Quaternion(), Rotator2.Quaternion());
    return AngularDistance;
}



FVector UFC_Functions::ClosestPointOnLine(const FVector& LineStart, const FVector& LineEnd, const FVector& Point)
{
	FVector LineVector = LineEnd - LineStart;
	FVector PointVector = Point - LineStart;


	float LineLengthSquared = FVector::DotProduct(LineVector, LineVector);

	if (LineLengthSquared == 0.0f)
	{
		return LineStart;
	}

	float t = FMath::Max(0.0f, FMath::Min(1.0f, FVector::DotProduct(PointVector, LineVector) / LineLengthSquared));

	return LineStart + LineVector * t;
}

bool UFC_Functions::IsLinePointingAtPoint(const FVector& LineStart, const FVector& LineEnd, const FVector& Point)
{
	FVector LineVector = LineEnd - LineStart;
	FVector PointVector = Point - LineStart;

	// Check if the line of fire is pointing towards the player
	if (FVector::DotProduct(LineVector, PointVector) < 0.0f)
	{
		return false;
	}
	
	return true;
}

float UFC_Functions::OneMinus(float Value)
{
	return 1 - Value;
}

FString UFC_Functions::RoundValueToDigits(int value, int digits)
{
	FString result = FString::Printf(TEXT("%0*d"), digits, value);
	return result;
}

float UFC_Functions::GetFPS()
{
	//return 
	return 1 / UGameplayStatics::GetWorldDeltaSeconds(GEngine->GetWorld());
	
}



void UFC_Functions::GetAllActorsWithComponent(const UObject* WorldContextObject,
	TSubclassOf<UActorComponent> ComponentClass, TArray<AActor*>& OutActors)
{
	OutActors.Reset();

	if(!ComponentClass)
	{
		return;
	}
	
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			
			UActorComponent* Component = Actor->FindComponentByClass(ComponentClass);
			if (IsValid(Component))
			{
				OutActors.Add(Actor);
			}
		}
	}
}

void UFC_Functions::GetAllActorsWithinRadius(const UObject* WorldContextObject, const FVector Origin, float Radius,
	TArray<AActor*>& OutActors)
{
	OutActors.Reset();

	if(Radius <= 0) // Radius is 0 or less, theres no point in doing anything
	{
		return;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			FVector ActorLocation = Actor->GetActorLocation();

			if(FVector::Dist(Origin, ActorLocation) <= Radius)
			{
				OutActors.Add(Actor);
			}
		}
	}
}

void UFC_Functions::GetAllActorsOfClassWithinRadius(const UObject* WorldContextObject, const FVector Origin,
	float Radius, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors)
{
	// Clear the output array
	OutActors.Reset();

	if (Radius <= 0)
	{
		return;
	}

	if (!ActorClass)
	{
		return;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* Actor = *It;
			FVector ActorLocation = Actor->GetActorLocation();

			if(FVector::Dist(Origin, ActorLocation) <= Radius)
			{
				OutActors.Add(Actor);
			}
		}
	}
	
}

void UFC_Functions::GetAllActorsWithinRadiusWithComponent(const UObject* WorldContextObject, const FVector Origin,
                                                          float Radius, TSubclassOf<UActorComponent> ComponentClass, TArray<AActor*>& OutActors)
{
	OutActors.Reset();

	if(Radius <= 0)
	{
		return;
	}

	if(!ComponentClass)
	{
		return;
	}


	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			FVector ActorLocation = Actor->GetActorLocation();
			UActorComponent* ActorComponent = Actor->FindComponentByClass(ComponentClass);

			if(FVector::Dist(Origin, ActorLocation) <= Radius)
			{
				if(IsValid(ActorComponent))
				{
					OutActors.Add(Actor);
				}
			}
		}
	}
}

void UFC_Functions::GetAllActorsOfClassWithinBounds(const UObject* WorldContextObject, const FVector Origin,
	const FVector Extent, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors)
{
	OutActors.Reset();

	if (!ActorClass)
	{
		return;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* Actor = *It;
			FVector ActorLocation = Actor->GetActorLocation();

			if (IsPointInExtent(ActorLocation, Origin, Extent))
			{
				OutActors.Add(Actor);
			}
		}
	}
}


bool UFC_Functions::IsInFrustum(AActor* Actor)
{
	ULocalPlayer* LocalPlayer = Actor->GetWorld()->GetFirstLocalPlayerFromController();
	if (LocalPlayer != nullptr && LocalPlayer->ViewportClient != nullptr && LocalPlayer->ViewportClient->Viewport)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		  LocalPlayer->ViewportClient->Viewport,
		  Actor->GetWorld()->Scene,
		  LocalPlayer->ViewportClient->EngineShowFlags)
		  .SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, LocalPlayer->ViewportClient->Viewport);
		if (SceneView != nullptr)
		{
			return SceneView->ViewFrustum.IntersectSphere(Actor->GetActorLocation(), Actor->GetSimpleCollisionRadius());
		}
	}
	return false;
}

int UFC_Functions::HashInts(int A, int B)
{
	return HashCombine(A, B);
}

bool UFC_Functions::IsPointInExtent(const FVector& Point,const FVector& Origin, const FVector& Extent)
{
	return UKismetMathLibrary::IsPointInBox(Point, Origin, Extent);
}

bool UFC_Functions::DoExtentsOverlap(const FVector& Extent1, const FVector& Origin1, const FVector& Extent2, const FVector& Origin2)
{
	// Calculate the min and max of the first box
	FVector Min1 = Origin1 - Extent1;
	FVector Max1 = Origin1 + Extent1;

	// Calculate the min and max of the second box
	FVector Min2 = Origin2 - Extent2;
	FVector Max2 = Origin2 + Extent2;

	// Return whether the boxes overlap
	return !(Min1.X > Max2.X || Min2.X > Max1.X || Min1.Y > Max2.Y || Min2.Y > Max1.Y || Min1.Z > Max2.Z || Min2.Z > Max1.Z);
}

bool UFC_Functions::DoesActorOverlapComponentExtent(AActor* Actor, UPrimitiveComponent* Component)
{
	if(!IsValid(Actor) || !IsValid(Component))
	{
		return false;
	}

	FVector ActorExtent = Actor->GetSimpleCollisionCylinderExtent();
	FVector ActorOrigin = Actor->GetActorLocation();

	FVector ComponentExtent = Component->Bounds.BoxExtent;
	FVector ComponentOrigin = Component->GetComponentLocation();

	return DoExtentsOverlap(ActorExtent, ActorOrigin, ComponentExtent, ComponentOrigin);
}

void UFC_Functions::TeleportComponent(UPrimitiveComponent* Component, const FVector& Location, const FRotator& Rotation)
{
	Component->SetWorldLocationAndRotation(Location, Rotation, false, nullptr, ETeleportType::TeleportPhysics);
}

FString UFC_Functions::ChopWordOffString(FString in, FString separator)
{
	// Chop off the last word (separate by separator)	
	int32 lastSeparatorIndex = 0;
	bool found = in.FindLastChar(separator[0], lastSeparatorIndex);
    
	if (found)
	{
		return in.Left(lastSeparatorIndex) + separator;
	}
	else
	{
		return FString(); // Return an empty string when there's no separator
	}
}



FString UFC_Functions::FindClosestString(FString in, TArray<FString> Strings)
{
	FString BestMatch;
	int32 BestMatchLength = 0;

	for (const FString& Str : Strings)
	{
		int32 MatchLength = 0;

		for (int32 i = 0; i < FMath::Min(in.Len(), Str.Len()); ++i)
		{
			if (in[i] == Str[i])
			{
				++MatchLength;
			}
			else
			{
				break;
			}
		}

		if (MatchLength > BestMatchLength)
		{
			BestMatch = Str;
			BestMatchLength = MatchLength;
		}
		else if (MatchLength == BestMatchLength && MatchLength > 0)
		{
			// If there's a tie, choose the lexicographically smaller string
			if (Str < BestMatch)
			{
				BestMatch = Str;
			}
		}
	}

	return BestMatch;
}

void UFC_Functions::CalculateScreenSpaceRectangle(AActor* Target, FVector2D& ScreenPosition, FVector2D& ScreenSize)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("Target is null"));
		return;
	}

	// Get the actor's bounding box
	FBox BoundingBox = Target->GetComponentsBoundingBox();

	// Get the player controller and viewport size
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Target->GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	// Project the bounding box's corners to screen space
	TArray<FVector> Corners;
	Corners.Reserve(8);
	Corners.Add(BoundingBox.Min);
	Corners.Add(FVector(BoundingBox.Min.X, BoundingBox.Min.Y, BoundingBox.Max.Z));
	Corners.Add(FVector(BoundingBox.Min.X, BoundingBox.Max.Y, BoundingBox.Min.Z));
	Corners.Add(FVector(BoundingBox.Min.X, BoundingBox.Max.Y, BoundingBox.Max.Z));
	Corners.Add(FVector(BoundingBox.Max.X, BoundingBox.Min.Y, BoundingBox.Min.Z));
	Corners.Add(FVector(BoundingBox.Max.X, BoundingBox.Min.Y, BoundingBox.Max.Z));
	Corners.Add(FVector(BoundingBox.Max.X, BoundingBox.Max.Y, BoundingBox.Min.Z));
	Corners.Add(BoundingBox.Max);

	FVector2D MinScreenCoords = FVector2D(FLT_MAX, FLT_MAX);
	FVector2D MaxScreenCoords = FVector2D(-FLT_MAX, -FLT_MAX);

	for (const FVector& Corner : Corners)
	{
		FVector2D ScreenCoords;
		PlayerController->ProjectWorldLocationToScreen(Corner, ScreenCoords);

		MinScreenCoords.X = FMath::Min(MinScreenCoords.X, ScreenCoords.X);
		MinScreenCoords.Y = FMath::Min(MinScreenCoords.Y, ScreenCoords.Y);
		MaxScreenCoords.X = FMath::Max(MaxScreenCoords.X, ScreenCoords.X);
		MaxScreenCoords.Y = FMath::Max(MaxScreenCoords.Y, ScreenCoords.Y);
	}

	// Calculate the screen position and size based on the minimum and maximum coordinates
	ScreenPosition = MinScreenCoords;
	ScreenSize = MaxScreenCoords - MinScreenCoords;

	// Clamp the screen position and size to the viewport size
	ScreenPosition.X = FMath::Clamp(ScreenPosition.X, 0.0f, ViewportSize.X);
	ScreenPosition.Y = FMath::Clamp(ScreenPosition.Y, 0.0f, ViewportSize.Y);
	ScreenSize.X = FMath::Clamp(ScreenSize.X, 0.0f, ViewportSize.X - ScreenPosition.X);
	ScreenSize.Y = FMath::Clamp(ScreenSize.Y, 0.0f, ViewportSize.Y - ScreenPosition.Y);
}

FVector UFC_Functions::GetClosestPointFromBounds(AActor* Target, FVector Origin)
{
	if (!Target) return FVector::ZeroVector;

	// Step 1: Get the target actor's bounding box
	FBoxSphereBounds Bounds = Target->GetRootComponent()->Bounds;
	FVector BoxMin = Bounds.GetBox().Min;
	FVector BoxMax = Bounds.GetBox().Max;

	// Step 2: Clamp the origin point inside the bounding box
	FVector ClampedPoint = Origin;
	ClampedPoint.X = FMath::Clamp(ClampedPoint.X, BoxMin.X, BoxMax.X);
	ClampedPoint.Y = FMath::Clamp(ClampedPoint.Y, BoxMin.Y, BoxMax.Y);
	ClampedPoint.Z = FMath::Clamp(ClampedPoint.Z, BoxMin.Z, BoxMax.Z);

	// Step 3: Calculate the distance from the clamped point to the origin point (optional)
	float Distance = FVector::Dist(ClampedPoint, Origin);

	// Step 4: Return the clamped point as the closest point
	return ClampedPoint;
}


FBox UFC_Functions::GetComponentsBoundingBox(AActor* Target, bool bNonColliding, bool bIncludeFromChildActors)
{
	return Target->GetComponentsBoundingBox(bNonColliding, bIncludeFromChildActors);

}

FVector UFC_Functions::GetComponentsCenter(AActor* Target, bool bNonColliding, bool bIncludeFromChildActors)
{
	return Target->GetComponentsBoundingBox(bNonColliding, bIncludeFromChildActors).GetCenter();
}

int UFC_Functions::ToPercent(float Value, float MaxValue, bool Abs)
{
	return FMath::RoundToInt((Value / MaxValue) * 100);
}

FString UFC_Functions::InsertSpacesBetweenWords(FString in)
{
	// Adds spaces between capital letters
	FString result = "";
	for (int i = 0; i < in.Len(); i++)
	{
		if (i > 0 && in[i] >= 'A' && in[i] <= 'Z')
		{
			result += " ";
		}
		result += in[i];
	}
	return result;
}

bool UFC_Functions::IsPlayerViewOfActorObstructed(AActor* Actor, FVector Origin, ECollisionChannel TraceChannel, bool bDebug)
{
	if (!Actor || !Actor->GetWorld())
	{
		return false;
	}

	FVector PlayerLocation = Origin;

	FBox Bounds = Actor->GetComponentsBoundingBox();
	TArray<FVector> PointsToCheck;
	PointsToCheck.Add(Bounds.GetCenter());
	PointsToCheck.Add(Bounds.Min);
	PointsToCheck.Add(Bounds.Max);
	PointsToCheck.Add(FVector(Bounds.Min.X, Bounds.Min.Y, Bounds.Max.Z));
	PointsToCheck.Add(FVector(Bounds.Max.X, Bounds.Max.Y, Bounds.Min.Z));
	PointsToCheck.Add(FVector(Bounds.Min.X, Bounds.Max.Y, Bounds.Max.Z));
	PointsToCheck.Add(FVector(Bounds.Max.X, Bounds.Min.Y, Bounds.Min.Z));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Actor);

	bool bAllTracesBlocked = true; // Assume all traces are blocked initially

	for (const FVector& EndPoint : PointsToCheck)
	{
		FHitResult HitResult;
		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			Actor->GetWorld(),
			PlayerLocation,
			EndPoint,
			UEngineTypes::ConvertToTraceType(TraceChannel),
			false,
			ActorsToIgnore,
			bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
			HitResult,
			true
		);

		if (!bHit || (bHit && HitResult.Actor.Get() == Actor)) // If not hit or hit the actor itself
		{
			bAllTracesBlocked = false; // Found an unblocked trace
			break; // No need to check further
		}
	}

	return bAllTracesBlocked; // Return true if all traces are blocked, false otherwise
}

FString UFC_Functions::StripString(FString in)
{
	// this function acts exactly like the python strip function
	// it removes all whitespace from the beginning and end of the string

	return in.TrimStartAndEnd();
}



UUserWidget* UFC_Functions::GetParentUserWidget(UWidget* InWidget, TSubclassOf<UUserWidget> ParentWidgetClass, bool bRecursive)
{
	// Check if the input widget is valid
	if (!InWidget || !ParentWidgetClass)
	{
		return nullptr;
	}

	// Traverse outwards through the objects
	UObject* CurrentOuter = InWidget->GetOuter();
	while (CurrentOuter)
	{
		// Get the next outer object
		UObject* NextOuter = CurrentOuter->GetOuter();

		// Check if the next outer object is of the desired class
		UUserWidget* ParentUserWidget = Cast<UUserWidget>(NextOuter);
		if (ParentUserWidget && ParentUserWidget->IsA(ParentWidgetClass))
		{
			return ParentUserWidget;
		}

		// If not recursive, stop after checking the immediate parent
		if (!bRecursive)
		{
			break;
		}

		// Continue traversing outwards through the objects
		CurrentOuter = NextOuter;
	}

	// If the desired parent widget is not found, return nullptr
	return nullptr;
}



bool UFC_Functions::PerformCardinalDirectionBoxTraces(UObject* WorldContextObject, FVector Origin, FVector Bounds, FRotator Rotation, ETraceTypeQuery TraceChannel, bool bDebug, TArray<AActor*> ActorsToIgnore, bool bIgnoreSelf)
{

	FHitResult HitResult;
	
	// Y Forward
	UKismetSystemLibrary::BoxTraceSingle(
		WorldContextObject,
		Origin,
		Origin + (UKismetMathLibrary::GetRightVector(Rotation) * Bounds.Y),
		FVector(Bounds.X, 0.0, Bounds.Z),
		Rotation,
		TraceChannel,
		false,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResult,
		bIgnoreSelf);

	if (HitResult.bBlockingHit)
	{
		return true;
	}

	// Y Backward
	UKismetSystemLibrary::BoxTraceSingle(
		WorldContextObject,
		Origin,
		Origin - (UKismetMathLibrary::GetRightVector(Rotation) * Bounds.Y),
		FVector(Bounds.X, 0.0, Bounds.Z),
		Rotation,
		TraceChannel,
		false,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResult,
		bIgnoreSelf);

	if (HitResult.bBlockingHit)
	{
		return true;
	}

	
	// X Forward
	UKismetSystemLibrary::BoxTraceSingle(
		WorldContextObject,
		Origin,
		Origin + (UKismetMathLibrary::GetForwardVector(Rotation) * Bounds.X),
		FVector(0.0, Bounds.Y, Bounds.Z),
		Rotation,
		TraceChannel,
		false,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResult,
		bIgnoreSelf);
	
	if (HitResult.bBlockingHit)
	{
		return true;
	}

	// X Backward
	UKismetSystemLibrary::BoxTraceSingle(
		WorldContextObject,
		Origin,
		Origin - (UKismetMathLibrary::GetForwardVector(Rotation) * Bounds.X),
		FVector(0.0, Bounds.Y, Bounds.Z),
		Rotation,
		TraceChannel,
		false,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResult,
		bIgnoreSelf);

	if (HitResult.bBlockingHit)
	{
		return true;
	}


	return false;
}

void UFC_Functions::SetAllComponentMaterials(UPrimitiveComponent* Component, UMaterialInterface* Material)
{
	// Set the material of all the component's elements
	for (int32 i = 0; i < Component->GetNumMaterials(); ++i)
	{
		Component->SetMaterial(i, Material);
	}
}

float UFC_Functions::RandomAngle()
{
	return FMath::RandRange(0.0f, 360.0f);
}

AActor* UFC_Functions::GetClosestActorToLocation(const UObject* WorldContextObject, const FVector Location,
	const TArray<AActor*> Actors)
{
	if (Actors.Num() == 0)
	{
		return nullptr;
	}

	AActor* ClosestActor = nullptr;
	float ClosestDistance = FLT_MAX;

	for (AActor* Actor : Actors)
	{
		if (IsValid(Actor))
		{
			float Distance = FVector::Dist(Location, Actor->GetActorLocation());

			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	return ClosestActor;
}

void UFC_Functions::GetOutdoorsLevel(const UObject* WorldContextObject, const FVector Location, float& OutdoorsValue, float& OutdoorsSize)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return; // Safety check

	// Skyward Raycast
	FHitResult SkyHit;
	FVector Start = Location + FVector(0, 0, 50); // Slightly above to prevent ground hits
	FVector End = Start + FVector(0, 0, 2000);   // Long upward ray
	World->LineTraceSingleByChannel(SkyHit, Start, End, ECC_Visibility);

	bool isSkyVisible = !SkyHit.bBlockingHit;

	// Cardinal Raycasts
	float totalDistance = 0.0f;
	int numClearDirections = 0;
	const float raycastLength = 1000.0f;
	const TArray<FVector> directions = { FVector(1, 0, 0), FVector(-1, 0, 0), FVector(0, 1, 0), FVector(0, -1, 0) };

	for (const FVector& dir : directions) 
	{
		FHitResult Hit;
		World->LineTraceSingleByChannel(Hit, Location, Location + dir * raycastLength, ECC_Visibility);
		if (!Hit.bBlockingHit) {
			numClearDirections++;
		}
		totalDistance += Hit.Distance; 
	}

	// Outdoorsness Calculation (Example - tweak according to your needs)
	OutdoorsValue = isSkyVisible ? 0.7f : 0.0f;  
	OutdoorsValue += (float)numClearDirections / 4.0f * 0.3f;

	// Size Estimation
	OutdoorsSize = totalDistance / 4.0f; // Average of cardinal distances
}

UActorComponent* UFC_Functions::GetComponentByName(AActor* Actor, FName Name)
{
	// Check if the Actor is valid
	if (!Actor)
	{
		return nullptr;
	}

	// Array to hold all components of the actor
	TArray<UActorComponent*> Components;
	Actor->GetComponents(Components);

	// Iterate through all components
	for (UActorComponent* Component : Components)
	{
		// Check if the component's name matches the target name
		if (Component->GetName() == Name.ToString())
		{
			// If a match is found, return the component
			return Component;
		}
	}

	// If no component matches the name, return nullptr
	return nullptr;
}

void UFC_Functions::SetActorRootComponent(AActor* Actor, USceneComponent* NewRootComponent)
{
	if(!IsValid(Actor) || !IsValid(NewRootComponent))
	{
		return;
	}
	
	Actor->SetRootComponent(NewRootComponent);
}

bool UFC_Functions::IsValidVector(const FVector& Vector)
{
	// Check if the vector is valid, an invalid vector has NaN values, or is max or min float
	return !Vector.ContainsNaN();
}

void UFC_Functions::ResetInputSettingsToDefault()
{
	// Erase mappings in the current user mapping settings
	{
		auto InputSettings = UInputSettings::GetInputSettings();
		auto AxisMappings = InputSettings->GetAxisMappings();
		for (auto Mapping : AxisMappings)
		{
			InputSettings->RemoveAxisMapping(Mapping, false);
		}

		auto ActionMappings = InputSettings->GetActionMappings();
		for (auto Mapping : ActionMappings)
		{
			InputSettings->RemoveActionMapping(Mapping, false);
		}
		InputSettings->SaveKeyMappings();
	}

	// Reload Input.ini settings which will cause DefaultInput.ini to be applied since its higher up in the config stack
	{
		FConfigCacheIni::LoadGlobalIniFile(GInputIni, TEXT("Input"), nullptr, true, true);
		auto InputSettings = UInputSettings::GetInputSettings();
		InputSettings->ReloadConfig(InputSettings->GetClass(), *GInputIni, UE4::LCPF_PropagateToInstances);
		InputSettings->ForceRebuildKeymaps();
		InputSettings->SaveKeyMappings();
	}


}

FVector UFC_Functions::GetFurthestVector(const FVector& Origin, const TArray<FVector>& Vectors)
{
	if (Vectors.Num() == 0)
	{
		// Handle the case where the array is empty. You might want to return Origin,
		// or perhaps an invalid FVector indicating that the input was invalid.
		return FVector::ZeroVector; // Or some other default/invalid value depending on your requirements.
	}

	FVector FurthestVector = Vectors[0];
	float MaxDistanceSquared = FVector::DistSquared(Origin, FurthestVector);

	for (const FVector& Vec : Vectors)
	{
		float DistanceSquared = FVector::DistSquared(Origin, Vec);
		if (DistanceSquared > MaxDistanceSquared)
		{
			MaxDistanceSquared = DistanceSquared;
			FurthestVector = Vec;
		}
	}

	return FurthestVector;
}

ULevel* UFC_Functions::GetLevel(AActor* Actor)
{
	// Check if the Actor is valid
	if (!Actor)
	{
		return nullptr;
	}

	// Get the Actor's level
	return Actor->GetLevel();
}

void UFC_Functions::GetAllActorsOfClassInLevel(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass,
    ULevelStreaming* Level, TArray<AActor*>& OutActors)
{
    if (!WorldContextObject || !Level || !ActorClass) return;

    // Clear the output array to ensure we're not adding to existing entries.
    OutActors.Empty();

    // Get the actual level from the streaming level object
    ULevel* LoadedLevel = Level->GetLoadedLevel();
    if (!LoadedLevel) return; // Make sure the level is actually loaded

    // Iterate through all actors of the specified class in the world
    for (TActorIterator<AActor> It(WorldContextObject->GetWorld(), ActorClass); It; ++It)
    {
        AActor* Actor = *It;
        if (!Actor) continue;

        // Check if this actor iss part of the level we're interested in
        if (Actor->GetLevel() == LoadedLevel)
        {
            // If so, add it to the output array
            OutActors.Add(Actor);
        }
    }
}

FVector UFC_Functions::SnapVectorToGridOnAxis(const FVector& Vector, float GridSize, bool X, bool Y, bool Z)
{
	FVector SnappedVector = Vector; // Start with the original vector

	if (GridSize <= 0.0f)
	{
		// If the grid size is invalid, return the original vector
		return SnappedVector;
	}
	
	// Snap on X axis
	if (X)
	{
		SnappedVector.X = FMath::RoundHalfToEven(Vector.X / GridSize) * GridSize;
	}

	// Snap on Y axis
	if (Y)
	{
		SnappedVector.Y = FMath::RoundHalfToEven(Vector.Y / GridSize) * GridSize;
	}

	// Snap on Z axis
	if (Z)
	{
		SnappedVector.Z = FMath::RoundHalfToEven(Vector.Z / GridSize) * GridSize;
	}

	return SnappedVector;
}

TArray<FInputAxisKeyMapping> UFC_Functions::SortInputAxisMappingsByScale(
	const TArray<FInputAxisKeyMapping>& AxisMappings)
{
	// Create a copy of the input array
	TArray<FInputAxisKeyMapping> SortedMappings = AxisMappings;
	// Sort the array using a custom predicate
	SortedMappings.Sort([](const FInputAxisKeyMapping& A, const FInputAxisKeyMapping& B)
	{
		// Compare the Scale values of the mappings
		return A.Scale < B.Scale;
	});

	// Return the sorted array
	return SortedMappings;
}
