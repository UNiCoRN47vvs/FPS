#pragma once

#include "CoreMinimal.h"
#include "QuestStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UQuestMasterDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest") int32 CurrentCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest") int32 MaxCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest") UQuestMasterDA* QuestMasterDA = nullptr;
};
//-----------------------------------------------------------------------------------------------------------