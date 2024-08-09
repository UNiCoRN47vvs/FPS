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
			PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UInventoryWidget::InitInventoryWidget);
	}
	else
		PlayerCharacter->GetInventoryComponent()->InitInvWidget.AddDynamic(this, &UInventoryWidget::InitInventoryWidget);

	ButtonClose->OnClicked.AddDynamic(this, &UInventoryWidget::HideInventory);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::InitInventoryWidget()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
	}

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
			LocalSlotWidget->StorageComponent = GetStorageComponent();
			UniformGridPanel->AddChildToUniformGrid(LocalSlotWidget, Row, Column);
		}
	}else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
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
void UInventoryWidget::UpdateInventoryWidget()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
	}

	TArray<FItemInvStruct> Inventory = PlayerCharacter->GetInventoryComponent()->GetInventory();
	for (int i = 0; i < UniformGridPanel->GetAllChildren().Num(); ++i)
	{
		IInventorySlot* LocalSlotInterface = Cast<IInventorySlot>(UniformGridPanel->GetAllChildren()[i]);
		if(!LocalSlotInterface)
			return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, LocalSlotInterface = nullptr!")));

		LocalSlotInterface->UpdateInvSlot(Inventory[i].ItemIcon, Inventory[i].ItemCount);
	}
}
//-----------------------------------------------------------------------------------------------------------
UInventoryComponent* UInventoryWidget::GetStorageComponent()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
		if(!PlayerCharacter)
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("InventoryWidget, PlayerCharacter = nullptr!")));
	}
	return PlayerCharacter->GetInventoryComponent();
}
