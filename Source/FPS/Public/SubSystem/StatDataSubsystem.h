#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Struct/StatData.h"
#include "Struct/StatGradeData.h"
#include "Struct/CraftCreationRecipe.h"
#include "Struct/CraftModificationRecipe.h"
#include "StatDataSubsystem.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStatDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static TArray<FStatData> StatArray;
	static TArray<FStatGradeData> StatGradeArray;
	static TMap<FName, FCraftCreationRecipe> CreationRecipeMap;
	static TMap<FName, FCraftModificationRecipe> ModificationRecipeMap;
};
//-----------------------------------------------------------------------------------------------------------