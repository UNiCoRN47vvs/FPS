#pragma once

#include "Widgets/MainMenu/MasterMenuWidget.h"
#include "CreateNewGameWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USignboardWidget;
class UEditableTextBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UCreateNewGameWidget : public UMasterMenuWidget
{
	GENERATED_BODY()
public:
	const FString& GetGameName();
	UPROPERTY(BlueprintReadOnly, Category = "Create New Game Widget", meta = (BindWidget)) USignboardWidget* EnterSignboardWidget;
	UPROPERTY(BlueprintReadOnly, Category = "Create New Game Widget", meta = (BindWidget)) USignboardWidget* BackSignboardWidget;
	UPROPERTY(BlueprintReadOnly, Category = "Create New Game Widget", meta = (BindWidget)) UEditableTextBox* EditableTB;
	UPROPERTY(BlueprintReadOnly, Category = "Signboard Widget", meta = (BindWidgetAnim), Transient) UWidgetAnimation* ErrorAnimation;
protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void TextChanged(const FText& Text);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create New Game Widget") int32 NameSize;
	FString GameName;
};
//-----------------------------------------------------------------------------------------------------------