#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Enums/SortType.h"
#include "SortButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UStorageComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USortButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitSortButton(UStorageComponent* storageComponent);

	UPROPERTY(BlueprintReadOnly, Category = "S_B_W", meta = (BindWidget)) UButton* ButtonSort;
	UPROPERTY(BlueprintReadOnly, Category = "S_B_W", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_B_W") ESortType SortType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_B_W") FText SortText;

protected:
	virtual void NativePreConstruct() override;
	UFUNCTION() void StorageSort();

	UPROPERTY() UStorageComponent* StorageComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_B_W") USoundWave* SortSound;
};
//-----------------------------------------------------------------------------------------------------------