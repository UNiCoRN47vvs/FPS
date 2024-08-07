#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InfoInteractWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCantPickUpItem);
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInfoInteractWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info Interact Widget", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(BlueprintAssignable, Category = "Info Interact Widget") FCantPickUpItem CantPickUpItem;
};
//-----------------------------------------------------------------------------------------------------------