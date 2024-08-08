#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPS/FPSPlayerController.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "ActorComponents/State/HealthStaminaComponent.h"
#include "ActorComponents/Interact/InteractComponent.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Interfaces/ItemInteract.h"
//-----------------------------------------------------------------------------------------------------------
AFPSCharacter::AFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}
//-----------------------------------------------------------------------------------------------------------
//Interfaces
//true if begin overlap, fasle if end overlap
void AFPSCharacter::InteractPlayerWithItem(bool bTurnOn)
{
	if (!InteractComponent)
	{
		InteractComponent = GetInteractComponent();
		if (!InteractComponent)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, InteractComponent = nullptr!")));
	}

	InteractComponent->SetInteractLine(bTurnOn);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
//Inputs
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFPSCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &AFPSCharacter::StopSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopSprint);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPSCharacter::Interact);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AFPSCharacter::ShowHideInventory);
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, EnhancedInputComponent = nullptr!")));
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
UHealthStaminaComponent* AFPSCharacter::GetHealthStaminaComponent()
{
	return FindComponentByClass<UHealthStaminaComponent>();
}
UInteractComponent* AFPSCharacter::GetInteractComponent()
{
	return FindComponentByClass<UInteractComponent>();
}
UCameraComponent* AFPSCharacter::GetCameraComponent()
{
	return FirstPersonCameraComponent;
}
UInventoryComponent* AFPSCharacter::GetInventoryComponent()
{
	return FindComponentByClass<UInventoryComponent>();
}
//-----------------------------------------------------------------------------------------------------------
//Sprint
void AFPSCharacter::Sprint()
{
	if(!CharacterMovement || !HealthStaminaComponent)
	{
		HealthStaminaComponent = this->GetHealthStaminaComponent();
		CharacterMovement = this->GetCharacterMovement();
		if (!CharacterMovement || !HealthStaminaComponent)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, CharacterMovement or HealthStaminaComponent = nullptr!")));
	}

	if (HealthStaminaComponent->GetStateMapElem(EStateName::Stamina) <= 10)
		return;

	StandartSpeed = CharacterMovement->MaxWalkSpeed;
	CharacterMovement->MaxWalkSpeed *= 2;
	OnChangeSprint.Broadcast(true);
	
}
void AFPSCharacter::StopSprint()
{
	if (!CharacterMovement)
	{
		CharacterMovement = this->GetCharacterMovement();
		if (!CharacterMovement)
			return;
	}

	CharacterMovement->MaxWalkSpeed = StandartSpeed;
	OnChangeSprint.Broadcast(false);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Interact()
{
	AActor* LocalTarget = GetInteractComponent()->GetTargetActor();
	if (LocalTarget && LocalTarget->GetClass()->ImplementsInterface(UItemInteract::StaticClass()))
	{
		IItemInteract* LocalInteractInterface = Cast<IItemInteract>(GetInteractComponent()->GetTargetActor());
		if (LocalInteractInterface)
			LocalInteractInterface->InteractWithActor(this);
		else
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, LocalInteractInterface = nullptr!")));
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, GetInteractComponent()->GetTargetActor() = nullptr!")));
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ShowHideInventory()
{
	if (!PlayerController)
	{
		PlayerController = Cast<AFPSPlayerController>(GetController());
		if(!PlayerController)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerController = nullptr!")));
	}

	const ESlateVisibility LocalVisibility = PlayerController->MainHUD->WBPInventory->GetVisibility();
	switch (LocalVisibility)
	{
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::Hidden:
		PlayerController->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, PlayerController->MainHUD->WBPInventory);
		PlayerController->MainHUD->WBPInventory->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESlateVisibility::Visible:
	case ESlateVisibility::HitTestInvisible:
	case ESlateVisibility::SelfHitTestInvisible:
		PlayerController->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->MainHUD->WBPInventory->SetVisibility(ESlateVisibility::Collapsed);
		break;

	default:
		break;
	}
}
