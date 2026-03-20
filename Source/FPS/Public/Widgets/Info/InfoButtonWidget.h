#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "InfoButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInfoButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_B_W") FName InfoNameWidget;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void UseInfoButton();

	UPROPERTY(BlueprintReadOnly, Category = "I_B_W", meta = (BindWidget)) UButton* InfoButton;
	UPROPERTY(BlueprintReadOnly, Category = "I_B_W", meta = (BindWidgetAnim), Transient) UWidgetAnimation* FirstAnimation;
};
//-----------------------------------------------------------------------------------------------------------