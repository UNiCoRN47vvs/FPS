#pragma once

#include "FPS/FPS.h"
#include "Widgets/MainMenu/SettingsMenuWidget.h"
#include "ControlSettingsWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UControlSettingsBoxWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UControlSettingsWidget : public USettingsMenuWidget
{
	GENERATED_BODY()
public:
	void InitControlWidget();

	UPROPERTY(BlueprintReadOnly, Category = "C_S_W", meta = (BindWidget)) UVerticalBox* VerticalBox;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_S_W") TSubclassOf<UControlSettingsBoxWidget> BoxWidget;
};
//-----------------------------------------------------------------------------------------------------------