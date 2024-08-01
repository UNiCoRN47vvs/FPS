#include "ActorComponents/State/StateMasterComponent.h"
//-----------------------------------------------------------------------------------------------------------
UStateMasterComponent::UStateMasterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------