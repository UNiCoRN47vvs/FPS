#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "ControlSettingsBoxWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UInputKeySelector;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UControlSettingsBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitBox(const FName& mappingName, const FText& text, const FKey& key);
	UFUNCTION() void SetBoxInformation(FInputChord inputChord);

	UPROPERTY(BlueprintReadOnly, Category = "C_S_B_W", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(BlueprintReadOnly, Category = "C_S_B_W", meta = (BindWidget)) UInputKeySelector* InputKeySelector;
protected:
	FName MappingName;
};
//-----------------------------------------------------------------------------------------------------------