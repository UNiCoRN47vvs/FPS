#include "SubSystem/StatDataSubsystem.h"
//-----------------------------------------------------------------------------------------------------------
TArray<FStatData> UStatDataSubsystem::StatArray;
TArray<FStatGradeData> UStatDataSubsystem::StatGradeArray;
//-----------------------------------------------------------------------------------------------------------
TMap<FName, FCraftCreationRecipe> UStatDataSubsystem::CreationRecipeMap;
TMap<FName, FCraftModificationRecipe> UStatDataSubsystem::ModificationRecipeMap;