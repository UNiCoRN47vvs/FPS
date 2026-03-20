#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "PopUpMasterWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPopUpMasterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void InitPopUp(const FText& name, const int32 currentGoal, TSoftObjectPtr<UTexture2D> image);
	UPROPERTY(BlueprintReadOnly, Category = "PopUp", meta = (BindWidget)) UTextBlock* NameTB;
	UPROPERTY(BlueprintReadOnly, Category = "PopUp", meta = (BindWidget)) UTextBlock* CurrentGoalTB;
	UPROPERTY(BlueprintReadOnly, Category = "PopUp", meta = (BindWidget)) UImage* Image;
	UPROPERTY(BlueprintReadOnly, Category = "PopUp", meta = (BindWidgetAnim), Transient) UWidgetAnimation* PopUpAnimation;
};
//-----------------------------------------------------------------------------------------------------------