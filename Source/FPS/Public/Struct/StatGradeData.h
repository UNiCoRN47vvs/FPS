#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enums/ItemGrade.h"
#include "StatGradeData.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStatGradeData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_G_D") EItemGrade StatName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_G_D") TMap<FGameplayTag, int32> StatCounts;

};
//-----------------------------------------------------------------------------------------------------------