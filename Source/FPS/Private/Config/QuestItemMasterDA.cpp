#include "Config/QuestItemMasterDA.h"
#include "FPS/FPSPlayerController.h"
#include "SubSystem/WorldRuler.h"
#include "SubSystem/EventBus.h"
//-----------------------------------------------------------------------------------------------------------
bool UQuestItemMasterDA::UseItem(AFPSPlayerController* playerController)
{
	if (!playerController)
		return false;

	if (!WorldRuler)
	{
		WorldRuler = playerController->GetWorld()->GetSubsystem<UWorldRuler>();
		if (!WorldRuler)
		{
			ALARM_LOG
			return false;
		}
	}

	int32 questIndex = 0;

	if (!WorldRuler->FindQuestTarget(QuestTarget, questIndex))
		return false;

	UEventBus::OnUseQuestInteract.ExecuteIfBound(QuestTarget);
	playerController->CreateWidgetInMainHUD(EStorageType::Inventory);

	return true;
}
