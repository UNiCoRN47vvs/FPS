#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "KeyTextWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UKeyTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K_T_W", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K_T_W") FName MappingName;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void UpdateInfo();
};
//-----------------------------------------------------------------------------------------------------------