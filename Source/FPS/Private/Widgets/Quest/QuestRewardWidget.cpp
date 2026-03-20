#include "Widgets/Quest/QuestRewardWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/Inventory/SlotWidget.h"
#include "Config/QuestMasterDA.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UQuestRewardWidget::InitRewardWidget(const FItemReward& item)
{
	CHECK_PTR(RewardSlot)
	CHECK_PTR(item.ItemDA.LoadSynchronous())
	
	RewardSlot->UpdateInvSlot(item.ItemDA.LoadSynchronous()->ItemIcon, item.ItemCount, item.ItemDA.LoadSynchronous());
}
