// Copyright Frinky 2022

#pragma once

#include "CoreMinimal.h"
#include "FC_GunComponent.h"
#include "FC_HealthComponent.h"
#include "FC_InteractionManager.h"
#include "FrinkysComponents/Action/FC_ActionManager.h"
#include "FrinkysComponents/Aim/FC_AimHandler.h"
#include "FrinkysComponents/Armour/FC_ArmourComponent.h"
#include "FrinkysComponents/Armour/FC_ArmourHandlerComponent.h"
#include "FrinkysComponents/Equipment/FC_EquipmentComponent.h"
#include "FrinkysComponents/Equipment/FC_EquipmentHandlerComponent.h"
#include "FrinkysComponents/Seats/FC_Seat.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Components/Widget.h"
#include "FC_Functions.generated.h"

class UFC_InventoryComponent;
class UFC_ItemComponent;
/**
 * 
 */
UCLASS()
class FRINKYSCOMPONENTS_API UFC_Functions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_HealthComponent* GetHealthComponent(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_ItemComponent* GetItemComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_InventoryComponent* GetInventoryComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_GenericAttachable* GetGenericAttachable(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_GenericAttachableHandler* GetGenericAttachableHandler(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_EquipmentComponent* GetEquipmentComponent(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_EquipmentHandlerComponent* GetEquipmentHandler(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_GunComponent* GetGunComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_ArmourComponent* GetArmourComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_ArmourHandlerComponent* GetArmourHandlerComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_InteractionManager* GetInteractionManagerComponent(AActor* Actor);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_Seat* GetActorSeat(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_EquipmentComponent* GetHeld(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static AActor* GetHeldActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_GunComponent* GetHeldGunComponent(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE", meta=(DefaultToSelf = "Actor"))
		static UFC_ActionManager* GetActionManager(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_AimHandler* GetAimHandler(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static UFC_Barrel* GetBarrel(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
		static float GetHealth(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category="FRINKYCORE")
		static float Invert(float in);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category="FRINKYCORE")
		static float GetDirectionToTargetDotProduct(FVector Origin, FVector Direction, FVector Target);

	UFUNCTION(BlueprintCallable, Category="FRINKYCORE", meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
		static void GetNumberOfAliveOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> Class, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category="FRINKYCORE")
	static int32 GetClosestRotationIndex(FRotator TargetRotation, const TArray<FRotator>& RotationsArray);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static float GetAngularDistanceBetweenRotators(FRotator Rotator1, FRotator Rotator2);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static FVector ClosestPointOnLine(const FVector& LineStart, const FVector& LineEnd, const FVector& Point);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static bool IsLinePointingAtPoint(const FVector& LineStart, const FVector& LineEnd, const FVector& Point);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE", meta = (BlueprintThreadSafe))
	static float OneMinus(float Value);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE", meta = (BlueprintThreadSafe))
	static FString RoundValueToDigits(int value, int digits);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static float GetFPS();

	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsWithComponent(const UObject* WorldContextObject, TSubclassOf<UActorComponent> ComponentClass, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsWithinRadius(const UObject* WorldContextObject, const FVector Origin, float Radius, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsOfClassWithinRadius(const UObject* WorldContextObject, const FVector Origin, float Radius, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors);
	
	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsWithinRadiusWithComponent(const UObject* WorldContextObject, const FVector Origin, float Radius, TSubclassOf<UActorComponent> ComponentClass, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsOfClassWithinBounds(const UObject* WorldContextObject, const FVector Origin, const FVector Extent, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static bool IsInFrustum(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="FRINKYCORE")
	static int HashInts(int A, int B);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static bool IsPointInExtent(const FVector& Point, const FVector& Origin, const FVector& Extent);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static bool DoExtentsOverlap(const FVector& Extent1, const FVector& Origin1, const FVector& Extent2, const FVector& Origin2);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static bool DoesActorOverlapComponentExtent(AActor* Actor, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, Category="FRINKYCORE")
	static void TeleportComponent(UPrimitiveComponent* Component, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static FString ChopWordOffString(FString in, FString separator);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static FString FindClosestString(FString in, TArray<FString> Strings);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static void CalculateScreenSpaceRectangle(AActor* Target, FVector2D& ScreenPosition, FVector2D& ScreenSize);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static FVector GetClosestPointFromBounds(AActor* Target, FVector Origin);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="FRINKYCORE")
	static FBox GetComponentsBoundingBox(AActor* Target, bool bNonColliding = false, bool bIncludeFromChildActors = false);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static FVector GetComponentsCenter(AActor* Target, bool bNonColliding = false, bool bIncludeFromChildActors = false);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static int ToPercent(float Value = 0.5, float MaxValue = 1.0, bool Abs = true);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static FString InsertSpacesBetweenWords(FString in);

	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE")
	static bool IsPlayerViewOfActorObstructed(AActor* Actor, FVector Origin, ECollisionChannel TraceChannel, bool bDebug);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static FString StripString(FString in);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE", meta = (DeterminesOutputType = "ParentWidgetClass", DefaultToSelf = "InWidget"))
	static UUserWidget* GetParentUserWidget(UWidget* InWidget, TSubclassOf<UUserWidget> ParentWidgetClass, bool bRecursive = false);
	
	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE")
	static bool PerformCardinalDirectionBoxTraces(UObject* WorldContextObject, FVector Origin, FVector Bounds, FRotator Rotation, ETraceTypeQuery TraceChannel, bool bDebug, TArray<AActor*> ActorsToIgnore, bool bIgnoreSelf = true);
	
	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE")
	static void SetAllComponentMaterials(UPrimitiveComponent* Component, UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static float RandomAngle();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static AActor* GetClosestActorToLocation(const UObject* WorldContextObject, const FVector Location, const TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE")
	static void GetOutdoorsLevel(const UObject* WorldContextObject, const FVector Location,  float& OutdoorsValue, float& OutdoorsSize);
	
	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE", meta = (DefaultToSelf = "Actor"))
    static UActorComponent* GetComponentByName(AActor* Actor, FName Name);
	
	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE", meta = (DefaultToSelf = "Actor"))
	static void SetActorRootComponent(AActor* Actor, USceneComponent* NewRootComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static bool IsValidVector(const FVector& Vector);

	UFUNCTION(BlueprintCallable, Category = "FRINKYCORE")
	static void ResetInputSettingsToDefault();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
    static FVector GetFurthestVector(const FVector& Origin, const TArray<FVector>& Vectors);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static ULevel* GetLevel(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Actor",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ActorClass", DynamicOutputParam="OutActors"))
	static void GetAllActorsOfClassInLevel(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, ULevelStreaming* Level, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
	static FVector SnapVectorToGridOnAxis(const FVector& Vector, float GridSize, bool X, bool Y, bool Z);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FRINKYCORE")
    static TArray<FInputAxisKeyMapping> SortInputAxisMappingsByScale(const TArray<FInputAxisKeyMapping>& AxisMappings);
};
