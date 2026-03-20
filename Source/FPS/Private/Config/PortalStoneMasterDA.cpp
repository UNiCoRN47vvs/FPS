#include "Config/PortalStoneMasterDA.h"

TMap<FString, FText> UPortalStoneMasterDA::GetItemInfo()
{
   TMap<FString, FText> itemInfo = Super::GetItemInfo();

   for (auto& item : StatsValue.StatsValue)
   {
      itemInfo.Add(StaticEnum<EStateName>() ? StaticEnum<EStateName>()->GetDisplayNameTextByValue(static_cast<int32>(item.Key)).ToString() : TEXT("Invalid"), FText::AsNumber(item.Value));
   }

    return itemInfo;
}
