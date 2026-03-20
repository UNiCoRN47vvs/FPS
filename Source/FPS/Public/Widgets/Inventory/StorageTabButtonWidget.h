#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageTabButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStorageComponent;
class UChestWidget;
class UButton;
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStorageTabButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitStorageTabButtonWidget(int32 Index, UStorageComponent* Storage, UChestWidget* Widget);
	void PlayActiveTabAnimation();
protected:
	UFUNCTION() void SetNewActiveCurrentTab();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage Tab Button Widget", meta = (BindWidget)) UButton* TabButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage Tab Button Widget", meta = (BindWidget)) UTextBlock* TabNumberText;
	UPROPERTY(BlueprintReadOnly, Category = "Storage Tab Button Widget", meta = (BindWidgetAnim), Transient) UWidgetAnimation* ActiveTabAnimation;

	UPROPERTY() int32 IndexTab;
	UPROPERTY() UStorageComponent* StorageComponent;
	UPROPERTY() UChestWidget* StorageWidget;

};
//-----------------------------------------------------------------------------------------------------------