#include "ActorComponents/Interact/InteractComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "SubSystem/EventBus.h"
#include "Interfaces/InteractInfo.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Interact/InfoInteractWidget.h"
#include "Items/ItemMaster.h"
//-----------------------------------------------------------------------------------------------------------
UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	OnTraceDelegate.BindUObject(this, &UInteractComponent::OnAcyncTraceDelegate);

	GetWorld()->GetTimerManager().SetTimer(LineTraceTimer, this, &UInteractComponent::LineTraceCall, 0.2, true);
}
//-----------------------------------------------------------------------------------------------------------
//Getter
const TWeakObjectPtr<AActor>& UInteractComponent::GetTargetActor()
{
	return TargetActor;
}
//-----------------------------------------------------------------------------------------------------------
// Основная логика трассировки линии для взаимодействия с объектами
void UInteractComponent::LineTraceCall()
{
	if (!CameraComponent)
	{
		CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
		CHECK_PTR(CameraComponent)
	}
	
	FVector startLocation = CameraComponent->GetComponentLocation();
	FVector endLocation = CameraComponent->GetForwardVector() * 242.0f + startLocation;

	GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Single, startLocation, endLocation, ECollisionChannel::ECC_Visibility, FCollisionQueryParams::DefaultQueryParam, 
		FCollisionResponseParams::DefaultResponseParam, &OnTraceDelegate);

	//DrawDebugLine(GetWorld(), LocalStartLocation, LocalEndLocation, FColor::Red, false, 3.0, 0, 0.1);
}
//-----------------------------------------------------------------------------------------------------------
void UInteractComponent::OnAcyncTraceDelegate(const FTraceHandle& traceHandle, FTraceDatum& traceDatum)
{
	IInteractInfo* itemInfo = nullptr;
	
	if (traceDatum.OutHits.IsEmpty() || !traceDatum.OutHits[0].bBlockingHit || traceDatum.OutHits[0].GetActor()->ActorHasTag(FName(TEXT("NotInteractable"))) || traceDatum.OutHits[0].GetComponent()->ComponentHasTag(FName(TEXT("NotInteractable"))))
	{
		TargetActor = nullptr;
		WidgetInfo(false, nullptr);
		return;
	}

	TargetActor = traceDatum.OutHits[0].GetActor();

	if (TargetActor.IsValid())
	{
		itemInfo = Cast<IInteractInfo>(TargetActor);
		if (itemInfo)
		{
			if (StringName != itemInfo->GetInteractInfo().ItemName)
				WidgetInfo(false, itemInfo);

			WidgetInfo(true, itemInfo);
		}
		else
			WidgetInfo(false, itemInfo);
	}
	else
		WidgetInfo(false, nullptr);
}
//-----------------------------------------------------------------------------------------------------------
// Логика отображения виджета информации о взаимодействии
void UInteractComponent::WidgetInfo(bool bCreate, IInteractInfo* itemInfo)
{
	FText text = {};
	if (!itemInfo)
	{
		UEventBus::OnTriggerInteractWidget.ExecuteIfBound(bCreate, text);
		return;
	}

	FString string1 = itemInfo->GetInteractInfo().InteractButton;
	FString string2 = itemInfo->GetInteractInfo().IteractAction;
	text = FText::FromString(string1 + string2 + StringName);
	StringName = itemInfo->GetInteractInfo().ItemName;

	UEventBus::OnTriggerInteractWidget.ExecuteIfBound(bCreate, text);
}
