#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "InformationStandWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UScrollBox;
class UStandButtonWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInformationStandWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitInformationStand();
	void StandButtonClick(const FName& name);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UScrollBox* ListInfoSB;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UScrollBox* InfoSB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_W") TMap<FName, TSubclassOf<UUserWidget>> InfoMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_W") TSubclassOf<UStandButtonWidget> ButtonWidgetClass;
private:
	UPROPERTY() UUserWidget* InfoWidget;
};
//-----------------------------------------------------------------------------------------------------------