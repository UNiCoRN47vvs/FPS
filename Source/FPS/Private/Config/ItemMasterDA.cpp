#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
bool UItemMasterDA::UseItem(AFPSPlayerController* playerController)
{
	return false;
}
//-----------------------------------------------------------------------------------------------------------
TMap<FString, FText> UItemMasterDA::GetItemInfo()
{
	TMap<FString, FText> itemInfo = {};
	itemInfo.Add(TEXT("Name"), FText::FromName(ItemName));
	itemInfo.Add(TEXT("Weight"), FText::AsNumber(ItemWeight));
	itemInfo.Add(TEXT("Sulfur Sell Price"), FText::AsNumber(ItemCurrency.Sulfur));
	itemInfo.Add(TEXT("Item Grade"), StaticEnum<EItemGrade>() ? StaticEnum<EItemGrade>()->GetDisplayNameTextByValue(static_cast<int32>(ItemGrade)) : FText::FromString(TEXT("Invalid")));

	return itemInfo;
}
//-----------------------------------------------------------------------------------------------------------
FStatRange UItemMasterDA::GetItemDamage()
{
	return FStatRange();
}
//-----------------------------------------------------------------------------------------------------------
TMap<EStateName, float> UItemMasterDA::GetItemStat()
{
	return TMap<EStateName, float>();
}
//-----------------------------------------------------------------------------------------------------------
void UItemMasterDA::ApplyRuneData()
{
}
//-----------------------------------------------------------------------------------------------------------
