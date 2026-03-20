#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeleteSaveGameWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class USignboardWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UDeleteSaveGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Delete Save Game Widget", meta = (BindWidget)) UButton* DeleteButton;
	UPROPERTY(BlueprintReadOnly, Category = "Delete Save Game Widget", meta = (BindWidget)) USignboardWidget* SignboardWidget;
protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void LoadGame();
	UFUNCTION() void DeleteSave();
};
//-----------------------------------------------------------------------------------------------------------