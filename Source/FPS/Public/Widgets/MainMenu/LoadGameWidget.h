#pragma once

#include "Widgets/MainMenu/MasterMenuWidget.h"
#include "LoadGameWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UDeleteSaveGameWidget;
class UScrollBox;
class USignboardWidget;
class UMasterSave;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ULoadGameWidget : public UMasterMenuWidget
{
	GENERATED_BODY()
public:
	void InitLoadGameWidget(UMasterSave* MasterSave);
	void ClearLoadGameWidget();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Load Game Widget") TSubclassOf<UDeleteSaveGameWidget> WBPDeleteSaveGameWidget;
	UPROPERTY(BlueprintReadOnly, Category = "Load Game Widget", meta = (BindWidget)) UScrollBox* ScrollBox;
	UPROPERTY(BlueprintReadOnly, Category = "Load Game Widget", meta = (BindWidget)) USignboardWidget* BackSignboardWidget;
};
//-----------------------------------------------------------------------------------------------------------