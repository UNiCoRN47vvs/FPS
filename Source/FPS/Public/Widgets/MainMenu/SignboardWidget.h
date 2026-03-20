#pragma once

#include "Widgets/MainMenu/MasterMenuWidget.h"
#include "SignboardWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UButton;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USignboardWidget : public UMasterMenuWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Signboard Widget", meta = (BindWidget)) UButton* ButtonSignboard;
	UPROPERTY(BlueprintReadOnly, Category = "Signboard Widget", meta = (BindWidget)) UTextBlock* TextTB;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Signboard Widget") FText SignboardText;
protected:

};
//-----------------------------------------------------------------------------------------------------------