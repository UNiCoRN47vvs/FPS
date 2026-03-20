#include "ActorComponents/Skill/SkillMasterComponent.h"
//-----------------------------------------------------------------------------------------------------------
USkillMasterComponent::USkillMasterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void USkillMasterComponent::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
