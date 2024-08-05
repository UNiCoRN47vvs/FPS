#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InfoInteractWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInfoInteractWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info Interact Widget", meta = (BindWidget))
	UTextBlock* TextBlock;
};
//-----------------------------------------------------------------------------------------------------------