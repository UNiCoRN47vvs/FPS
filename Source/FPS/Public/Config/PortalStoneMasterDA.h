#pragma once

#include "Config/SuppliesMasterDA.h"
#include "Struct/StatValueStruct.h"
#include "PortalStoneMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPortalStoneMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual TMap<FString, FText> GetItemInfo() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Stone") int32 SpawnEnemyAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Stone") int32 SpawnEnemyWave;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Stone") FStatValueStruct StatsValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Stone") TSoftObjectPtr<UWorld> PortalLevel;
};
