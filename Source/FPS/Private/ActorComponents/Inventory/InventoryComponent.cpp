#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "ActorComponents/State/PlayerStateComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsPotionCooldown = false;
	TimePotionCooldown = 5.0f;
	CurrentTimePotionCooldown = 0.0f;
	bIsScrollCooldown = false;
	TimeScrollCooldown = 10.0f;
	CurrentTimeScrollCooldown = 0.0f;
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UEventBus::OnSelectorPotion.BindUObject(this, &UInventoryComponent::SelectPotion);
	UEventBus::OnUseSelectedPotion.AddUObject(this, &UInventoryComponent::UseSelectedPotion);
	UEventBus::OnSelectorScroll.BindUObject(this, &UInventoryComponent::SelectScroll);
	UEventBus::OnUseSelectedScroll.AddUObject(this, &UInventoryComponent::UseSelectedScroll);

	UEventBus::OnApplySelectedScroll.BindUObject(this, &UInventoryComponent::UseScroll);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UEventBus::OnSelectorPotion.Unbind();
	UEventBus::OnUseSelectedPotion.RemoveAll(this);
	UEventBus::OnSelectorScroll.Unbind();
	UEventBus::OnUseSelectedScroll.RemoveAll(this);

	UEventBus::OnApplySelectedScroll.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::SelectPotion(UItemMasterDA* itemMasterDA)
{
	PotionDA = itemMasterDA;

	UEventBus::OnUpdateInfoFastSelectorPotion.Broadcast(PotionDA, GetStorage());
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::UseSelectedPotion()
{
	if (bIsPotionCooldown) //TODO : Добавить обочзачение что сейчас кд на использование
	{
		UGameplayStatics::PlaySound2D(this, CooldownSound);
		return;
	}

	CHECK_PTR(PotionDA)

	if (!PlayerController)
	{
		PlayerController = GetOwner<APawn>()->GetController<AFPSPlayerController>();
		CHECK_PTR(PlayerController)
	}

	TArray<FItemInvStruct>& inventory = Storage[CurrentActiveInvTab].StorageTab;
	
	for (int32 i = 0; i < inventory.Num(); i++)
	{
		if (inventory[i].ItemCount <= 0 && inventory.Num() - 1 == i)
		{
			PotionDA = nullptr;
			bIsPotionCooldown = false;
		}

		if (!inventory[i].bOccupied || !inventory[i].ItemDA || inventory[i].ItemDA != PotionDA)
			continue;

		inventory[i].ItemDA->UseItem(PlayerController);
		--inventory[i].ItemCount;

		SetItemFromIndex(inventory[i], CurrentActiveInvTab, i);
		bIsPotionCooldown = true;

		CoolDownTimer(PotionTimer, bIsPotionCooldown, TimePotionCooldown, CurrentTimePotionCooldown);
		UEventBus::OnPotionCoolDown.ExecuteIfBound(CurrentTimePotionCooldown, TimePotionCooldown);
		break;
	}

	if(PotionDA)
		UGameplayStatics::PlaySound2D(this, DrinkPotionSound);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::SelectScroll(UItemMasterDA* itemMasterDA)
{
	ScrollDA = itemMasterDA;

	UEventBus::OnUpdateInfoFastSelectorScroll.Broadcast(ScrollDA, GetStorage());
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::UseSelectedScroll()
{
	if (bIsScrollCooldown) 
	{
		UGameplayStatics::PlaySound2D(this, CooldownSound);
		return;
	}

	CHECK_PTR(ScrollDA)

	USkillScrollDA* scrollDA = nullptr;
	TArray<FItemInvStruct>& inventory = Storage[CurrentActiveInvTab].StorageTab;

	for (int32 i = 0; i < inventory.Num(); i++)
	{
		if (!inventory[i].bOccupied || !inventory[i].ItemDA || inventory[i].ItemDA != ScrollDA)
			continue;

		scrollDA = Cast<USkillScrollDA>(inventory[i].ItemDA);
		if (!scrollDA)
			continue;

		if(!(GetPlayerStateComponent() && PlayerStateComponent->WasteMana(scrollDA->ManaCost, false)))
		{
			UGameplayStatics::PlaySound2D(this, CooldownSound);
			return;
		}

		UEventBus::OnPlayerSkill.Broadcast(scrollDA);
		ScrollIndex = i;
		
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::CoolDownTimer(FTimerHandle& timerHandle, bool& bIsCoolDown, float& timeCoolDown, float& currentTimeCoolDown)
{
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]()
		{
			if (!IsValid(this))
				return;

			currentTimeCoolDown += 0.1f;

			if(timerHandle == PotionTimer)
				UEventBus::OnPotionCoolDown.ExecuteIfBound(currentTimeCoolDown, timeCoolDown);
			else
				UEventBus::OnScrollCoolDown.ExecuteIfBound(currentTimeCoolDown, timeCoolDown);

			if (currentTimeCoolDown >= timeCoolDown)
			{
				bIsCoolDown = false;
				currentTimeCoolDown = 0.0f;
				GetWorld()->GetTimerManager().ClearTimer(timerHandle);
			}
		}, 0.1f, true);
	
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::UseScroll()
{
	float cooldown = 0.0f;
	USkillScrollDA* scrollDA = nullptr;
	TArray<FItemInvStruct>& inventory = Storage[CurrentActiveInvTab].StorageTab;

	scrollDA = Cast<USkillScrollDA>(inventory[ScrollIndex].ItemDA);
	CHECK_PTR(scrollDA)
	CHECK_PTR(GetPlayerStateComponent())

	PlayerStateComponent->WasteMana(scrollDA->ManaCost, true);

	if (!inventory.IsValidIndex(ScrollIndex))
		return;

	UGameplayStatics::PlaySound2D(this, scrollDA->StartSound);

	if(PlayerStateComponent->GetStateMapElem(EStateName::ScrollSaveChance) < FMath::RandRange(0.0f, 100.0f))
		--inventory[ScrollIndex].ItemCount;

	SetItemFromIndex(inventory[ScrollIndex], CurrentActiveInvTab, ScrollIndex);
	bIsScrollCooldown = true;

	cooldown = PlayerStateComponent->GetStateMapElem(EStateName::DescreaceSkillCooldown) / 100.0f;

	TimeScrollCooldown = scrollDA->Cooldown;
	TimeScrollCooldown -= TimeScrollCooldown * cooldown;

	CoolDownTimer(ScrollTimer, bIsScrollCooldown, TimeScrollCooldown, CurrentTimeScrollCooldown);
	UEventBus::OnScrollCoolDown.ExecuteIfBound(CurrentTimePotionCooldown, TimePotionCooldown);
}
//-----------------------------------------------------------------------------------------------------------
bool UInventoryComponent::DoesHasEmptySlots(int32 numberEmptySlots)
{
	for (const FItemInvStruct& item : Storage[CurrentActiveInvTab].StorageTab)
	{
		if (item.bOccupied)
			continue;

		--numberEmptySlots;
		if (numberEmptySlots <= 0)
			return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------
UPlayerStateComponent* UInventoryComponent::GetPlayerStateComponent()
{
	if (!PlayerStateComponent)
		PlayerStateComponent = GetOwner()->FindComponentByClass<UPlayerStateComponent>();

	return PlayerStateComponent;
}
const FCurrency& UInventoryComponent::GetCurrency()
{
	return Currency;
}
void UInventoryComponent::SetCurrency(FCurrency Value)
{
	Currency = Value;
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::SubtractCurrency(FCurrency Value)
{
	Currency.Sulfur -= Value.Sulfur;
}
//-----------------------------------------------------------------------------------------------------------
bool UInventoryComponent::DoesHaveEnoughCurrency(FCurrency Price)
{
	bool result = true;

	if (Currency.Sulfur < Price.Sulfur)
		result = false;

	return result;
}
//-----------------------------------------------------------------------------------------------------------
bool UInventoryComponent::DoesHaveEnoughItem(UItemMasterDA* ItemDataAsset, int32 Count)
{
	int32 count = Count;

	for (int32 i = 0; i < GetStorage().Num(); ++i)
	{
		if (GetStorage()[i].ItemDA == ItemDataAsset)
		{
			if (GetStorage()[i].ItemCount >= count)
				break;
			else
				count -= GetStorage()[i].ItemCount;
		}

		if (i >= GetStorage().Num() - 1 && count > 0)
			return false; // TODO :: Сообщить что не хватает предметов в инвентаре для покупки
	}
	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::SetItemFromIndex(FItemInvStruct item, int32 indexTab, int32 indexStorage)
{
	Super::SetItemFromIndex(item, indexTab, indexStorage);

	UEventBus::OnUpdateInfoFastSelectorPotion.Broadcast(PotionDA, GetStorage());
	UEventBus::OnUpdateInfoFastSelectorScroll.Broadcast(ScrollDA, GetStorage());
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::ApplyFastDrop(AFPSPlayerController* Controller, int32 Index, UInventorySlotWidget* WidgetSlot)
{
	FastDropStorage = EStorageType::Inventory;
	Super::ApplyFastDrop(Controller, Index, WidgetSlot);


	UEventBus::OnUpdateInfoFastSelectorPotion.Broadcast(PotionDA, GetStorage());
	UEventBus::OnUpdateInfoFastSelectorScroll.Broadcast(ScrollDA, GetStorage());
}
//-----------------------------------------------------------------------------------------------------------
bool UInventoryComponent::PickUpItem(int32& itemCount, UItemMasterDA* itemDA, int32 itemLevel, const FStatValueStruct statValueStruct)
{
	UEventBus::OnUpdateInfoFastSelectorPotion.Broadcast(PotionDA, GetStorage());
	UEventBus::OnUpdateInfoFastSelectorScroll.Broadcast(ScrollDA, GetStorage());

	return Super::PickUpItem(itemCount, itemDA, itemLevel, statValueStruct);
}
bool UInventoryComponent::PickUpItem(const FCurrency& pickUpCurrency)
{
	return Super::PickUpItem(pickUpCurrency);
}
//-----------------------------------------------------------------------------------------------------------