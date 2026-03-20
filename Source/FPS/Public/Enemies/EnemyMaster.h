#pragma once

#include "Character/CharacterMaster.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Config/EnemyMasterDA.h"
#include "Interfaces/ItemInteract.h"
#include "Interfaces/DropInterface.h"
#include "Interfaces/InteractInfo.h"
#include "Enums/ItemGrade.h"
#include "Struct/EnemySkillsData.h"
#include "Struct/StatRange.h"
#include "Struct/DamageStruct.h"
#include "EnemyMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region Forward Declaration
class UNiagaraComponent;
class UNiagaraSystem;
class UHealthStaminaComponent;
class UEnemyStateComponent;
class UAIBrainComponent;
class UFPSGameInstance;
class UDebuffWidgetComponent;
class ANavigationData;
class UNavigationSystemV1;
class AEnemyAIController;
class UDropComponent;
class UEnemySC;
struct FInteractStruct;
struct FPortalStat;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
struct FPhysicsBody
{
	float PhysicsBlendWeight = 0.0;
	FName BoneName = {};
};
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FEnemySkillPoints
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") EEnemySkillType SkillType = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") float SkillPoints = 0.0;
};
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FEnemiesData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TSoftClassPtr<AEnemyMaster> Enemy = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TMap<EItemGrade, TSoftObjectPtr<UCharacterMasterDA>> EnemyData = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") float Chance = 0.0;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AEnemyMaster : public ACharacterMaster, public IItemInteract, public IDropInterface, public IInteractInfo
{
	GENERATED_BODY()

public:
	AEnemyMaster();
	//**************************
	//Interfaces
	virtual void ApplyDeath();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual void ApplyDrop(FItemInvStruct& Item, UNiagaraSystem* Niagara, FLinearColor Color) override;
	virtual FInteractStruct GetInteractInfo() override;
	//**************************
	virtual USkeletalMeshComponent* GetCharacterMesh() override;
	virtual void DealDamage(FDamageStruct& damageStruct, FHitResult hitResult = {}) override;
	virtual void DeleteEnemyComponents() override;
	virtual void HitReaction() override;
	virtual void PickUpEnemyLoot(UInventoryComponent* inventoryComponent) override;
	//**************************
	//Getters
	TWeakObjectPtr<UDebuffWidgetComponent> GetDebuffWidgetComponent();
	TWeakObjectPtr<UAIBrainComponent> GetAIBrainComponent();
	TWeakObjectPtr<UEnemyStateComponent> GetEnemyStateComponent();
	UDropComponent* GetDropComponent();
	UEnemySC* GetEnemySC();
	//**************************
	UFUNCTION(BlueprintCallable) void TESTING_Activate_Enemy(APawn* Pawn, UEnemyMasterDA* EnemyDataAsset, int32 portalLevel, EItemGrade portalGrade);
	void SetDataAsset(UCharacterMasterDA* DataAsset);
	void Reactivate();
	void ReactivateAndTeleport(bool bIsSelfCenter = false);
	void DestroyDropComponent();

	UFUNCTION() void AttackAfterMove();
	void InitEnemy(const FPortalStat& PortalStat, APawn* Pawn);
	void EnemyClearing();
	bool IsDefenseSkillActive();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Master") UNiagaraComponent* NiagaraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Master") UArrowComponent* EnemyArrowComponent;
	UPROPERTY() APawn* PawnTarget;

	uint8 bIsDead : 1;
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TArray<FEnemySkillPoints> EnemySkillPoints;
private:
	void EnemyUpdate();
	void InitEnemyDA();
	ACharacterMaster* TryGetPlayerCharacter(float radius, const FVector& location, UWorld* world = nullptr);
	void CheckAndDisablePhysics();
	void ApplySkillMontageEffect();

	void ApplyIllusionDeathEffect();
	
	uint8 bCanInteract : 1;
	float EnemyUpdateRate;
	TArray<FPhysicsBody> PhysicsBodiesArray;
	UPROPERTY() TWeakObjectPtr<UDebuffWidgetComponent> DebuffWidgetComponent;
	UPROPERTY() TWeakObjectPtr<UAIBrainComponent> AIBrainComponent;
	UPROPERTY() TWeakObjectPtr<UEnemyStateComponent> EnemyStateComponent;
	UPROPERTY() UEnemySC* EnemySC;
	UPROPERTY() UDropComponent* DropComponent;
	UPROPERTY() AEnemyAIController* AIController;
	UPROPERTY() UEnemyMasterDA* EnemyDA;
	UPROPERTY() ANavigationData* UseNavData;
	UPROPERTY() UNavigationSystemV1* NavSys;
	UPROPERTY() FTimerHandle EnemyHandle;
	UPROPERTY() FTimerHandle DeathTimerHandle;
	UPROPERTY() FTimerHandle DeleteComponentsHandle;
};
//-----------------------------------------------------------------------------------------------------------