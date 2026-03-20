#include "Config/ArmorMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
//TMap<FString, FText> UArmorMasterDA::GetItemInfo()
//{
//   TMap<FString, FText> itemInfo = Super::GetItemInfo();
//
//   for (const auto& item : ArmorStat.StatsValue)
//   {
//      itemInfo.Add(StaticEnum<EStateName>() ? StaticEnum<EStateName>()->GetDisplayNameTextByValue(static_cast<int32>(item.Key)).ToString() : TEXT("Invalid"), FText::AsNumber(item.Value));
//   }
//
//   return itemInfo;
//}
//-----------------------------------------------------------------------------------------------------------
TMap<EStateName, float> UArmorMasterDA::GetItemStat()
{
    return ArmorStat.StatsValue;
}
//-----------------------------------------------------------------------------------------------------------