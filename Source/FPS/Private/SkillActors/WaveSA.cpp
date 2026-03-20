#include "SkillActors/WaveSA.h"
#include "NiagaraComponent.h"
#include "Character/CharacterMaster.h"
#include "Struct/DamageStruct.h"
#include "Config/SkillAttackDA.h"
//-----------------------------------------------------------------------------------------------------------
AWaveSA::AWaveSA()
{
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Default Scene Component")));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh")));

	if (DefaultSceneComponent)
	{
		RootComponent = DefaultSceneComponent;
		if (StaticMesh)
			StaticMesh->SetupAttachment(DefaultSceneComponent);
	}

	NiagaraComponent->SetupAttachment(StaticMesh);
}
//-----------------------------------------------------------------------------------------------------------
void AWaveSA::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AWaveSA::StaticMeshComponentOverlapBegin);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AWaveSA::DestroyAfterNiagara);
}
//-----------------------------------------------------------------------------------------------------------
void AWaveSA::InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA)
{
	CHECK_PTR(skillAttackDA)

	DamageStruct = damageStruct;
	NiagaraComponent->SetAsset(skillAttackDA->SkillProjectileEffect);
	NiagaraComponent->ActivateSystem();

	if (skillAttackDA->SkillEffectColor.IsValidIndex(0))
		NiagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), skillAttackDA->SkillEffectColor[0]);

	NiagaraComponent->ResetSystem();
}
//-----------------------------------------------------------------------------------------------------------
void AWaveSA::StaticMeshComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterMaster* character = Cast<ACharacterMaster>(OtherActor);
	CHECK_PTR(character)

	character->DealDamage(DamageStruct);

	StaticMesh->Deactivate();
	StaticMesh->DestroyComponent();
}
//-----------------------------------------------------------------------------------------------------------
