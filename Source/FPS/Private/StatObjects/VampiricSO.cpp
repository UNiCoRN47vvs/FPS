#include "StatObjects/VampiricSO.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
//-----------------------------------------------------------------------------------------------------------
void UVampiricSO::ApplyStatEffect(FDamageStruct& damageStruct)
{
	Super::ApplyStatEffect(damageStruct);

	if (FMath::RandRange(0.0f, 100.0f) > EffectChanse)
		return;

	CHECK_PTR(StateComponent)
	StateComponent->ApplyHeal(VampiricDamagePercent / 100.0f * damageStruct.Damage);
}
//-----------------------------------------------------------------------------------------------------------
