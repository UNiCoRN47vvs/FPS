#include "Config/PotionMasterDA.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
//-----------------------------------------------------------------------------------------------------------
bool UPotionMasterDA::UseItem(AFPSPlayerController* playerController)
{
	UEventBus::OnUseConsumableSupplies.ExecuteIfBound(StatModifier);
	return true;
}
