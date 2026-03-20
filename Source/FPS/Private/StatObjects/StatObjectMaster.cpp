#include "StatObjects/StatObjectMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UStatObjectMaster::PostInitProperties()
{
	Super::PostInitProperties();
}
//-----------------------------------------------------------------------------------------------------------
void UStatObjectMaster::DestroyStatObject()
{
	if (StateComponent)
	{
		StateComponent->OnDealDamage.RemoveAll(this);
		StateComponent->OnTakeDamage.RemoveAll(this);
	}
	RemoveFromRoot();
}
void UStatObjectMaster::InitParams(UStateMasterComponent* stateComponent, float effectChanse)
{
	if (!stateComponent)
	{
		ALARM_LOG
		DestroyStatObject();
	}

	StateComponent = stateComponent;
	EffectChanse = effectChanse;
}
//-----------------------------------------------------------------------------------------------------------
void UStatObjectMaster::ApplyStatEffect(FDamageStruct& damageStruct)
{
	DamageStruct = damageStruct;
}
//-----------------------------------------------------------------------------------------------------------
