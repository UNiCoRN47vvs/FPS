#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirstQuestWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMainHUDWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFirstQuestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitFirstQuest(UMainHUDWidget* mainHUD);
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	UPROPERTY() UMainHUDWidget* MainHUD;
};
//-----------------------------------------------------------------------------------------------------------