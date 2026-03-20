#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/CurrencyStruct.h"
#include "QuestMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemReward
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Reward") int32 ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Reward") TSoftObjectPtr<UItemMasterDA> ItemDA;
};
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FRewards
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rewards") FCurrency CurrencyReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rewards") TArray<FItemReward> ItemRewards;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestMasterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") int32 UnicQuestLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") FText QuestName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") FText QuestDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") int32 QuestMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") TSoftObjectPtr<UQuestMasterDA> QuestRequirement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") TArray<TSoftObjectPtr<UPrimaryDataAsset>> QuestTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_M_DA") FRewards QuestReward;
	
};
//-----------------------------------------------------------------------------------------------------------