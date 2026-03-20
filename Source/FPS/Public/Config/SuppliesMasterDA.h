#pragma once

#include "CoreMinimal.h"
#include "Config/ItemMasterDA.h"
#include "SuppliesMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USuppliesMasterDA : public UItemMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Master")	TSoftObjectPtr<UStaticMesh> StaticMesh;
};
//-----------------------------------------------------------------------------------------------------------