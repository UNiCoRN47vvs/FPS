#include "Config/ConsumableSuppliesMasterDA.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
//-----------------------------------------------------------------------------------------------------------
bool UConsumableSuppliesMasterDA::UseItem(AFPSPlayerController* playerController)
{
	return true;
}
TMap<FString, FText> UConsumableSuppliesMasterDA::GetItemInfo()
{
	TMap<FString, FText> itemInfo = Super::GetItemInfo();

	for (auto& item : StatModifier)
	{
		itemInfo.Add(StaticEnum<EStateName>() ? StaticEnum<EStateName>()->GetDisplayNameTextByValue(static_cast<int32>(item.Key)).ToString() : TEXT("Invalid"), FText::AsNumber(item.Value));
	}

	return itemInfo;
}
//-----------------------------------------------------------------------------------------------------------