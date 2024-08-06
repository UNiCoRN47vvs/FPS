#include "ActorComponents/Interact/InteractComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "FPS/FPSCharacter.h"
#include "Interfaces/ItemInteract.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Interact/InfoInteractWidget.h"
#include "Items/ItemMaster.h"
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

		if (InteractWidget)
			InteractWidget->RemoveFromParent();
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
AActor* UInteractComponent::GetTargetActor()
{
	return TargetActor;
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::LineTraceCall()
{
	if (!CameraComponent || !PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwner());
		if (!PlayerCharacter)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, PlayerCharacter = nullptr!")));

		CameraComponent = PlayerCharacter->GetCameraComponent();

		if(!CameraComponent)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, CameraComponent = nullptr!")));

	}

	FHitResult LocalHitResult;
	FVector LocalStartLocation = CameraComponent->GetComponentLocation();
	FVector LocalEndLocation = CameraComponent->GetForwardVector() * 220.0 + LocalStartLocation;

	GetWorld()->LineTraceSingleByChannel(LocalHitResult, LocalStartLocation, LocalEndLocation, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(GetWorld(), LocalStartLocation, LocalEndLocation, FColor::Red, false, 0.3, 0, 0.1);

	TargetActor = LocalHitResult.GetActor();

	if (TargetActor)
	{
		IItemInteract* LocalItemInteract = Cast<IItemInteract>(TargetActor);
		if (LocalItemInteract)
		{
			//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, LocalItemInteract->GetItemInfo());
			WidgetInfo(true, LocalItemInteract);
		}
		else
		{
			WidgetInfo(false, LocalItemInteract);
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, LocalItemInteract = nullptr!")));
		}
	}
	else
	{
		WidgetInfo(false, nullptr);
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InteractComponent, TargetActor = nullptr!")));
	}

}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::WidgetInfo(bool bCreate, IItemInteract* ItemInteract)
{
	if (bCreate)
	{
		if (InteractWidget)
			return;

		FString LocalString1 = FString(TEXT("[E] "));
		FString LocalString2 = FString(TEXT("Interact "));
		FString LocalString3 = ItemInteract->GetItemInfo().ItemName.ToString();

		InteractWidget = CreateWidget<UInfoInteractWidget>(GetWorld(), BPInteractWidget);
		InteractWidget->TextBlock->SetText(FText::FromString(LocalString1 + LocalString2 + LocalString3));
		InteractWidget->AddToViewport();
	}
	else
	{
		if (!InteractWidget)
			return;

		InteractWidget->RemoveFromParent();
		InteractWidget = nullptr;
	}
}
