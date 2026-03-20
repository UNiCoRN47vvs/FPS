#include "ActorComponents/Upgrade/UpgradeComponent.h"
#include "Subsystem/EventBus.h"
#include "Save/MasterSave.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPerson/FPSGameInstance.h"
//-----------------------------------------------------------------------------------------------------------
void UUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();
	UEventBus::OnUpgradeSave.BindUObject(this, &UUpgradeComponent::SetUpgradeSave);

	FSaveStruct* saveData = nullptr;
	UMasterSave* masterSave = nullptr;
	UFPSGameInstance* gameInstance = nullptr;

	TArray<AActor*> actors = {};

	if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
		return;

	CHECK_CAST(gameInstance, UFPSGameInstance, GetWorld()->GetGameInstance())

	masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

	CHECK_PTR(masterSave)

	saveData = masterSave->MasterSave.Find(gameInstance->GetSaveName());
	CHECK_PTR(saveData)
	Storage = saveData->Upgrade;

	if (!Storage.IsValidIndex(0))
	{
		InvMaxSlots = 2;
		InitStorage();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UEventBus::OnUpgradeSave.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
void UUpgradeComponent::SetUpgradeSave(TArray<FStorageTab>& storage)
{
	storage = Storage;
}
//-----------------------------------------------------------------------------------------------------------