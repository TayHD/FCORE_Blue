// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FC_Breakable.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FRINKYSCOMPONENTS_API UFC_Breakable : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFC_Breakable();

	TArray<UStaticMeshComponent> BreakableComponents;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Initialize();
	
};
