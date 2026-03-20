#include "SkillActors/SkillActor.h"
#include "NiagaraComponent.h"
//-----------------------------------------------------------------------------------------------------------
ASkillActor::ASkillActor()
{
	PrimaryActorTick.bCanEverTick = true;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));

	InitialLifeSpan = 20.0f;
}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::DestroyAfterNiagara(UNiagaraComponent* PSystem)
{
	Destroy();
}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA)
{

}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner)
{
}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::InitParam(float damage, UEnemyMasterDA* enemyMasterDA, AEnemyMaster* enemy, USkillAttackDA* skillDA)
{
}
//-----------------------------------------------------------------------------------------------------------
void ASkillActor::ActivateSkill()
{

}
