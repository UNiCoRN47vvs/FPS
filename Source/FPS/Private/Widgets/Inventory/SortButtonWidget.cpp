#include "Widgets/Inventory/SortButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ActorComponents/StorageComponent.h"
//-----------------------------------------------------------------------------------------------------------
void USortButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock->SetText(SortText);
}
//-----------------------------------------------------------------------------------------------------------
void USortButtonWidget::InitSortButton(UStorageComponent* storageComponent)
{
	StorageComponent = storageComponent;
	PTR(ButtonSort)->OnClicked.AddDynamic(this, &USortButtonWidget::StorageSort);
}
//-----------------------------------------------------------------------------------------------------------
void USortButtonWidget::StorageSort()
{
	const TArray<FItemInvStruct>& inventoryStorage = StorageComponent->GetStorage();
	int32 enumSize = 0;
	int32 inventorSize = inventoryStorage.Num();
	int32 startIndex = 0;
	FString string1 = {};
	FString string2 = {};
	TArray<FItemInvStruct> array = {};

	UGameplayStatics::PlaySound2D(this, SortSound);

	switch (SortType)
	{
	case ESortType::SortType:
		enumSize = static_cast<int32>(EItemType::MAX);
		startIndex = 1;
		break;

	case ESortType::SortGrade:
		enumSize = static_cast<int32>(EItemGrade::MAX);
		break;

	default:
		break;
	}

	for (int32 i = startIndex; i < enumSize; ++i)
	{
		for (auto& item : inventoryStorage)
		{
			if (!item.bOccupied || !item.ItemDA)
				continue;

			switch (SortType)
			{
			case ESortType::SortType:
				if (item.ItemDA->ItemType == static_cast<EItemType>(i))
					array.Add(item);
				break;

			case ESortType::SortGrade:
				if (item.ItemDA->ItemGrade == static_cast<EItemGrade>(i))
					array.Add(item);
				break;

			default:
				break;
			}
		}
	}

	if (SortType == ESortType::SortName)
	{
		for (const FItemInvStruct& item : inventoryStorage)
		{
			if (item.bOccupied)
				array.Add(item);
		}
		for (int32 i = 0; i < array.Num(); ++i)
		{
			if (!array[i].ItemDA)
				continue;
			for (int32 j = 0; j < array.Num(); ++j)
			{
				if (!array[j].ItemDA)
					continue;

				string1 = array[i].ItemDA->ItemName.ToString();
				string2 = array[j].ItemDA->ItemName.ToString();

				if (array[i].ItemDA->ItemName.ToString() < array[j].ItemDA->ItemName.ToString())
					array.Swap(i, j);
			}
		}
	}

	while (array.Num() < inventoryStorage.Num())
	{
		array.Add(FItemInvStruct{});
	}

	for (int32 i = 0; i < array.Num(); ++i)
	{
		StorageComponent->SetItemFromIndex(array[i], StorageComponent->CurrentActiveInvTab, i);
	}
}
//-----------------------------------------------------------------------------------------------------------