#include "Widgets/FastSlotSelector/FastSelectorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Widgets/FastSlotSelector/FastSelectorIconWidget.h"
#include "Widgets/Inventory/SlotWidget.h"
#include "Widgets/FastSlotSelector/FastSelectorBlockWidget.h"
#include "Widgets/FastSlotSelector/FastSelectorItemSlotWidget.h"
#include "Config/PotionMasterDA.h"
#include "Config/SkillScrollDA.h"
#include "Config/ItemMasterDA.h"
#include "Enums/ItemGrade.h"
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UEventBus::OnShowHideFastSelector.BindUObject(this, &UFastSelectorWidget::ShowHideWidget);	
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UEventBus::OnShowHideFastSelector.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
UInventoryComponent* UFastSelectorWidget::GetInventoryComponent()
{
	if (!InventoryComponent)
		InventoryComponent = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	
	return InventoryComponent;
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::GetPotionsAndScrolls(TMap<FName, FPotionStruct>& potionsMap, TArray<FPotionStruct>& potionsArray, TMap<FName, FScrollStruct>& scrollsMap, TArray<FScrollStruct>& scrollsArray)
{
	UPotionMasterDA* potionDA = nullptr;
	USkillScrollDA* scrollDA = nullptr;

	CHECK_PTR(GetInventoryComponent())

	const TArray<FItemInvStruct>& inventory = InventoryComponent->GetStorage();

	for (const FItemInvStruct& item : inventory)
	{
		if (!item.bOccupied)
			continue;
		
		potionDA = Cast<UPotionMasterDA>(item.ItemDA);
		if (potionDA)
		{
			potionsArray.Add(FPotionStruct{ item.ItemCount, potionDA });

			if (potionsMap.Contains(potionDA->ItemName))
				potionsMap.Find(potionDA->ItemName)->PotionCount += item.ItemCount;
			else
				potionsMap.Add(potionDA->ItemName, FPotionStruct{ item.ItemCount, potionDA });

			continue;
		}

		scrollDA = Cast<USkillScrollDA>(item.ItemDA);
		if (scrollDA)
		{
			scrollsArray.Add(FScrollStruct{ item.ItemCount, scrollDA });

			if (scrollsMap.Contains(scrollDA->ItemName))
				scrollsMap.Find(scrollDA->ItemName)->ScrollCount += item.ItemCount;
			else
				scrollsMap.Add(scrollDA->ItemName, FScrollStruct{ item.ItemCount, scrollDA });
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::ShowHideWidget(bool bIsShow)
{
	FVector2D viewportSize = {};
	FVector2D center = {};
	TArray<FPotionStruct> potionsArray = {};
	TArray<FScrollStruct> scrollArray = {};
	TMap<FName, FScrollStruct> scrollMap = {};
	TMap<FName, FPotionStruct> potionsMap = {};
	if (!Controller)
	{
		Controller = GetOwningPlayer();
		CHECK_PTR(Controller)
	}

	Controller->bShowMouseCursor = bIsShow;

	if (bIsShow)
	{
		Controller->SetInputMode(FInputModeGameAndUI());
		UGameplayStatics::SetGlobalTimeDilation(this, 0.2f);

		GEngine->GameViewport->GetViewportSize(viewportSize);
		center = viewportSize * 0.5f;
		Controller->SetMouseLocation(center.X, center.Y);
		
		SetVisibility(ESlateVisibility::Visible);

		GetPotionsAndScrolls(potionsMap, potionsArray, scrollMap, scrollArray);

		InitPotionWidgets(potionsMap, potionsArray);
		InitSkillsWidgets(scrollMap, scrollArray);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
		Controller->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGlobalTimeDilation(this, 1.0f);

		PotionWidgetSwitcher->SetActiveWidgetIndex(0);
		PotionWidgetSwitcher->ClearChildren();
		PotionWidgetSwitcher->SetVisibility(ESlateVisibility::Collapsed);
		PotionVB->ClearChildren();

		ScrollWidgetSwitcher->SetActiveWidgetIndex(0);
		ScrollWidgetSwitcher->ClearChildren();
		ScrollWidgetSwitcher->SetVisibility(ESlateVisibility::Collapsed);
		ScrollVB->ClearChildren();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::InitPotionWidgets(TMap<FName, FPotionStruct>& potionsMap, TArray<FPotionStruct>& potionsArray)
{
	int32 index = 0;
	int32 itemCount = 0;
	constexpr int32 enumLength = static_cast<int32>(EItemGrade::MAX);
	UFastSelectorIconWidget* selectorIcon = nullptr;
	UPotionMasterDA* potionDA = nullptr;
	UFastSelectorBlockWidget* selectorBlock = nullptr;
	UFastSelectorItemSlotWidget* slotWidget = nullptr;

	for (const auto& item : potionsMap)
	{
		selectorIcon = CreateWidget<UFastSelectorIconWidget>(this, FastSelectorIconClass);
		if (!selectorIcon)
			continue;

		PotionVB->AddChild(selectorIcon);
		selectorIcon->InitSelectorIconWidget(index, item.Value.PotionCount, item.Value.PotionDA);
		selectorIcon->OnSelectorIconClick.BindUObject(this, &UFastSelectorWidget::SelectorIconClickPotion);

		selectorBlock = CreateWidget<UFastSelectorBlockWidget>(this, SelectorBlockClass);
		if (!selectorBlock)
			continue;

		PotionWidgetSwitcher->AddChild(selectorBlock);
		for (int32 i = 0; i < enumLength; ++i)
		{
			for (const FPotionStruct& subItem : potionsArray)
			{
				if (!subItem.PotionDA || subItem.PotionDA->ItemName != item.Value.PotionDA->ItemName || static_cast<int32>(subItem.PotionDA->ItemGrade) != i)
					continue;

				itemCount += subItem.PotionCount;
				potionDA = subItem.PotionDA;
			}
			if (itemCount <= 0)
				continue;

			slotWidget = CreateWidget<UFastSelectorItemSlotWidget>(this, ItemSlotClass);
			if (!slotWidget)
				continue;

			selectorBlock->ItemsHB->AddChild(slotWidget);
			slotWidget->InitSelectorSlotType(EItemType::Potion);
			slotWidget->UpdateInvSlot(potionDA->ItemIcon, itemCount, potionDA);
			itemCount = 0;
		}

		++index;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::InitSkillsWidgets(TMap<FName, FScrollStruct>& scrollsMap, TArray<FScrollStruct>& scrollsArray)
{
	int32 index = 0;
	int32 itemCount = 0;
	constexpr int32 enumLength = static_cast<int32>(EItemGrade::MAX);
	UFastSelectorIconWidget* selectorIcon = nullptr;
	USkillScrollDA* potionDA = nullptr;
	UFastSelectorBlockWidget* selectorBlock = nullptr;
	UFastSelectorItemSlotWidget* slotWidget = nullptr;
	TArray<FSoftObjectPath> softRefArray = {};

	for (const FScrollStruct& item : scrollsArray)
	{
		if (!item.ScrollDA)
			continue;

		softRefArray.Add(item.ScrollDA->ExplodeNiagara.ToSoftObjectPath());
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(softRefArray, [this]()
		{});

	for (const auto& item : scrollsMap)
	{
		selectorIcon = CreateWidget<UFastSelectorIconWidget>(this, FastSelectorIconClass);
		if (!selectorIcon)
			continue;

		ScrollVB->AddChild(selectorIcon);
		selectorIcon->InitSelectorIconWidget(index, item.Value.ScrollCount, item.Value.ScrollDA);
		selectorIcon->OnSelectorIconClick.BindUObject(this, &UFastSelectorWidget::SelectorIconClickScroll);

		selectorBlock = CreateWidget<UFastSelectorBlockWidget>(this, SelectorBlockClass);
		if (!selectorBlock)
			continue;

		ScrollWidgetSwitcher->AddChild(selectorBlock);
		for (int32 i = 0; i < enumLength; ++i)
		{
			for (const FScrollStruct& subItem : scrollsArray)
			{
				if (!subItem.ScrollDA || subItem.ScrollDA->ItemName != item.Value.ScrollDA->ItemName || static_cast<int32>(subItem.ScrollDA->ItemGrade) != i)
					continue;

				itemCount += subItem.ScrollCount;
				potionDA = subItem.ScrollDA;
			}
			if (itemCount <= 0)
				continue;

			slotWidget = CreateWidget<UFastSelectorItemSlotWidget>(this, ItemSlotClass);
			if (!slotWidget)
				continue;

			selectorBlock->ItemsHB->AddChild(slotWidget);
			slotWidget->InitSelectorSlotType(EItemType::ScrollSkill);
			slotWidget->UpdateInvSlot(potionDA->ItemIcon, itemCount, potionDA);
			itemCount = 0;
		}

		++index;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::SelectorIconClickPotion(int32 index)
{
	PotionWidgetSwitcher->SetActiveWidgetIndex(index);
	PotionWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorWidget::SelectorIconClickScroll(int32 index)
{
	ScrollWidgetSwitcher->SetActiveWidgetIndex(index);
	ScrollWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
}
//-----------------------------------------------------------------------------------------------------------
