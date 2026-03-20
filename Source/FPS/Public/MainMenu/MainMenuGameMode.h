#pragma once

#include "FPS/FPS.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void SwichSignboards();
protected:
};
//-----------------------------------------------------------------------------------------------------------