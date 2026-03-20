#include "SkillActors/ProjectileSA.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Character/CharacterMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Config/SkillAttackDA.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
AProjectileSA::AProjectileSA()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Collision Sphere Component")));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Projectile Component")));

	RootComponent = CollisionSphereComponent;
	NiagaraComponent->SetupAttachment(CollisionSphereComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA)
{
	CHECK_PTR(skillAttackDA)

	DamageStruct = damageStruct;
	SkillAttackDA = skillAttackDA;

	NiagaraComponent->SetAsset(SkillAttackDA->SkillProjectileEffect);
	NiagaraComponent->ActivateSystem();

	if (SkillAttackDA->SkillEffectColor.IsValidIndex(0))
		NiagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), SkillAttackDA->SkillEffectColor[0]);

	NiagaraComponent->ResetSystem();
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner)
{
	ScrollDA = scrollDA;
	ElementChance = elementChance;

	CHECK_PTR(owner)

	DamageStruct.DamageOwner = owner;
	DamageStruct.DamageOwnerComponent = owner->FindComponentByClass<UStateMasterComponent>();

	UGameplayStatics::PlaySoundAtLocation(this, ScrollDA->StartSound, GetActorLocation());
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileSA::SphereBeginOverlap);
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ACharacterMaster* character = Cast<ACharacterMaster>(otherActor);
	if (character)
		character->DealDamage(DamageStruct);

	Destroy();
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::ApplyNiagaraParameters(UNiagaraSystem* niagaraSystem, const FVector& niagaraSize)
{
	NiagaraComponent->SetAsset(niagaraSystem);
	NiagaraComponent->ResetSystem();
	NiagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), ScrollDA->SkillColor);
	NiagaraComponent->SetWorldScale3D(FVector(niagaraSize));
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSA::MakeProjectileHoming(USceneComponent* sceneComponent)
{
	ProjectileComponent->bIsHomingProjectile = true;
	ProjectileComponent->HomingTargetComponent = sceneComponent;
}
//-----------------------------------------------------------------------------------------------------------