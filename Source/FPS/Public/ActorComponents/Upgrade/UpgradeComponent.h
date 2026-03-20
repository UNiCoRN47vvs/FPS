#pragma once

#include "ActorComponents/StorageComponent.h"
#include "UpgradeComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class FPS_API UUpgradeComponent : public UStorageComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	void SetUpgradeSave(TArray<FStorageTab>& storage);
};
//-----------------------------------------------------------------------------------------------------------