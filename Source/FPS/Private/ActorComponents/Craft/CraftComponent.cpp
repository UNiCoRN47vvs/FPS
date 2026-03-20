#include "ActorComponents/Craft/CraftComponent.h"
#include "SubSystem/EventBus.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPerson/FPSGameInstance.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Config/RuneMasterDA.h"
#include "Save/MasterSave.h"
#include "Widgets/Craft/CraftWidget.h"
//-----------------------------------------------------------------------------------------------------------
#define CHECK_CRAFT_INFO(BOOL)\
       if (BOOL) {\
			CraftEvent(false);\
			return false;\
           }
//-----------------------------------------------------------------------------------------------------------
void UCraftComponent::BeginPlay()
{
	Super::BeginPlay();
	UEventBus::OnGeneralWidgetClose.AddUObject(this, &UCraftComponent::DestroyCraftComponent);

	UMasterSave* masterSave = nullptr;
	FSaveStruct* saveData = nullptr;
	
	CHECK_CAST(GameInstance, UFPSGameInstance, GetOwner()->GetGameInstance())

	masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

	CHECK_PTR(masterSave)

	saveData = masterSave->MasterSave.Find(GameInstance->GetSaveName());
	CHECK_PTR(saveData)

	if(!saveData->Craft.IsEmpty())
		Storage = saveData->Craft;
}
//-----------------------------------------------------------------------------------------------------------
void UCraftComponent::DestroyCraftComponent()
{
	UEventBus::OnGeneralWidgetClose.RemoveAll(this);

	Deactivate();
	DestroyComponent();
}
//-----------------------------------------------------------------------------------------------------------
void UCraftComponent::Craft(UCraftWidget* craftWidget)
{
	CraftWidget = craftWidget;

	if (CreationCraft())
		return;

	if (ModificationCraft())
		return;
}
//-----------------------------------------------------------------------------------------------------------
bool UCraftComponent::CreationCraft()
{
	int32 randomIdex = 0;
	int32 recipePrice = 0;
	UItemMasterDA* itemDA = nullptr;
	UInventoryComponent* inventoryComponent = nullptr;
	FString pathNames = {};
	FItemInvStruct invStruct = {};
	FCraftCreationRecipe creationRecipe = {};
	TSoftObjectPtr<UItemMasterDA> softItemDA = {};
	TArray<int32> indexesArray = {};
	TArray<FString> pathNamesArray = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;
	TArray<TPair<TSoftObjectPtr<UItemMasterDA>, int32>> mapArray = {};

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		if (!storage[i].bOccupied || !storage[i].ItemDA)
			continue;

		pathNamesArray.Add(storage[i].ItemDA->GetPathName());
		indexesArray.Add(i);
	}

	pathNamesArray.Sort();

	for (const FString& item : pathNamesArray)
	{
		pathNames += item;
	}

	if (!UStatDataSubsystem::CreationRecipeMap.Contains(FName(*pathNames)))
		return false;

	creationRecipe = *UStatDataSubsystem::CreationRecipeMap.Find(FName(*pathNames));

	for (const int32 item : indexesArray)
	{
		softItemDA = storage[item].ItemDA;

		recipePrice = *creationRecipe.RecipePrice.Find(softItemDA);

		CHECK_CRAFT_INFO(storage[item].ItemCount < recipePrice)
	}

	inventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
	CHECK_CRAFT_INFO(!inventoryComponent)

	switch (creationRecipe.CraftAction)
	{
	case ECraftAction::Giver:
		CHECK_CRAFT_INFO(!inventoryComponent->DoesHasEmptySlots(creationRecipe.Items.Num()))

		for (auto& item : creationRecipe.Items)
		{
			itemDA = item.Key.LoadSynchronous();
			if (!itemDA)
				continue;

			inventoryComponent->PickUpItem(item.Value, itemDA, 0, itemDA->StatStruct.FindRandomStatWithRandomValue(itemDA->ItemGrade));
		}
		break;

	case ECraftAction::RandomGiver:
		CHECK_CRAFT_INFO(!inventoryComponent->DoesHasEmptySlots(1))

		mapArray = creationRecipe.Items.Array();
		randomIdex = FMath::RandRange(0, creationRecipe.Items.Num() - 1);
		CHECK_CRAFT_INFO(!mapArray.IsValidIndex(randomIdex))

		itemDA = mapArray[randomIdex].Key.LoadSynchronous();
		CHECK_CRAFT_INFO(!itemDA)

		inventoryComponent->PickUpItem(mapArray[randomIdex].Value, itemDA, 0, itemDA->StatStruct.FindRandomStatWithRandomValue(itemDA->ItemGrade));
		break;

	default:
		break;
	}


	for (const int32 item : indexesArray)
	{
		softItemDA = storage[item].ItemDA;

		recipePrice = *creationRecipe.RecipePrice.Find(softItemDA);

		storage[item].ItemCount -= recipePrice;

		SetItemFromIndex(storage[item], CurrentActiveInvTab, item);
	}

	CraftEvent(true);

	return true;
}
//-----------------------------------------------------------------------------------------------------------
bool UCraftComponent::ModificationCraft()
{
	bool bFirstCheck = false;
	int32 recipePrice = 0;
	TArray<int32> runeIndexes = {};
	EItemGrade currentItemGrade = EItemGrade::MAX;
	URuneMasterDA* runeDA = nullptr;
	UInventoryComponent* inventoryComponent = nullptr;
	FString pathNames = {};
	FText runeText = {};
	FCraftModificationRecipe modificationRecipe = {};
	TSoftObjectPtr<UItemMasterDA> softItemDA = {};
	TArray<int32> indexesArray = {};
	TArray<FString> pathNamesArray = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		if (!storage[i].bOccupied || !storage[i].ItemDA) 
			continue;

		CHECK_CRAFT_INFO(currentItemGrade != EItemGrade::MAX && currentItemGrade != storage[i].ItemDA->ItemGrade)

		currentItemGrade = storage[i].ItemDA->ItemGrade;

		switch (storage[i].ItemDA->ItemType)
		{
		case EItemType::Rune :
			runeIndexes.Add(i);
			pathNamesArray.Add(storage[i].ItemDA->GetPathName());
			break;
		default:
			break;
		}

		if (storage[i].ItemDA->ItemType != EItemType::Rune)
		{
			CHECK_CRAFT_INFO(bFirstCheck)

			bFirstCheck = true;
		}

		indexesArray.Add(i);
	}

	CHECK_CRAFT_INFO(runeIndexes.IsEmpty() || indexesArray.Num() <= 1)

	runeDA = Cast<URuneMasterDA>(storage[runeIndexes[0]].ItemDA);
	CHECK_CRAFT_INFO(!runeDA)

	pathNamesArray.Sort();

	for (const FString& item : pathNamesArray)
	{
		pathNames += item;
	}

	ENUM_TO_TEXT(runeDA->TargetItemType, EItemType, runeText)

	pathNames += runeText.ToString();

	CHECK_CRAFT_INFO(!UStatDataSubsystem::ModificationRecipeMap.Contains(FName(*pathNames)))

	modificationRecipe = *UStatDataSubsystem::ModificationRecipeMap.Find(FName(*pathNames));

	for (const int32 item : indexesArray)
	{
		CHECK_CRAFT_INFO(storage[item].ItemDA->ItemType != runeDA->ItemType && runeDA->TargetItemType != EItemType::All && runeDA->TargetItemType != storage[item].ItemDA->ItemType)
		
		softItemDA = storage[item].ItemDA;
		if (!modificationRecipe.RecipeItems.Contains(softItemDA))
			continue;

		recipePrice = *modificationRecipe.RecipeItems.Find(softItemDA);

		CHECK_CRAFT_INFO(storage[item].ItemCount < recipePrice)
	}

	inventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
	CHECK_CRAFT_INFO(!inventoryComponent)

	CHECK_CRAFT_INFO(!inventoryComponent->DoesHasEmptySlots(1))
	switch (modificationRecipe.CraftAction)
	{
	case ECraftAction::RandomGiver:
		return ModificationCraftRandomGiver(inventoryComponent, modificationRecipe, indexesArray);
		break;

	case ECraftAction::AddStat:
		return AddStat(inventoryComponent, modificationRecipe, indexesArray);
			break;

	case ECraftAction::RemoveStat:
		return RemoveStat(inventoryComponent, modificationRecipe, indexesArray);
		break;

	default:
		break;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------
bool UCraftComponent::ModificationCraftRandomGiver(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray)
{
	int32 recipePrice = 0;
	int32 randomIdex = 0;
	UItemMasterDA* itemDA = nullptr;
	TSoftObjectPtr<UItemMasterDA> softItemDA = {};
	TArray<TPair<TSoftObjectPtr<UItemMasterDA>, int32>> mapArray = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;

	mapArray = modificationRecipe.GiverItems.Array();
	randomIdex = FMath::RandRange(0, modificationRecipe.GiverItems.Num() - 1);
	CHECK_CRAFT_INFO(!mapArray.IsValidIndex(randomIdex))

	itemDA = mapArray[randomIdex].Key.LoadSynchronous();
	CHECK_CRAFT_INFO(!itemDA)

	inventoryComponent->PickUpItem(mapArray[randomIdex].Value, itemDA, 0, itemDA->StatStruct.FindRandomStatWithRandomValue(itemDA->ItemGrade));

	for (const int32 item : indexesArray)
	{
		recipePrice = 1;

		softItemDA = storage[item].ItemDA;
		itemDA = softItemDA.LoadSynchronous();
		CHECK_CRAFT_INFO(!itemDA)
		
		if (itemDA->ItemType == EItemType::Rune)
			recipePrice = *modificationRecipe.RecipeItems.Find(softItemDA);

		storage[item].ItemCount -= recipePrice;

		SetItemFromIndex(storage[item], CurrentActiveInvTab, item);
	}

	CraftEvent(true);
	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UCraftComponent::CraftEvent(bool bIsSuccess)
{
	if (bIsSuccess)
		UGameplayStatics::PlaySound2D(this, SuccessCraftSound);
	else
		UGameplayStatics::PlaySound2D(this, FailCraftSound);
	
	PTR(CraftWidget)->CraftEvent(bIsSuccess);
}
//-----------------------------------------------------------------------------------------------------------
bool UCraftComponent::AddStat(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray)
{
	bool bIsFindIgnore = false;
	int32 itemIndex = 0;
	int32 randomIndex = 0;
	int32 recipePrice = 0;
	UItemMasterDA* itemDA = nullptr;
	TSoftObjectPtr<UItemMasterDA> softItemDA = {};
	FItemInvStruct currentItem = {};
	TArray<EStateName> stateNames = {};
	TArray<float> valueArray = {};
	TArray<EStateName> stateNamesIgnore = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;
	const TArray<FStatData>& statArray = UStatDataSubsystem::StatArray;
	const TArray<FStatGradeData>& statGradeArray = UStatDataSubsystem::StatGradeArray;

	
	for (const int32 item : indexesArray)
	{
		if (storage[item].ItemDA && storage[item].ItemDA->ItemType != EItemType::Rune)
		{
			itemIndex = item;
			break;
		}
	}
	
	currentItem = storage[itemIndex];

	CHECK_CRAFT_INFO(!statGradeArray[static_cast<int32>(currentItem.ItemDA->ItemGrade)].StatCounts.Contains(modificationRecipe.StatTag))

	for (const auto& item : currentItem.StatValue.StatsValue)
	{
		if (statArray.IsValidIndex(static_cast<int32>(item.Key)) && statArray[static_cast<int32>(item.Key)].GameplayTag.HasTag(modificationRecipe.StatTag))
			stateNamesIgnore.Add(item.Key);
	}

	CHECK_CRAFT_INFO(stateNamesIgnore.Num() >= *statGradeArray[static_cast<int32>(currentItem.ItemDA->ItemGrade)].StatCounts.Find(modificationRecipe.StatTag))

	for (auto& item : currentItem.ItemDA->StatStruct.StatsMap)
	{
		bIsFindIgnore = false;

		for (EStateName subItem : stateNamesIgnore)
		{
			if(item.Key == subItem)
				bIsFindIgnore = true;
		}
		
		if (bIsFindIgnore || !statArray[static_cast<int32>(item.Key)].GameplayTag.HasTag(modificationRecipe.StatTag))
			continue;

		stateNames.Add(item.Key);
		valueArray.Add(item.Value.GetValueFromRange());
	}

	randomIndex = FMath::RandRange(0, stateNames.Num() - 1);

	CHECK_CRAFT_INFO(stateNames.IsEmpty() || !stateNames.IsValidIndex(randomIndex))

	currentItem.StatValue.StatsValue.Add(statArray[static_cast<int32>(stateNames[randomIndex])].StatName, valueArray[randomIndex]);

	inventoryComponent->PickUpItem(currentItem.ItemCount, currentItem.ItemDA, currentItem.ItemLevel, currentItem.StatValue);

	for (const int32 item : indexesArray)
	{
		recipePrice = 1;

		softItemDA = storage[item].ItemDA;
		itemDA = softItemDA.LoadSynchronous();
		CHECK_CRAFT_INFO(!itemDA)

			if (itemDA->ItemType == EItemType::Rune)
				recipePrice = *modificationRecipe.RecipeItems.Find(softItemDA);

		storage[item].ItemCount -= recipePrice;

		SetItemFromIndex(storage[item], CurrentActiveInvTab, item);
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------
bool UCraftComponent::RemoveStat(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray)
{
	bool bIsFindIgnore = false;
	int32 itemIndex = 0;
	int32 randomIndex = 0;
	int32 recipePrice = 0;
	UItemMasterDA* itemDA = nullptr;
	TSoftObjectPtr<UItemMasterDA> softItemDA = {};
	FItemInvStruct currentItem = {};
	TArray<EStateName> stateNames = {};
	TArray<float> valueArray = {};
	TArray<EStateName> stateNamesIgnore = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;
	const TArray<FStatData>& statArray = UStatDataSubsystem::StatArray;
	const TArray<FStatGradeData>& statGradeArray = UStatDataSubsystem::StatGradeArray;

	for (const int32 item : indexesArray)
	{
		if (storage[item].ItemDA && storage[item].ItemDA->ItemType != EItemType::Rune)
		{
			itemIndex = item;
			break;
		}
	}

	currentItem = storage[itemIndex];

	currentItem.StatValue.StatsValue.GetKeys(stateNames);

	randomIndex = FMath::RandRange(0, stateNames.Num() - 1);

	CHECK_CRAFT_INFO(stateNames.IsEmpty() || !stateNames.IsValidIndex(randomIndex))

	currentItem.StatValue.StatsValue.Remove(stateNames[randomIndex]);

	inventoryComponent->PickUpItem(currentItem.ItemCount, currentItem.ItemDA, currentItem.ItemLevel, currentItem.StatValue);

	for (const int32 item : indexesArray)
	{
		recipePrice = 1;

		softItemDA = storage[item].ItemDA;
		itemDA = softItemDA.LoadSynchronous();
		CHECK_CRAFT_INFO(!itemDA)

			if (itemDA->ItemType == EItemType::Rune)
				recipePrice = *modificationRecipe.RecipeItems.Find(softItemDA);

		storage[item].ItemCount -= recipePrice;

		SetItemFromIndex(storage[item], CurrentActiveInvTab, item);
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------
