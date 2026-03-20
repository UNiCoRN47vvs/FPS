#include "Widgets/Inventory/SlotWidget.h"
#include "Components/Border.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/StorageComponent.h"
#include "Widgets/Inventory/InformationWidget.h"
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BorderBrush = ItemGradeBorder->Background;
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!UEventBus::OnShowInformationWidget.IsBound())
		return;

	if (StorageComponent && StorageComponent->GetStorage()[Index].bOccupied)
	{
		SetToolTip(UEventBus::OnShowInformationWidget.Execute(StorageComponent->GetStorage()[Index]));
		return;
	}

	if (!ItemDA)
		return;

	FItemInvStruct itemStruct = {};
	itemStruct.bOccupied = true;
	itemStruct.ItemCount = 1;
	itemStruct.ItemDA = ItemDA;
	itemStruct.ItemLevel = 0;
	itemStruct.StatValue = {};

	SetToolTip(UEventBus::OnShowInformationWidget.Execute(itemStruct));
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::UpdateInvSlot(TSoftObjectPtr<UTexture2D> icon, int32 count, UItemMasterDA* itemDataAsset)
{
	ImageTexture2D = icon;
	if (!icon.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(icon.ToSoftObjectPath(), [this, icon, count, itemDataAsset]()
			{
				UpdateInvSlot(icon, count, itemDataAsset);
			});
		return;
	}

	FString itemLevelText = TEXT("");
	FSlateBrush borderBrush = BorderBrush;
	
	CHECK_PTR(itemDataAsset)

	ItemDA = itemDataAsset;
	Image->SetBrushFromTexture(icon.Get());

	if (ItemCountTB)
		count > 1 ? ItemCountTB->SetText(FText::AsNumber(count)) : ItemCountTB->SetText(FText::FromString(TEXT("")));
	
	PTR(PlusTB)->SetVisibility(ESlateVisibility::Hidden);
	PTR(ItemLevelTB)->SetText(FText::FromString(itemLevelText));
	
	CHECK_PTR(ItemGradeColorDA)

	switch (ItemDA->ItemGrade)
	{
	case EItemGrade::White:
		borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeWhite;
		break;

	case EItemGrade::Green:
		borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeGreen;
		break;

	case EItemGrade::Blue:
		borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeBlue;
		break;

	case EItemGrade::Epic:
		borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeEpic;
		break;

	case EItemGrade::Legendary:
		borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeLegendary;
		break;

	default:
		break;
	}

	ItemGradeBorder->SetBrush(borderBrush);
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::UpdateInvSlot()
{
	CHECK_PTR(StorageComponent)

	const FItemInvStruct& storageItem = StorageComponent->GetStorage()[Index];
	
	if (!storageItem.ItemDA)
		return;

	CHECK_PTR(storageItem.ItemDA->ItemIcon)

	UpdateInvSlot(storageItem.ItemDA->ItemIcon, storageItem.ItemCount);
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::UpdateInvSlot(TSoftObjectPtr<UTexture2D> icon, int32 count)
{
	ImageTexture2D = icon;
	if (count > 0 && StorageComponent)
	{
		if (icon.Get())
			UpdateInvSlotSubFunc1(icon, count);
		else
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(icon.ToSoftObjectPath(), [this, icon, count]()
				{
					UpdateInvSlotSubFunc1(icon, count);
				});
		}
	}
	else
	{
		if (DefaultImage.Get())
			UpdateInvSlotSubFunc2();
		else
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(DefaultImage.ToSoftObjectPath(), [this]()
				{
					UpdateInvSlotSubFunc2();
				});
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::UpdateInvSlotSubFunc1(TSoftObjectPtr<UTexture2D> icon, int32 count)
{
	FString itemLevelText = TEXT("");
	FSlateBrush borderBrush = BorderBrush;
	const FItemInvStruct& item = StorageComponent->GetStorage()[Index];

	CHECK_PTR(icon.Get())
	CHECK_PTR(item.ItemDA)

		Image->SetBrushFromTexture(icon.Get());

	if (ItemCountTB)
		count > 1 ? ItemCountTB->SetText(FText::AsNumber(count)) : ItemCountTB->SetText(FText::FromString(TEXT("")));

	if (ItemLevelTB && PlusTB)
	{
		if (item.ItemLevel > 0)
		{
			itemLevelText = FString::FromInt(item.ItemLevel);
			PlusTB->SetVisibility(ESlateVisibility::Visible);
		}
		else
			PlusTB->SetVisibility(ESlateVisibility::Hidden);

		ItemLevelTB->SetText(FText::FromString(itemLevelText));
	}

	CHECK_PTR(ItemGradeColorDA)

		switch (item.ItemDA->ItemGrade)
		{
		case EItemGrade::White:
			borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeWhite;
			break;

		case EItemGrade::Green:
			borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeGreen;
			break;

		case EItemGrade::Blue:
			borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeBlue;
			break;

		case EItemGrade::Epic:
			borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeEpic;
			break;

		case EItemGrade::Legendary:
			borderBrush.OutlineSettings.Color = ItemGradeColorDA->ColorGradeLegendary;
			break;

		default:
			break;
		}

	ItemGradeBorder->SetBrush(borderBrush);
}
//-----------------------------------------------------------------------------------------------------------
void USlotWidget::UpdateInvSlotSubFunc2()
{
	if (DefaultImage.Get())
	{
		Image->SetBrushFromTexture(DefaultImage.Get());
		if (ItemCountTB)
			ItemCountTB->SetText(FText::FromString(TEXT("")));
		if (ItemLevelTB && PlusTB)
		{
			ItemLevelTB->SetText(FText::FromString(TEXT("")));
			PlusTB->SetVisibility(ESlateVisibility::Hidden);
		}

		SetToolTipText(FText::FromString(TEXT("")));
		ItemGradeBorder->SetBrush(BorderBrush);
	}
}
//-----------------------------------------------------------------------------------------------------------

