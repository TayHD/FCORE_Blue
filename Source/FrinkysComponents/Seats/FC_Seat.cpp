// Copyright Frinky 2022


#include "FC_Seat.h"

#include "Components/CapsuleComponent.h"
#include "FrinkysComponents/General/FC_Functions.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UFC_Seat::UFC_Seat()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	
}

void UFC_Seat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(IsValid(AttachedPawn))
	{
		AttachedPawn->SetActorRotation(GetComponentRotation());
	}
}

void UFC_Seat::InitializeComponent()
{

	Super::InitializeComponent();
	
}

void UFC_Seat::OnComponentCreated()
{
	Super::OnComponentCreated();
	# if WITH_EDITOR
		DebugMeshComponent = NewObject<USkeletalMeshComponent>(this, TEXT("DebugMesh"));
		DebugMeshComponent->RegisterComponent();
		DebugMeshComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		DebugMeshComponent->SetSkeletalMesh(PreviewMesh);
		DebugMeshComponent->SetRelativeRotation(PreviewRotation);
		DebugMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DebugMeshComponent->SetRelativeLocation(PawnOffset + PreviewLocation);
		DebugMeshComponent->SetHiddenInGame(true);

		// load material Material'/Engine/EngineMaterials/BlinkingCaret.BlinkingCaret'
		UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Engine/EngineMaterials/BlinkingCaret.BlinkingCaret'"));
		// set all materials to this material
		for (int i = 0; i < DebugMeshComponent->GetNumMaterials(); i++)
		{
			DebugMeshComponent->SetMaterial(i, Material);
		}
		
		PreviewEjectMeshComponent = NewObject<USkeletalMeshComponent>(this, TEXT("EjectMesh"));
		PreviewEjectMeshComponent->RegisterComponent();
		PreviewEjectMeshComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		PreviewEjectMeshComponent->SetSkeletalMesh(PreviewMesh);
		PreviewEjectMeshComponent->SetRelativeRotation(PreviewRotation);
		PreviewEjectMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PreviewEjectMeshComponent->SetRelativeLocation(ExitPosition + FVector(0.f, 0.f, -96.f));
		PreviewEjectMeshComponent->SetHiddenInGame(true);

		// load material Material'/Engine/EngineMaterials/BlinkingCaret.BlinkingCaret'
		// set all materials to this material
		for (int i = 0; i < PreviewEjectMeshComponent->GetNumMaterials(); i++)
		{
			PreviewEjectMeshComponent->SetMaterial(i, Material);
		}
		
		//Set animation to "Pose"
		if (Pose)
		{
			DebugMeshComponent->PlayAnimation(Pose, true);
		}
	#endif
	
}


void UFC_Seat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFC_Seat, AttachedPawn);
}

void UFC_Seat::OnRep_AttachedPawn()
{
	if (AttachedPawn)
	{
		UFC_Seat* OldSeat = UFC_Functions::GetActorSeat(AttachedPawn);
		if(IsValid(OldSeat))
		{
			OldSeat->Eject();
		}

		SitMulti(AttachedPawn);
		
		
		AttachedPawn->bUseControllerRotationYaw = false;
		
		const ACharacter* Character = dynamic_cast<ACharacter*>(AttachedPawn);
		
		if (IsValid(Character) && IsValid(Character->Controller))
		{
			
			Character->GetCharacterMovement()->DisableMovement();
			Character->Controller->SetControlRotation(GetComponentRotation());

			// if controller is a player controller, disable input
			const APlayerController* PlayerController = const_cast<APlayerController*>(Character->GetController<APlayerController>());
			if (IsValid(PlayerController))
			{
				SavedMaxViewPitch = PlayerController->PlayerCameraManager->ViewPitchMax;
				SavedMinViewPitch = PlayerController->PlayerCameraManager->ViewPitchMin;
				SavedMaxViewYaw = PlayerController->PlayerCameraManager->ViewYawMax;
				SavedMinViewYaw = PlayerController->PlayerCameraManager->ViewYawMin;

				
				PlayerController->PlayerCameraManager->ViewYawMax = MinViewYaw;
				PlayerController->PlayerCameraManager->ViewYawMin = MaxViewYaw;
				PlayerController->PlayerCameraManager->ViewPitchMax = MaxViewPitch;
				PlayerController->PlayerCameraManager->ViewPitchMin = MinViewPitch;;
			}
		}

		OnSit.Broadcast(AttachedPawn);
	}
}

void UFC_Seat::SitMulti_Implementation(APawn* Pawn)
{
	const ACharacter* Character = dynamic_cast<ACharacter*>(Pawn);
	if(IsValid(Character))
	{
		Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
	}
	
	Pawn->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
	Pawn->SetActorRelativeLocation(PawnOffset);
	
	
}

void UFC_Seat::EjectMulti_Implementation()
{
	if (AttachedPawn)
	{
		AttachedPawn->bUseControllerRotationYaw = true;
		AttachedPawn->SetActorRelativeLocation(ExitPosition);
		AttachedPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		const ACharacter* Character = dynamic_cast<ACharacter*>(AttachedPawn);
		if (Character)
		{
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			if (IsValid(PlayerController))
			{
				PlayerController->PlayerCameraManager->ViewYawMax = SavedMaxViewYaw;
				PlayerController->PlayerCameraManager->ViewYawMin = SavedMinViewYaw;
				PlayerController->PlayerCameraManager->ViewPitchMax = SavedMaxViewPitch;
				PlayerController->PlayerCameraManager->ViewPitchMin = SavedMinViewPitch;
			}
		}
		OnEject.Broadcast(AttachedPawn);
	}
}

bool UFC_Seat::IsPawnSeated()
{
	return (IsValid(AttachedPawn));
}

void UFC_Seat::AddForwardInput(float Value)
{
	OnForwardInput.Broadcast(Value);
}

void UFC_Seat::AddRightInput(float Value)
{
	OnRightInput.Broadcast(Value);
}

void UFC_Seat::Sit_Implementation(APawn* Pawn)
{
	if (AttachedPawn != Pawn)
	{
		AttachedPawn = Pawn;
		OnRep_AttachedPawn();
	}
}

void UFC_Seat::Eject_Implementation()
{
	EjectMulti();
	
	AttachedPawn = nullptr;
	OnRep_AttachedPawn();
}
