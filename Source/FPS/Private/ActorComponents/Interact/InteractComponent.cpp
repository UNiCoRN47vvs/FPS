#include "ActorComponents/Interact/InteractComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "FPS/FPSCharacter.h"
//-----------------------------------------------------------------------------------------------------------
UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();	
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::SetInteractLine(bool bTurnOn)
{
	if (bTurnOn)
	{
		++TimerCounter;
		if (TimerCounter > 1)
			return;

		GetWorld()->GetTimerManager().SetTimer(LineTraceTimer, this, &UInteractComponent::LineTraceCall, 0.1, true);
	}
	else
	{
		--TimerCounter;
		if (TimerCounter > 0)
			return;

		GetWorld()->GetTimerManager().ClearTimer(LineTraceTimer);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::LineTraceCall()
{
	if (!CameraComponent || !PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwner());
		if (!PlayerCharacter)
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, PlayerCharacter = nullptr!")));
			return;
		}
		CameraComponent = PlayerCharacter->GetCameraComponent();
		if(!CameraComponent)
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, CameraComponent = nullptr!")));
			return;
		}
	}

	FHitResult LocalHitResult;
	FVector LocalStartLocation = CameraComponent->GetComponentLocation();
	FVector LocalEndLocation = CameraComponent->GetForwardVector() * 220.0 + LocalStartLocation;

	GetWorld()->LineTraceSingleByChannel(LocalHitResult, LocalStartLocation, LocalEndLocation, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(GetWorld(), LocalStartLocation, LocalEndLocation, FColor::Red, false, 1, 0, 1);
}