#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FastSelectorBlockWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UHorizontalBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFastSelectorBlockWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "F_S_B_W", meta = (BindWidget)) UHorizontalBox* ItemsHB;
	
};
//-----------------------------------------------------------------------------------------------------------