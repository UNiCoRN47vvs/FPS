#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ProgressBarWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetValueProgressBar(float currentValue, float maxValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "P_B_W", meta = (BindWidget))	UProgressBar* ProgressBar;
	UPROPERTY(BlueprintReadOnly, Category = "P_B_W", meta = (BindWidget))	UTextBlock* ValueTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "P_B_W")	FLinearColor ProgressBarColor;
};
//-----------------------------------------------------------------------------------------------------------