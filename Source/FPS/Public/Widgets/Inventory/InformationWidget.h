#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemGrade.h"
#include "Enums/StateName.h"
#include "Enums/FiringMode.h"
#include "InformationWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UInformationTextWidget;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInformationWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInformationWidget* InitParams(FItemInvStruct itemData);
	UInformationWidget* InitParams(TMap<EStateName, float>& stateMap);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void ClearParams();
	
	//***********************************************************************************************************
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UVerticalBox* VB1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UVerticalBox* VB2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UVerticalBox* VB3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UVerticalBox* VB4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_W") TSubclassOf<UInformationTextWidget> InformTextWidgetClass;

private:
};
//-----------------------------------------------------------------------------------------------------------
