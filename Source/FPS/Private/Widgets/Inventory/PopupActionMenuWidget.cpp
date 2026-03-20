#include "Widgets/Inventory/PopupActionMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "FPS/FPSPlayerController.h"
#include "ActorComponents/StorageComponent.h"
#include "Items/Supplies/SuppliesMaster.h"
#include "Config/HomePortalMasterDA.h"
#include "Widgets/Inventory/InventoryButtonWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DestroyButton->Button->OnClicked.AddDynamic(this, &UPopupActionMenuWidget::DestroyItem);
	SellButton->Button->OnClicked.AddDynamic(this, &UPopupActionMenuWidget::SellItem);
	UseButton->Button->OnClicked.AddDynamic(this, &UPopupActionMenuWidget::UseItem);
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::SetData(int32 itemIndex, UStorageComponent* itemStorageComponent, AFPSPlayerController* itemPlayerController)
{
	Index = itemIndex;
	StorageComponent = itemStorageComponent;
	PlayerController = itemPlayerController;

	CHECK_PTR(StorageComponent)

	const FItemInvStruct& item = StorageComponent->GetStorage()[Index];

	if (StorageComponent->GetStorageType() == EStorageType::Equipment)
		DestroyButton->SetVisibility(ESlateVisibility::Collapsed);

	if(!PlayerController->IsStoreValid())
		SellButton->SetVisibility(ESlateVisibility::Collapsed);

	CHECK_PTR(item.ItemDA)
	
	switch (item.ItemDA->ItemType)
	{
	case EItemType::ConsumableSupplies:
	case EItemType::PortalStone:
		UseButton->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::QuestItem:
		UseButton->SetVisibility(ESlateVisibility::Visible);
		SellButton->SetVisibility(ESlateVisibility::Collapsed);
		DestroyButton->SetVisibility(ESlateVisibility::Collapsed);

		break;
	case EItemType::All:
	case EItemType::Armor:
	case EItemType::Currency:
	case EItemType::Magazine:
	case EItemType::MagicWeapon:
	case EItemType::MagicMagazine:
	case EItemType::MAX:
	case EItemType::Supplies:
	case EItemType::Potion:
	case EItemType::PortalDungeon:
		break;

	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::UseItem()
{
	CHECK_PTR(PlayerController)
	CHECK_PTR(StorageComponent)

	bool bIsUseItemSuccess = false;
	FItemInvStruct item = StorageComponent->GetStorage()[Index];
	UConsumableSuppliesMasterDA* itemDA = nullptr;
	CHECK_PTR(item.ItemDA)

	itemDA = Cast<UConsumableSuppliesMasterDA>(item.ItemDA);

	CHECK_PTR(itemDA)

	bIsUseItemSuccess = itemDA->UseItem(PlayerController);

	if (!bIsUseItemSuccess)
		return;

	--item.ItemCount;
	if (item.ItemCount <= 0)
		item = FItemInvStruct{};

	StorageComponent->SetItemFromIndex(item, StorageComponent->CurrentActiveInvTab, Index);
	RemovePopupWidget();
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::SellItem()
{
	CHECK_PTR(StorageComponent)
	CHECK_PTR(StorageComponent->GetStorage()[Index].ItemDA)

	FCurrency currency = {};

	currency = StorageComponent->GetStorage()[Index].ItemDA->ItemCurrency;
	currency *= StorageComponent->GetStorage()[Index].ItemCount;	

	StorageComponent->PickUpItem(currency);
	StorageComponent->SetItemFromIndex(FItemInvStruct{}, StorageComponent->CurrentActiveInvTab, Index);
	UGameplayStatics::PlaySound2D(this, SellSound);
	RemovePopupWidget();
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::DestroyItem()
{
	StorageComponent->SetItemFromIndex(FItemInvStruct{}, StorageComponent->CurrentActiveInvTab, Index);
	UGameplayStatics::PlaySound2D(this, DestroySound);
	RemovePopupWidget();
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::RemovePopupWidget()
{
	if(!PlayerController)
		PlayerController = GetOwningPlayer<AFPSPlayerController>();

	this->RemoveFromParent();

	if(PlayerController)
		PlayerController->PopupMenu = nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);
}
//-----------------------------------------------------------------------------------------------------------
void UPopupActionMenuWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);
	RemovePopupWidget();
}
//-----------------------------------------------------------------------------------------------------------