#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestsDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UQuestMasterDA;
struct FQuest;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestsDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quests DA") TArray<FQuest> QuestsDA;
};
//-----------------------------------------------------------------------------------------------------------