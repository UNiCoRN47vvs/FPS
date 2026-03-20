#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DebuffWidgetComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStateMasterComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class FPS_API UDebuffWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	void InitWidgetComponent(UStateMasterComponent* stateComponent);
};
//-----------------------------------------------------------------------------------------------------------