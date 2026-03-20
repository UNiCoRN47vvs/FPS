#pragma once

#include "ActorComponents/StorageComponent.h"
#include "SubSystem/StatDataSubsystem.h"
#include "CraftComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UFPSGameInstance;
class UCraftWidget;
class UInventoryComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPS_API UCraftComponent : public UStorageComponent
{
	GENERATED_BODY()
public:
	void Craft(UCraftWidget* craftWidget);
protected:
	virtual void BeginPlay() override;
	void DestroyCraftComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C") USoundWave* SuccessCraftSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C") USoundWave* FailCraftSound;

	UPROPERTY() UFPSGameInstance* GameInstance;
	UPROPERTY() UCraftWidget* CraftWidget;
private:
	bool CreationCraft();
	bool ModificationCraft();
	bool ModificationCraftRandomGiver(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray);
	void CraftEvent(bool bIsSuccess);
	bool AddStat(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray);
	bool RemoveStat(UInventoryComponent* inventoryComponent, FCraftModificationRecipe& modificationRecipe, TArray<int32>& indexesArray);
};
//-----------------------------------------------------------------------------------------------------------