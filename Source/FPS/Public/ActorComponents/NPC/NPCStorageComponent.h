#pragma once

#include "ActorComponents/StorageComponent.h"
#include "NPCStorageComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
struct FItemForSaleStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPS_API UNPCStorageComponent : public UStorageComponent
{
	GENERATED_BODY()
public:
	void InitNPCStorage(UDataTable* dataTable);
	void RefreshStore();

	UPROPERTY() UDataTable* ItemDataTable;
	TArray<FItemForSaleStruct*> ItemsPrice;
	TMulticastDelegate<void()> OnRefreshStore;
};
//-----------------------------------------------------------------------------------------------------------