#include "Struct/StatStruct.h"
#include "SubSystem/StatDataSubsystem.h"
//-----------------------------------------------------------------------------------------------------------
FStatValueStruct FStatStruct::FindRandomStatWithRandomValue(EItemGrade itemGrade)
{
	bool bIsFindTag = false;
	int32 randomIndex = 0;
	int32 stopCount = 0;
	EStateName currentStateName = {};
	FStatRange* statRange = nullptr;
	FStatValueStruct statValue = {};
	FGameplayTag gameplayTag = {};
	FStatGradeData statGradeData = {};
	TArray<EStateName> mapKeys = {};

	statGradeData = UStatDataSubsystem::StatGradeArray[static_cast<int32>(itemGrade)];
	
	StatsMap.GetKeys(mapKeys);

	for (const auto& item : statGradeData.StatCounts)
	{
		stopCount += item.Value;
	}

	while (stopCount > 0 && !mapKeys.IsEmpty())
	{
		bIsFindTag = false;
		randomIndex = FMath::RandRange(0, mapKeys.Num() - 1);
		currentStateName = mapKeys[randomIndex];
		mapKeys.RemoveAt(randomIndex);

		for (const auto& item : statGradeData.StatCounts)
		{
			if (UStatDataSubsystem::StatArray[static_cast<int32>(currentStateName)].GameplayTag.HasTag(item.Key) && item.Value > 0)
			{
				bIsFindTag = true;
				gameplayTag = item.Key;
				break;
			}
		}

		if (!bIsFindTag || !StatsMap.Contains(currentStateName))
		{
			gameplayTag = {};
			continue;
		}

		statRange = StatsMap.Find(currentStateName);

		*statGradeData.StatCounts.Find(gameplayTag) -= 1;

		statValue.StatsValue.Add(currentStateName, statRange->GetValueFromRange());

		//switch (mapKeys[randomIndex])
		//{
		//case EStateName::ColdResistance :
		//	break;
		//	//TODO : добавить специфические параметры. 1% шанс отхилить 5 хп, или что-то типо такого.
		//default:
		//	break;
		//}

		--stopCount;
		gameplayTag = {};

		if (FMath::RandRange(1, 3) == 3)
			break;
	}

   return statValue;
}
//-----------------------------------------------------------------------------------------------------------