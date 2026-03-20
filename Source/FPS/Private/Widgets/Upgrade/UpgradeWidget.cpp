#include "Widgets/Upgrade/UpgradeWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/Upgrade/UpgradeComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Config/ItemMasterDA.h"
#include "Struct/ItemInvStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FWidgetAnimationDynamicEvent animationEnd;
	animationEnd.BindDynamic(this, &UUpgradeWidget::UpgradeItem);
	BindToAnimationFinished(UpgradeAnimation, animationEnd);

	UpgradeButton->OnClicked.AddDynamic(this, &UUpgradeWidget::PushUpgradeButton);
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeWidget::UpdateSlots()
{
	CHECK_PTR(StorageComp)

	if(StorageComp->GetStorage()[0].ItemDA)
		UpgradeSlot1->UpdateInvSlot(StorageComp->GetStorage()[0].ItemDA->ItemIcon, StorageComp->GetStorage()[0].ItemCount);
	if(StorageComp->GetStorage()[1].ItemDA)
		UpgradeSlot2->UpdateInvSlot(StorageComp->GetStorage()[1].ItemDA->ItemIcon, StorageComp->GetStorage()[1].ItemCount);
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeWidget::InitUpgradeWidget(UUpgradeComponent* StorageComponent)
{
	CHECK_PTR(StorageComponent)

	StorageComp = StorageComponent;

	const TArray<FItemInvStruct>& storage = StorageComponent->GetStorage();
	TSoftObjectPtr<UTexture2D> icon = nullptr;
	UpgradeComponent = StorageComponent;
	for (int i = 0; i < storage.Num(); ++i)
	{
		if (storage[i].ItemDA)
			icon = storage[i].ItemDA->ItemIcon;		
		
		if (i == 0)
		{
			UpgradeSlot1->StorageComponent = StorageComponent;
			UpgradeSlot1->UpdateInvSlot(icon, storage[i].ItemCount);
		}
		else
		{
			UpgradeSlot2->StorageComponent = StorageComponent;
			UpgradeSlot2->UpdateInvSlot(icon, storage[i].ItemCount);
		}

		icon = nullptr;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeWidget::PushUpgradeButton()
{
	if (bIsAnimationPlay)
		return;

	float timerSpeed = 1.0;
	const TArray<FItemInvStruct>& storage = UpgradeComponent->GetStorage();
	if (storage.IsEmpty())
		return;

	CHECK_PTR(storage[0].ItemDA)
	CHECK_PTR(storage[1].ItemDA)

	bool check1 = storage[0].bOccupied && storage[1].bOccupied;
	bool check2 = storage[0].ItemDA->ItemName	== storage[1].ItemDA->ItemName;
	bool check3 = storage[0].ItemDA->ItemGrade == storage[1].ItemDA->ItemGrade;
	bool check4 = storage[0].ItemLevel >= storage[1].ItemLevel;
	bool check5 = false;

	switch (storage[0].ItemDA->ItemType)
	{
	case EItemType::Armor :
	case EItemType::MagicWeapon :
	case EItemType::PortalDungeon :
	case EItemType::Audus :
		check5 = true;
		break;

	default:
		break;
	}

	if (check1 && check2 && check3 && check4 && check5)
	{
		PlayAnimation(UpgradeAnimation);
		PlaySound(UpgradingItemSound);
		UpgradeSlot1->bIsSlotBlock = true;
		UpgradeSlot2->bIsSlotBlock = true;
		bIsAnimationPlay = true;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("-[%S]- : UPGRADE FAIL"), __FUNCTION__);
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeWidget::UpgradeItem()
{
	int32 enumSize = static_cast<int32>(EItemGrade::MAX);
	float random = 0.0;
	float chanse = 0.0;
	const TArray<FItemInvStruct>& storage = UpgradeComponent->GetStorage();
	FItemInvStruct item = storage[0];
	UItemMasterDA* itemMasterDA = nullptr;
	UItemMasterDA* itemDA = nullptr;
	FGradeUpgradeChance* DTRow = {};

	if (storage.IsEmpty())
		return;

	CHECK_PTR(DTGradeUpgradeChance)
	CHECK_PTR(item.ItemDA)

	itemMasterDA = Cast<UItemMasterDA>(item.ItemDA);
	CHECK_PTR(itemMasterDA)

	const TMap<FName, uint8*>& rowMap = DTGradeUpgradeChance->GetRowMap();
	for (const auto& subItem : rowMap)
	{
		// Преобразуем указатель на байты в нашу структуру строки
		DTRow = reinterpret_cast<FGradeUpgradeChance*>(subItem.Value);
		if (!DTRow)
			continue;

		if (DTRow->Grade == item.ItemDA->ItemGrade)
			break;

		DTRow = nullptr;
	}

	CHECK_PTR(DTRow)

	chanse = DTRow->UpgradeChance + DTRow->DowngradeChance + DTRow->NothingChance;
	random = FMath::RandRange(random, chanse);
	
	if (random <= DTRow->UpgradeChance)
	{
		if (item.ItemDA->ItemGrade == EItemGrade::Legendary || item.ItemLevel < 10)
			item.ItemLevel += 1;
		else
		{
			itemDA = itemMasterDA->NextUpgrade.LoadSynchronous();
			if (!itemDA)
			{
				ALARM_LOG
				UpgradeSlot1->bIsSlotBlock = false;
				UpgradeSlot2->bIsSlotBlock = false;
				UpgradeProgressBar->SetPercent(0);
				bIsAnimationPlay = false;
				return;
			}

			item.ItemDA			= itemDA;
			item.ItemLevel		= 0;
			item.StatValue		= itemDA->StatStruct.FindRandomStatWithRandomValue(itemDA->ItemGrade);
		}
		PlaySound(UpgradingSuccessSound);
	}
	else if (random <= DTRow->UpgradeChance + DTRow->DowngradeChance)
	{
		if(item.ItemLevel != 0)
			item.ItemLevel -= 1;

		PlaySound(UpgradingFailSound);
	}
	else
	{
		PlaySound(UpgradingFailSound);
	}

	UpgradeComponent->SetItemFromIndex(item, StorageComp->CurrentActiveInvTab, 0);
	UpgradeComponent->SetItemFromIndex(FItemInvStruct{}, StorageComp->CurrentActiveInvTab, 1);
	
	UpgradeSlot1->bIsSlotBlock = false;
	UpgradeSlot2->bIsSlotBlock = false;
	
	UpgradeSlot1->UpdateInvSlot(storage[0].ItemDA ? storage[0].ItemDA->ItemIcon : nullptr, storage[0].ItemCount);
	UpgradeSlot2->UpdateInvSlot(storage[1].ItemDA ? storage[1].ItemDA->ItemIcon : nullptr, storage[1].ItemCount);

	UpgradeProgressBar->SetPercent(0);
	bIsAnimationPlay = false;

	UEventBus::OnSaveGame.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------