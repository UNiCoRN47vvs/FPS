#include "FPSGameMode.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
//-----------------------------------------------------------------------------------------------------------
AFPSGameMode::AFPSGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
//-----------------------------------------------------------------------------------------------------------