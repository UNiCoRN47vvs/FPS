#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UVerticalBox;
class USignboardWidget;
class AMainMenuController;
class FWidgetAnimationDynamicEvent;
class UCreateNewGameWidget;
class UMasterSave;
class ULoadGameWidget;
class UMasterMenuWidget;
class UGraphicsBoxWidget;
class USoundMenuWidget;
class UControlSettingsWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UseButton(UVerticalBox* currentVerticalBox, UVerticalBox* futureVerticalBox);
	//&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&

	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* MainVB;

	//&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&

	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* NewGameSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* NewGameVB;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W") UCreateNewGameWidget* CreateNewGameMenu;

	//&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&

	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* LoadGameSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* LoadGameVB;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W") ULoadGameWidget* LoadGameWidget;

	//&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&

	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* SettingsSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* SettingsVB;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* GraphicsSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* GraphicsVB;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W") UGraphicsBoxWidget* GraphicsBox;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* SoundSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* SoundVB;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W") USoundMenuWidget* SoundBox;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* ControlSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) UVerticalBox* ControlVB;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W") UControlSettingsWidget* ControlBox;
	//********************************************
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) USignboardWidget* SettingsBackSignboard;
	
	//&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&M_M_W-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&-&

	UPROPERTY(BlueprintReadOnly, Category = "Main Menu Widget", meta = (BindWidget)) USignboardWidget* ExitSignboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSoftObjectPtr<UWorld> MainWorld;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSubclassOf<UCreateNewGameWidget> NewGameWClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSubclassOf<ULoadGameWidget> LoadGameWClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSubclassOf<UGraphicsBoxWidget> GraphicsClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSubclassOf<USoundMenuWidget> SoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_M_W") TSubclassOf<UControlSettingsWidget> ControlClass;

protected:
	virtual void NativeConstruct() override;
	void ShowHideVerticalBox(UVerticalBox* VerticalBox, bool bIsShow);
	//********************************************
	UFUNCTION() void UseNewGameButton();
	UFUNCTION() void UseNewGameEnterButton();
	UFUNCTION() void UseNewGameBackButton();
	//********************************************
	UFUNCTION() void UseLoadGameButton();
	UFUNCTION() void UseLoadGameBackButton();
	//********************************************
	UFUNCTION() void UseSettingsButton();
	UFUNCTION() void UseGraphicsButton();
	UFUNCTION() void UseGraphicsBackButton();
	UFUNCTION() void UseSoundButton();
	UFUNCTION() void UseSoundBackButton();
	UFUNCTION() void UseControlButton();
	UFUNCTION() void UseControlBackButton();
	//********************************************
	UFUNCTION() void UseExitButton();
	//********************************************
	UFUNCTION() void UseSettingsBackButton();

	UPROPERTY() AMainMenuController* MainMenuController;
private:

	UPROPERTY() UMasterSave* MasterSave;
};
//-----------------------------------------------------------------------------------------------------------