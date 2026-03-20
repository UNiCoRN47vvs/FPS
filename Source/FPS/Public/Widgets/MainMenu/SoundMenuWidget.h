#pragma once

#include "Widgets/MainMenu/SettingsMenuWidget.h"
#include "SoundMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UGraphicsWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USoundMenuWidget : public USettingsMenuWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "S_M_W", meta = (BindWidget)) UGraphicsWidget* SoundMaster;
	UPROPERTY(BlueprintReadOnly, Category = "S_M_W", meta = (BindWidget)) UGraphicsWidget* SoundEffect;
	UPROPERTY(BlueprintReadOnly, Category = "S_M_W", meta = (BindWidget)) UGraphicsWidget* SoundMusic;
};
//-----------------------------------------------------------------------------------------------------------