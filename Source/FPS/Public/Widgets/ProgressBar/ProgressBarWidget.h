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
	void SetValueProgressBar(double CurrentValue, double MaxValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress Bar Widget", meta = (BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(BlueprintReadOnly, Category = "Progress Bar Widget", meta = (BindWidget))
	UTextBlock* ValueTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress Bar Widget")
	FLinearColor ProgressBarColor;
};
//-----------------------------------------------------------------------------------------------------------