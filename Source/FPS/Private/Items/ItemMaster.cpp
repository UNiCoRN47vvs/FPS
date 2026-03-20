#include "Items/ItemMaster.h"
#include "Character/CharacterMaster.h"
//-----------------------------------------------------------------------------------------------------------
AItemMaster::AItemMaster()
{
	PrimaryActorTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void AItemMaster::BeginPlay()
{
	Super::BeginPlay();
	if (ItemCount <= 0)
		ItemCount = 1;

	InitParams();
}
//-----------------------------------------------------------------------------------------------------------
void AItemMaster::InitParams(UItemMasterDA* ItemDA)
{
	if (ItemDA)
		DataAssetConfig = ItemDA;

	UItemMasterDA* itemDA = GetConfigDA<UItemMasterDA>();
	CHECK_PTR(itemDA)

	InteractInfo.ItemName = itemDA->ItemName.ToString();
	InteractInfo.InteractButton = itemDA->InteractButton;
	InteractInfo.IteractAction = itemDA->IteractAction;

}
//-----------------------------------------------------------------------------------------------------------
//Getter
FItemStructMaster AItemMaster::GetItemInfo()
{
	FItemStructMaster itemInfo = {};
	UItemMasterDA* dataAsset = GetConfigDA<UItemMasterDA>();
	if (dataAsset)
	{
		itemInfo.ItemClass = dataAsset->ItemClass;
		itemInfo.ItemCount = ItemCount;
		itemInfo.ItemCountMax = dataAsset->ItemCountMax;
		itemInfo.ItemDesc = dataAsset->ItemDesc;
		itemInfo.ItemIcon = dataAsset->ItemIcon;
		itemInfo.ItemName = dataAsset->ItemName;
		itemInfo.ItemType = dataAsset->ItemType;
		itemInfo.ItemWeight = dataAsset->ItemWeight;
	}

	return itemInfo;
}
FInteractStruct AItemMaster::GetInteractInfo()
{
	return InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------
void AItemMaster::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	CHECK_PTR(PlayerCharacter)

	UItemMasterDA* suppliesDA = GetConfigDA<UItemMasterDA>();
	CHECK_PTR(suppliesDA)

		if (PlayerCharacter->PickUpItem(ItemCount, suppliesDA))
			Destroy();
}
//-----------------------------------------------------------------------------------------------------------