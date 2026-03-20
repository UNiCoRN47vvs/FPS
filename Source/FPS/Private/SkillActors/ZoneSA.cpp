#include "SkillActors/ZoneSA.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraSystemInstance.h"
#include "Enemies/EnemyMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Config/SkillAttackDA.h"
#include "Config/EnemyMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
AZoneSA::AZoneSA()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("Box Component")));

	RootComponent = BoxComponent;
	NiagaraComponent->SetupAttachment(BoxComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AZoneSA::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AZoneSA::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AZoneSA::EndOverlap);
}
//-----------------------------------------------------------------------------------------------------------
void AZoneSA::ActivateSkill()
{
	CHECK_PTR(SKillAttackDA)

	if (SKillAttackDA->SkillEffect.IsValidIndex(0))
		PTR(NiagaraComponent)->SetAsset(SKillAttackDA->SkillEffect[0]);

	NiagaraComponent->SetFloatParameter(FName(L"LifeTime"), ZoneLifeTime);
	NiagaraComponent->ResetSystem();
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AZoneSA::DestroyAfterNiagara);

	GetWorld()->GetTimerManager().SetTimer(ZoneTimer, this, &AZoneSA::ApplyZoneDamage, 0.33f, true);

	DamageStruct.Element1 = SKillAttackDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyCharacter->GetStateComponent()->FindElementChanseFromElement(SKillAttackDA->SkillElement1);
}
//-----------------------------------------------------------------------------------------------------------
void AZoneSA::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
		PlayerCharacter = Cast<ACharacterMaster>(OtherActor);
}
//-----------------------------------------------------------------------------------------------------------
void AZoneSA::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
		PlayerCharacter = nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void AZoneSA::ApplyZoneDamage()
{
	if (!PlayerCharacter)
		return;

	DamageStruct.Damage = SKillAttackDA->SkillAttackDamage.GetValueFromRange() + EnemyDA->EnemyAttackDamage.GetValueFromRange();

	PlayerCharacter->DealDamage(DamageStruct);
}
//-----------------------------------------------------------------------------------------------------------