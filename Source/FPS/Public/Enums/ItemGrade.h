#pragma once

#include "CoreMinimal.h"
#include "ItemGrade.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	//Новый тип добавить в UpgradeWidget в Array
	White UMETA(DisplayName = "White"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	MAX UMETA(Hidden)
};
