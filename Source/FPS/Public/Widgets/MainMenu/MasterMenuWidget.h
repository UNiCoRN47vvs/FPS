#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "MasterMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMasterMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitSignboardWidget(bool bIsShow);
	

protected:
};
//-----------------------------------------------------------------------------------------------------------