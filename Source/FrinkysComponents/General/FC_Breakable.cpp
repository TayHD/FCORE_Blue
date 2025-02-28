#include "FC_Breakable.h"

// The goal of this is to automatically setup a breaking to an actor, essentially we'll take all the static mesh
// components, attach them to a root component, and then bind some events so that they'll seperate from its parent once its hit.

UFC_Breakable::UFC_Breakable()
{

	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UFC_Breakable::BeginPlay()
{
	Super::BeginPlay();



}

void UFC_Breakable::Initialize()
{
	// first, we'll populate the breakable components array with all the static mesh components
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	// next, we'll create a root component, and attach all the static mesh components to it
	USceneComponent* RootComponent = NewObject<USceneComponent>(GetOwner(), TEXT("BreakableRootComponent"));

	for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
	{
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	// now lets simulate physics on the root component
}



