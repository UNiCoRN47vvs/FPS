#include "Widgets/Inventory/InventoryWidget.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Interfaces/InventorySlot.h"
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
		else
			PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UInventoryWidget::InitStorageWidget);
	}
	else
		PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UInventoryWidget::InitStorageWidget);

	ButtonClose->OnClicked.AddDynamic(this, &UInventoryWidget::HideInventory);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::HideInventory()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
	}
		PlayerCharacter->ShowHideInventory();
}
//-----------------------------------------------------------------------------------------------------------
//Getter
UStorageComponent* UInventoryWidget::GetStorageComponent()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
	}
	return PlayerCharacter->GetInventoryComponent();
}
