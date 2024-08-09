#include "Widgets/Inventory/ChestWidget.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Interfaces/InventorySlot.h"
//-----------------------------------------------------------------------------------------------------------
void UChestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("ChestWidget, PlayerCharacter = nullptr!")));
		else
			PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UChestWidget::InitStorageWidget);
	}
	else
		PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UChestWidget::InitStorageWidget);

	//ButtonClose->OnClicked.AddDynamic(this, &UInventoryWidget::HideInventory);
}
//-----------------------------------------------------------------------------------------------------------
UStorageComponent* UChestWidget::GetStorageComponent()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("ChestWidget, PlayerCharacter = nullptr!")));
	}
	
	return PlayerCharacter->GetChestComponent();
}