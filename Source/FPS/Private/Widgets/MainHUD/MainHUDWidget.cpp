#include "Widgets/MainHUD/MainHUDWidget.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AFPSCharacter* LocalPlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
	if (LocalPlayerCharacter)
	{
		UHealthStaminaComponent* LocalComponent = LocalPlayerCharacter->GetHealthStaminaComponent();
		if (LocalComponent)
			LocalComponent->OnChangeState.AddDynamic(this, &UMainHUDWidget::UpdateProgressBar);
		else
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("MainHUDWidget, LocalComponent = nullptr")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("MainHUDWidget, LocalPlayerCharacter = nullptr")));


}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::UpdateProgressBar(EStateName StateName, double CurrentValue, double MaxValue)
{
	switch (StateName)
	{
	case EStateName::Health:
	case EStateName::HealthMax:
		WBPHealth->SetValueProgressBar(CurrentValue, MaxValue);
		break;
	
	case EStateName::Stamina:
	case EStateName::StaminaMax:
		WBPStamina->SetValueProgressBar(CurrentValue, MaxValue);
		break;

	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::DragDropOperation(UStorageComponent* StorageComponent, int Index, bool bIsDrop)
{
	if (bIsDrop)
	{
		DropStorage = StorageComponent;
		DropIndex = Index;
		if (DragStorage && DropStorage)
		{
			TArray<FItemInvStruct> LocalDragItemStorage = DragStorage->GetStorage();
			TArray<FItemInvStruct> LocalDropItemStorage = DropStorage->GetStorage();
			DragStorage->SetItemFromIndex(LocalDropItemStorage[DropIndex], DragIndex);
			DropStorage->SetItemFromIndex(LocalDragItemStorage[DragIndex], DropIndex);
			WBPInventory->UpdateInventoryWidget();
		}
	}
	else
	{
		DragStorage = StorageComponent;
		DragIndex = Index;
	}
}