#pragma once

#include "Widgets/MainMenu/SettingsMenuWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "GraphicsBoxWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USignboardWidget;
class UGraphicsWidget;
class UComboBoxString;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UGraphicsBoxWidget : public USettingsMenuWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UComboBoxString* ResolutionCB;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UComboBoxString* FullscreenModeCB;

	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* ViewDistance;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* AntiAliasing;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* PostProcessing;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Shadows;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* GlobalIllumination;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Reflections;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Textures;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Effects;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Foliage;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* Shading;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* VSync;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* FrameLimits;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* FrameRate;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* AntiAliasingMethod;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UGraphicsWidget* MSAACount;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION() void OnFullscreenModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
//-----------------------------------------------------------------------------------------------------------