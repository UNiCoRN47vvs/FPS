#include "Widgets/Portal/PortalWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/WorldRuler.h"
#include "FPS/FPSPlayerController.h"
#include "ActorComponents/Portal/PortalComponent.h"
#include "Interact/Portal/Portal.h"
#include "Items/Supplies/PortalStoneMaster.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Struct/ItemDataStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UPortalWidget::InitPortalWidget(UPortalComponent* storageComponent)
{
	if (storageComponent)
	{
		StorageComp = storageComponent;
		const TArray<FItemInvStruct>& storage = storageComponent->GetStorage();
		PortalComponent = storageComponent;
	
		PortalSlot->StorageComponent = storageComponent;
		PortalSlot->UpdateInvSlot(storage[0].ItemDA ? storage[0].ItemDA->ItemIcon : nullptr, storage[0].ItemCount);

		PortalButton->OnClicked.AddDynamic(this, &UPortalWidget::CheckAndOpenPortal);
		FreePortalButton->OnClicked.AddDynamic(this, &UPortalWidget::OpenFreePortal);
	}else
		ALARM_LOG
}
//-----------------------------------------------------------------------------------------------------------
void UPortalWidget::UpdateSlots()
{
	CHECK_PTR(StorageComp)
	CHECK_PTR(StorageComp->GetStorage()[0].ItemDA)

	PortalSlot->UpdateInvSlot(StorageComp->GetStorage()[0].ItemDA->ItemIcon, StorageComp->GetStorage()[0].ItemCount);
}
//-----------------------------------------------------------------------------------------------------------
void UPortalWidget::CheckAndOpenPortal()
{
	int32 itemLevel = 0;
	AFPSPlayerController* playerController = nullptr;
	APortal* portal = nullptr;
	UPortalStoneMasterDA* portalStoneDA = nullptr;
	TSoftObjectPtr<UWorld> portalLevel = nullptr;
	UWorldRuler* worldRuler = nullptr;
	EItemGrade grade = {};
	const FItemInvStruct& item = PortalSlot->StorageComponent->GetStorage()[PortalSlot->Index];

	CHECK_PTR(item.ItemDA)

	worldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
	CHECK_PTR(worldRuler)

	if (worldRuler->GetPortalStat().bIsExist)
	{
		RemoveCurrentDungeonPortal(worldRuler, FName("CheckAndOpenPortal"));
		return;
	}

	grade = item.ItemDA->ItemGrade;

	if (item.ItemDA->ItemType != EItemType::PortalDungeon)
		return; //Проиграть анимацию неудачи

	playerController = Cast<AFPSPlayerController>(GetOwningPlayer());

	CHECK_PTR(playerController)

	portalStoneDA = Cast<UPortalStoneMasterDA>(item.ItemDA);

	CHECK_PTR(portalStoneDA)

	portalLevel = portalStoneDA->PortalLevel;
	itemLevel = item.ItemLevel;

	portal = Cast<APortal>(UGameplayStatics::GetActorOfClass(this, APortal::StaticClass()) );
	CHECK_PTR(portal)

	PortalSlot->StorageComponent->SetItemFromIndex(FItemInvStruct{}, PortalSlot->StorageComponent->CurrentActiveInvTab, 0);
	portal->OpenPortal(playerController, portalLevel, grade);

	worldRuler->SetPortalStat(portalStoneDA, itemLevel);
}
//-----------------------------------------------------------------------------------------------------------
void UPortalWidget::OpenFreePortal()
{
	CHECK_PTR(DTPortalStones)

	AFPSPlayerController* playerController = nullptr;
	APortal* portal = nullptr;
	UPortalStoneMasterDA* portalStoneDA = nullptr;
	TSoftObjectPtr<UWorld> portalLevel = nullptr;
	UWorldRuler* worldRuler = nullptr;
	FItemDataStruct* dataStruct = nullptr;
	EItemGrade grade = {};
	
	TArray<FItemDataStruct*> portales = {};
	TArray<FName> rowNames = DTPortalStones->GetRowNames();
	const FItemInvStruct& slot = PortalSlot->StorageComponent->GetStorage()[PortalSlot->Index];

	if (slot.ItemDA)
		return; //TODO : Добавить анимацию отказа.

	worldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
	CHECK_PTR(worldRuler)

	if (worldRuler->GetPortalStat().bIsExist)
	{
		RemoveCurrentDungeonPortal(worldRuler, FName("OpenFreePortal"));
		return;
	}

	for (FName& LocalItem : rowNames)
	{
		dataStruct = DTPortalStones->FindRow<FItemDataStruct>(LocalItem, TEXT(""));
		if (dataStruct && dataStruct->ItemGrade == EItemGrade::White)
			portales.Add(dataStruct);
	}

	playerController = Cast<AFPSPlayerController>(GetOwningPlayer());
	CHECK_PTR(playerController)

	portalStoneDA = Cast<UPortalStoneMasterDA>(portales[FMath::RandRange(0, portales.Num() - 1)]->DataAsset.LoadSynchronous());
	CHECK_PTR(portalStoneDA)

	grade = portalStoneDA->ItemGrade;
	portalLevel = portalStoneDA->PortalLevel;

	portal = Cast<APortal>(UGameplayStatics::GetActorOfClass(this, APortal::StaticClass()));
	CHECK_PTR(portal)


	portal->OpenPortal(playerController, portalLevel, grade);

	worldRuler->SetPortalStat(portalStoneDA, 0);
}
//-----------------------------------------------------------------------------------------------------------
void UPortalWidget::RemoveCurrentDungeonPortal(UWorldRuler* worldRuler,const FName& functionName)
{
	FLatentActionInfo latentInfo = {};

	CHECK_PTR(worldRuler)

	latentInfo.CallbackTarget = this;
	latentInfo.ExecutionFunction = functionName;
	latentInfo.Linkage = 0;
	latentInfo.UUID = __LINE__;

	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, worldRuler->CurrentDungeon, latentInfo, false);
	worldRuler->ResetDungeon();
	worldRuler->SetPortalStat(nullptr, 0);
	worldRuler->CurrentDungeon = nullptr;
}
//-----------------------------------------------------------------------------------------------------------