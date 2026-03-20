#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "EscapeMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USignboardWidget;
class UMainMenuWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEscapeMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escape Menu Widget", meta = (Bindwidget)) USignboardWidget* ResumeSignboard;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escape Menu Widget", meta = (Bindwidget)) UMainMenuWidget* SettingsSignboard;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escape Menu Widget", meta = (Bindwidget)) USignboardWidget* ExitSignboard;
protected:
	UFUNCTION() void ApplyResumeButton();
	UFUNCTION() void ApplyExitButton();
	UFUNCTION() void ShowHideSignboard();
};
//-----------------------------------------------------------------------------------------------------------