#pragma once

#include "Widgets/MainMenu/MasterMenuWidget.h"
#include "SettingsMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USignboardWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USettingsMenuWidget : public UMasterMenuWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* BackSignboard;
};
//-----------------------------------------------------------------------------------------------------------