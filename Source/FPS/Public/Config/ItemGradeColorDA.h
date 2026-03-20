#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemGradeColorDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UItemGradeColorDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Grade Color DA") FLinearColor ColorGradeWhite;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Grade Color DA") FLinearColor ColorGradeGreen;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Grade Color DA") FLinearColor ColorGradeBlue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Grade Color DA") FLinearColor ColorGradeEpic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Grade Color DA") FLinearColor ColorGradeLegendary;
};
//-----------------------------------------------------------------------------------------------------------