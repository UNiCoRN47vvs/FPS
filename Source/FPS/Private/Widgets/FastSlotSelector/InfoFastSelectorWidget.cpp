#include "Widgets/FastSlotSelector/InfoFastSelectorWidget.h"
#include "Components/ProgressBar.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UInfoFastSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);

	switch (ItemType)
	{
	case EItemType::All:
	case EItemType::Currency:
	case EItemType::Supplies:
	case EItemType::PortalStone:
	case EItemType::PortalDungeon:
	case EItemType::ConsumableSupplies:
	case EItemType::QuestItem:
	case EItemType::Armor:
	case EItemType::Magazine:
	case EItemType::MagicWeapon:
	case EItemType::MagicMagazine:
	case EItemType::Audus:
	case EItemType::StoreSlot:
	case EItemType::MAX:
	default:
		break;

	case EItemType::Potion:
		UEventBus::OnUpdateInfoFastSelectorPotion.AddUObject(this, &UInfoFastSelectorWidget::UpdateInfoFastSelector);
		UEventBus::OnPotionCoolDown.BindUObject(this, &UInfoFastSelectorWidget::Cooldown);
		UEventBus::OnUseSelectedPotion.AddUObject(this, &UInfoFastSelectorWidget::PlayWidgetAnim);
		break;

	case EItemType::ScrollSkill:
		UEventBus::OnUpdateInfoFastSelectorScroll.AddUObject(this, &UInfoFastSelectorWidget::UpdateInfoFastSelector);
		UEventBus::OnScrollCoolDown.BindUObject(this, &UInfoFastSelectorWidget::Cooldown);
		UEventBus::OnUseSelectedScroll.AddUObject(this, &UInfoFastSelectorWidget::PlayWidgetAnim);
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInfoFastSelectorWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UEventBus::OnUpdateInfoFastSelectorPotion.RemoveAll(this);
	UEventBus::OnPotionCoolDown.Unbind();
	UEventBus::OnUseSelectedPotion.RemoveAll(this);

	UEventBus::OnUpdateInfoFastSelectorScroll.RemoveAll(this);
	UEventBus::OnScrollCoolDown.Unbind();
	UEventBus::OnUseSelectedScroll.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
FReply UInfoFastSelectorWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
//-----------------------------------------------------------------------------------------------------------
void UInfoFastSelectorWidget::UpdateInfoFastSelector(UItemMasterDA* itemMasterDA, const TArray<FItemInvStruct>& inventory)
{
	if (!itemMasterDA)
		return;

	int32 itemCount = 0;
	for (const FItemInvStruct& item : inventory)
	{
		if (!item.bOccupied || !item.ItemDA || item.ItemDA != itemMasterDA)
			continue;

		itemCount += item.ItemCount;
	}

	if(itemCount <= 0)
		SetVisibility(ESlateVisibility::Hidden);
	else
		SetVisibility(ESlateVisibility::Visible);

	UpdateInvSlot(itemMasterDA->ItemIcon, itemCount, itemMasterDA);
}
//-----------------------------------------------------------------------------------------------------------
void UInfoFastSelectorWidget::Cooldown(const float currentTimeCooldown,const float timeCooldown) noexcept
{
	CoolDownPB->SetPercent(timeCooldown <= 0.0f ? 0.0f : (timeCooldown - currentTimeCooldown) / timeCooldown);
}
//-----------------------------------------------------------------------------------------------------------
void UInfoFastSelectorWidget::PlayWidgetAnim()
{
	if (CoolDownPB->GetPercent() >= 1.0f)
		PlayAnimation(PushAnim);
	else
		PlayAnimation(CooldownAnim);
}
//-----------------------------------------------------------------------------------------------------------