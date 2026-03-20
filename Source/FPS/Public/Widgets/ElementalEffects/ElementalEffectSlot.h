#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElementalEffectSlot.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UImage;
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UElementalEffectSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateSlot(int32 StackCount, UTexture2D* Icon = nullptr);
	UPROPERTY(BlueprintReadOnly, Category = "E_E_S", meta = (BindWidget)) UImage* ImageIcon;
	UPROPERTY(BlueprintReadOnly, Category = "E_E_S", meta = (BindWidget)) UTextBlock* StackCountTB;
};
//-----------------------------------------------------------------------------------------------------------