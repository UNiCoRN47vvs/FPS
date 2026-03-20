
#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "InformationTextWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInformationTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitValueText(FText Text);
	bool IsTextEmpty();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "I_T_W") FText NameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "I_T_W", meta = (BindWidget)) UTextBlock* NameTB;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "I_T_W", meta = (BindWidget)) UTextBlock* ValueTB;

	
};
//-----------------------------------------------------------------------------------------------------------