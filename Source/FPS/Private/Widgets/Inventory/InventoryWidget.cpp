#include "Widgets/Inventory/InventoryWidget.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
	if (PlayerCharacter)
		PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UInventoryWidget::InitInventoryWidget);
	else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::InitInventoryWidget()
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
	if (PlayerCharacter)
	{
		int InvSlotsPerRow = PlayerCharacter->GetInventoryComponent()->InvSlotsPerRow;
		TArray<FItemInvStruct> Inventory = PlayerCharacter->GetInventoryComponent()->GetInventory();
		for (int i = 0; i < Inventory.Num(); ++i)
		{
			int Row    = i / InvSlotsPerRow;
			int Column = i % InvSlotsPerRow;
			UInventorySlotWidget* LocalSlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotWidget);
			if (!LocalSlotWidget)
				return;

			LocalSlotWidget->Index = i;
			UniformGridPanel->AddChildToUniformGrid(LocalSlotWidget, Row, Column);
		}
	}else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
}
