#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FramePerSecondWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (ChildCanTick))
class FPS_API UFramePerSecondWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Per Second") float CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame Per Second") float MaxTime;

};
//-----------------------------------------------------------------------------------------------------------