#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "WaveEnemyCountWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UBorder;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UWaveEnemyCountWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateTimeCount(int32 Count);
	void UpdateWaveCount(int32 Count);
	void UpdateEnemyCount(int32 Count);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Wave Enemy Count Widget", meta = (BindWidget)) UBorder* CountBorder;
	UPROPERTY(BlueprintReadOnly, Category = "Wave Enemy Count Widget", meta = (BindWidget)) UTextBlock* EnemyCount;
	UPROPERTY(BlueprintReadOnly, Category = "Wave Enemy Count Widget", meta = (BindWidget)) UTextBlock* WaveCount;
	UPROPERTY(BlueprintReadOnly, Category = "Wave Enemy Count Widget", meta = (BindWidget)) UTextBlock* TimeCount;
};
//-----------------------------------------------------------------------------------------------------------