#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UNPCDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPSDA") FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPSDA") FString InteractButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPSDA") FString IteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCDA") UDataTable* ItemsForSaleDataTable;
};
//-----------------------------------------------------------------------------------------------------------