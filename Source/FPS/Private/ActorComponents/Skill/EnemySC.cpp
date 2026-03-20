#include "ActorComponents/Skill/EnemySC.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Engine/SkeletalMeshSocket.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemies/EnemyMaster.h"
#include "Components/CapsuleComponent.h"
#include "SubSystem/WorldRuler.h"
#include "ActorComponents/State/EnemyStateComponent.h"
#include "ActorComponents/AI/AIBrainComponent.h"
#include "ActorComponents/State/PlayerStateComponent.h"
#include "ActorComponents/Drop/DropComponent.h"
#include "SkillActors/ProjectileSA.h"
#include "SkillActors/ZoneSA.h"
#include "Config/SkillMasterDA.h"
#include "Config/EnemyMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::InitEnemySC(AEnemyMaster* enemyOwner, UEnemyMasterDA* enemyDA, APawn* pawnTarget)
{
	EnemyOwner = enemyOwner;
	EnemyDA = enemyDA;
	PawnTarget = pawnTarget;
	CheckData();

	DamageStruct.DamageOwner = EnemyOwner;
	DamageStruct.DamageOwnerComponent = GetEnemyStateComponent();
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::SetEnemyDamage(const FStatRange& enemyDamage)
{
	EnemyDamage = enemyDamage;
}
//-----------------------------------------------------------------------------------------------------------
bool UEnemySC::CheckData()
{
	if (!EnemyOwner || !EnemyDA || !PawnTarget)
	{
		ALARM_LOG

		Deactivate();
		DestroyComponent();
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::AttackEnded()
{
	CHECK_PTR(GetAIBrainComponent())
	AIBrainComponent->AttackEnded();
}
//-----------------------------------------------------------------------------------------------------------
UAIBrainComponent* UEnemySC::GetAIBrainComponent()
{
	if (!AIBrainComponent)
		AIBrainComponent = GetOwner()->FindComponentByClass<UAIBrainComponent>();
	return AIBrainComponent;
}
//-----------------------------------------------------------------------------------------------------------
UStateMasterComponent* UEnemySC::GetEnemyStateComponent()
{
	if (!EnemyStateComponent)
		EnemyStateComponent = GetOwner()->FindComponentByClass<UEnemyStateComponent>();
	return EnemyStateComponent;
}
//-----------------------------------------------------------------------------------------------------------
ACharacterMaster* UEnemySC::TryGetPlayerCharacter(float radius, const FVector& location, UWorld* world)
{
	bool bIsHit = false;
	UObject* worldContextObject = world;
	TArray<AActor*> ignoreActors = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<FHitResult> outHitResult = {};

	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);
	if (!world)
		worldContextObject = this;

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(worldContextObject, location, location, radius, objectType, false, ignoreActors,
		EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0);

	for (auto& item : outHitResult)
	{
		if (item.GetActor()->ActorHasTag(FName(TEXT("Player"))))
			return Cast<ACharacterMaster>(item.GetActor());
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------------------------
#pragma region Skills
void UEnemySC::UseDefenseSkill()
{
	UNiagaraComponent* niagaraComponent = nullptr;
	USkillDefenseDA* skillDA = GetCurrentSkillDA<USkillDefenseDA>();
	CHECK_PTR(skillDA)
	CHECK_PTR(skillDA->SkillEffect[0])

	CHECK_PTR(GetEnemyStateComponent())

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], FVector{}, FRotator{}, FVector{ 1.0f }, false);
	CHECK_PTR(niagaraComponent)

	niagaraComponent->AttachToComponent(EnemyOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	niagaraComponent->SetAbsolute(false, true, false);
	niagaraComponent->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));

	EnemyStateComponent->UseDefenseSkill(niagaraComponent, skillDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillStrike()
{
	if (CheckData())
		return;

	CHECK_PTR(CurrentSkill.SkillData)

	if (!CurrentSkill.SkillData->SkillEffect.IsValidIndex(0))
		return;

	CHECK_PTR(CurrentSkill.SkillData->SkillEffect[0])


	float radius = EnemyDA->AttackDistance * 10;
	ACharacterMaster* playerCharacter = nullptr;
	UNiagaraComponent* niagaraComponent = nullptr;

	CHECK_PTR(GetAIBrainComponent())
		
	playerCharacter = TryGetPlayerCharacter(radius, EnemyOwner->GetActorLocation());

	CHECK_PTR(playerCharacter)

	StrikeLocation = playerCharacter->GetActorLocation();
	StrikeLocation.Z -= 90.0;

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CurrentSkill.SkillData->SkillEffect[0], StrikeLocation, FRotator{ 0.0 }, FVector{ 1.0 });
	CHECK_PTR(niagaraComponent)

	if (CurrentSkill.SkillData->SkillEffectColor.IsValidIndex(0))
		niagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), CurrentSkill.SkillData->SkillEffectColor[0]);

	AIBrainComponent->bSkillIsActive = true;
	niagaraComponent->OnSystemFinished.RemoveAll(this);
	niagaraComponent->OnSystemFinished.AddDynamic(this, &UEnemySC::UseSkillStrikeStep2);
}
//***********************************************************************************************************
void UEnemySC::UseSkillStrikeStep2(UNiagaraComponent* FinishedComponent)
{
	if (CheckData())
		return;

	CHECK_PTR(FinishedComponent)
	CHECK_PTR(CurrentSkill.SkillData)

	bool bIsHit = false;
	float radius = false;
	ACharacterMaster* character = nullptr;
	UNiagaraSystem* skillEffect = nullptr;
	UNiagaraComponent* niagaraComponent = nullptr;
	USkillAttackDA* skillDA = nullptr;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<AActor*> ignoreActors = {};
	TArray<FHitResult> outHitResult = {};

	if (!CurrentSkill.SkillData->SkillEffect.IsValidIndex(1))
		return;

	skillEffect = CurrentSkill.SkillData->SkillEffect[1];
	if (skillEffect)
		niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillEffect, StrikeLocation, FRotator{}, FVector{ 1.0 });

	if (niagaraComponent && CurrentSkill.SkillData->SkillEffectColor.IsValidIndex(1))
		niagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), CurrentSkill.SkillData->SkillEffectColor[1]);

	radius = EnemyDA->AttackSphereRadius;
	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, StrikeLocation, StrikeLocation, radius, objectType, false,
		ignoreActors, EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 1.0);

	CHECK_PTR(GetAIBrainComponent())
	CHECK_PTR(GetEnemyStateComponent())

	AIBrainComponent->bSkillIsActive = false;

	if (!bIsHit)
		return;
	for (const FHitResult& item : outHitResult)
	{
		if (item.GetActor()->ActorHasTag(FName(TEXT("Player"))))
		{
			character = Cast<ACharacterMaster>(item.GetActor());
			skillDA = GetCurrentSkillDA<USkillAttackDA>();
			CHECK_PTR(character)
				CHECK_PTR(skillDA)

			DamageStruct.Damage = skillDA->SkillAttackDamage.GetValueFromRange() + EnemyDamage.GetValueFromRange();
			DamageStruct.Element1 = skillDA->SkillElement1;
			DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

			character->DealDamage(DamageStruct);
			break;
		}
	}
}
//***********************************************************************************************************
void UEnemySC::UseSkillMultiStrike()
{
	if (CheckData())
		return;

	int32 counter = 25;
	float spawnTime = 0.0f;
	UWorld* world = GetWorld();
	USkillSupportDA* skillDA = Cast<USkillSupportDA>(CurrentSkill.SkillData);

	CHECK_PTR(skillDA)
	CHECK_PTR(world)

	if (!skillDA->SkillActor.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(skillDA->SkillActor.ToSoftObjectPath(), [this]
			{
				AsyncTask(ENamedThreads::GameThread, [this]
					{
						UseSkillMultiStrike();
					});
			});
		return;
	}
	for (int32 i = counter; i > 0; --i)
	{
		FTimerHandle timerHandle = {};

		spawnTime = FMath::RandRange(0.25f, 4.75f);
		world->GetTimerManager().SetTimer(timerHandle, [this, skillDA]
			{
				if (CheckData())
					return;

				ASkillActor* skillActor = nullptr;
				skillActor = GetWorld()->SpawnActor<ASkillActor>(skillDA->SkillActor.Get(), EnemyOwner->GetActorLocation(), EnemyOwner->GetActorRotation());

				CHECK_PTR(skillActor)

				skillActor->InitParam(EnemyDamage.GetValueFromRange(), EnemyDA, EnemyOwner);
			}, spawnTime, false);
	}
}
//***********************************************************************************************************
void UEnemySC::UseSkillTripleProjectile()
{
	if (CheckData())
		return;

	USkillAttackDA* skillDA = GetCurrentSkillDA<USkillAttackDA>();
	CHECK_PTR(skillDA)
	CHECK_PTR(skillDA->AttackProjectyle)

	float damage = 0.0f;
	UWorld* world = this->GetWorld();
	UClass* projectileMaster = nullptr;
	TWeakObjectPtr<AProjectileSA> projectile = {};
	FActorSpawnParameters spawnParams = {};
	// Получаем позицию сокета для спавна снаряда

	FVector spawnLocation = EnemyOwner->GetMesh()->GetSocketLocation(skillDA->SkillSocketBoneName);
	FRotator rotation = EnemyOwner->GetActorRotation();

	CHECK_PTR(world)
	CHECK_PTR(GetEnemyStateComponent())
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	damage = EnemyDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange();
	projectileMaster = skillDA->AttackProjectyle;
	CHECK_PTR(projectileMaster)

	DamageStruct.Damage = damage;
	DamageStruct.Element1 = skillDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	projectile = world->SpawnActor<AProjectileSA>(projectileMaster, spawnLocation, rotation, spawnParams);
	if (!projectile.IsValid())
	{
		//Если не заспавнился
		DamageStruct.Damage = damage * 3;
		DealDamageIfNotSpawn(DamageStruct);
		return;
	}
	projectile->InitParam(DamageStruct, skillDA);
	projectile = world->SpawnActor<AProjectileSA>(projectileMaster, spawnLocation, rotation + FRotator(0.0, 15.0, 0.0), spawnParams);
	if (!projectile.IsValid())
	{
		//Если не заспавнился
		DamageStruct.Damage = damage * 2;
		DealDamageIfNotSpawn(DamageStruct);
		return;
	}
	projectile->InitParam(DamageStruct, skillDA);
	projectile = world->SpawnActor<AProjectileSA>(projectileMaster, spawnLocation, rotation - FRotator(0.0, 15.0, 0.0), spawnParams);
	if (!projectile.IsValid())
	{
		//Если не заспавнился
		DamageStruct.Damage = damage;
		DealDamageIfNotSpawn(DamageStruct);
		return;
	}
	projectile->InitParam(DamageStruct, skillDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillMelee()
{
	if (CheckData())
		return;

	ACharacterMaster* playerCharacter = nullptr;
	USkillAttackDA* skillDA = nullptr;
	float radius = 0.0f;
	FVector location = {};

	skillDA = GetCurrentSkillDA<USkillAttackDA>();
	CHECK_PTR(skillDA)

	radius = EnemyDA->AttackSphereRadius / 1.9f;

	location = EnemyOwner->GetCapsuleComponent()->GetForwardVector() * 170.0f + EnemyOwner->GetMesh()->GetSocketLocation(skillDA->SkillSocketBoneName);

	playerCharacter = TryGetPlayerCharacter(radius, location);

	CHECK_PTR(playerCharacter)
		CHECK_PTR(GetEnemyStateComponent())

		DamageStruct.Damage = EnemyDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange();
	DamageStruct.Element1 = skillDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	playerCharacter->DealDamage(DamageStruct);
}
//***********************************************************************************************************
void UEnemySC::UseSkillHomingProjectile()
{
	SpawnSkillProjectile(true);
}
//***********************************************************************************************************
void UEnemySC::UseSkillIcecleProjectile()
{
	SpawnSkillProjectile(false);
}
//***********************************************************************************************************
void UEnemySC::UseSkillProjectileSpawner()
{
	SpawnSkillProjectile(false);
}
//***********************************************************************************************************
void UEnemySC::UseSkillIceCage()
{
	if (CheckData())
		return;

	USkillDefenseDA* skillDA = GetCurrentSkillDA<USkillDefenseDA>();

	UPlayerStateComponent::OnApplyIceCage.ExecuteIfBound(PawnTarget, skillDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillBubble()
{
	if (CheckData())
		return;

	UNiagaraComponent* niagaraComponent = nullptr;
	USkillDefenseDA* skillDA = GetCurrentSkillDA<USkillDefenseDA>();
	CHECK_PTR(skillDA)
	CHECK_PTR(skillDA->SkillEffect[0])

	CHECK_PTR(GetEnemyStateComponent())

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], FVector{}, FRotator{}, FVector{ 1.0f }, false);

	CHECK_PTR(niagaraComponent)

	niagaraComponent->AttachToComponent(EnemyOwner->EnemyArrowComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	niagaraComponent->SetAbsolute(false, true, false);
	//LocalNiagaraComponent->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));

	EnemyStateComponent->UseDefenseSkill(niagaraComponent, skillDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillAura()
{
	if (CheckData())
		return;

	UNiagaraComponent* niagaraComponent = nullptr;
	USkillDefenseDA* skillDA = GetCurrentSkillDA<USkillDefenseDA>();
	CHECK_PTR(skillDA)
	CHECK_PTR(skillDA->SkillEffect[0])
	CHECK_PTR(GetEnemyStateComponent())

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], FVector{}, FRotator{}, FVector{ 1.0 }, false);
	CHECK_PTR(niagaraComponent)

	niagaraComponent->AttachToComponent(EnemyOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	niagaraComponent->SetAbsolute(false, true, false);
	niagaraComponent->SetRelativeScale3D(FVector(0.85, 0.85, 0.85));

	EnemyStateComponent->UseDefenseSkill(niagaraComponent, skillDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillLifeSteal()
{
	if (CheckData())
		return;

	float radius = 0.0f;
	ACharacterMaster* playerCharacter = nullptr;
	UNiagaraComponent* niagara = nullptr;
	USkillAttackDA* skillDA = GetCurrentSkillDA<USkillAttackDA>();
	FTimerHandle lifeStealHandle = {};

	CHECK_PTR(skillDA)
	CHECK_PTR(GetEnemyStateComponent())

		radius = EnemyDA->AttackDistance * 50;
	playerCharacter = TryGetPlayerCharacter(radius, EnemyOwner->GetActorLocation());

	CHECK_PTR(playerCharacter)

		DamageStruct.Damage = EnemyDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange();
	DamageStruct.Element1 = skillDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	playerCharacter->DealDamage(DamageStruct);

	EnemyStateComponent->ApplyHeal(DamageStruct.Damage * 10);

	CHECK_PTR(CurrentSkill.SkillData)
		CHECK_PTR(CurrentSkill.SkillData->SkillEffect[0])

		niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(CurrentSkill.SkillData->SkillEffect[0], EnemyOwner->GetMesh(), FName(TEXT("SkillLifeSteal_Socket")),
			FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTarget, true);

	GetWorld()->GetTimerManager().SetTimer(lifeStealHandle, [this, niagara, playerCharacter]()
		{
			SkillLifeStealNiagaraEffect(niagara, playerCharacter->GetActorLocation());
		}, 0.055, false);
}
void UEnemySC::SkillLifeStealNiagaraEffect(UNiagaraComponent* niagara, FVector location)
{
	if (!IsValid(niagara))
		return;

	FTimerHandle lifeStealHandle = {};

	niagara->SetVariableVec3(FName(TEXT("Target")), location);

	GetWorld()->GetTimerManager().SetTimer(lifeStealHandle, [this, niagara, location]()
		{
			SkillLifeStealNiagaraEffect(niagara, location);
		}, 0.055, false);
}
//***********************************************************************************************************
void UEnemySC::UseTeleportToPlayer()
{
	if (CheckData())
		return;

	bool bIsTouch = false;
	bool bLineTraceIsTouch = false;
	int32 infinityBlock = 100;
	float spawnRadius = 550.0f;
	float radius = EnemyDA->AttackDistance * 2;
	ACharacterMaster* playerCharacter = nullptr;
	UNavigationSystemV1* navSys = nullptr;
	ANavigationData* useNavData = nullptr;
	FVector randomPoint = {};
	FVector location = EnemyOwner->GetActorLocation();
	FVector playerLocation = {};
	FPathFindingQuery query = {};
	FNavLocation randomNavPoint(location);
	FHitResult hitResult = {};
	FHitResult lineTraceHitResult = {};
	TArray<AActor*> characters = {};
	TArray<AActor*> lineTraceIgnore = {};

	playerCharacter = TryGetPlayerCharacter(radius, location);

	CHECK_PTR(playerCharacter)

	playerLocation = playerCharacter->GetActorLocation();

	navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	CHECK_PTR(navSys)

	lineTraceIgnore.Add(playerCharacter);
	do
	{
		useNavData = navSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
		CHECK_PTR(useNavData)

			navSys->GetRandomReachablePointInRadius(playerLocation, spawnRadius, randomNavPoint, useNavData,
				UNavigationQueryFilter::GetQueryFilter(*useNavData, this, UNavigationQueryFilter::StaticClass()));

		randomPoint = randomNavPoint.Location + FVector(0.0, 0.0, 175.0);

		bIsTouch = UKismetSystemLibrary::SphereTraceSingle(this, randomPoint, randomPoint + FVector(0.0, 0.0, 120.0), 160.0,
			ETraceTypeQuery::TraceTypeQuery1, false, characters, EDrawDebugTrace::None, hitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0);

		bLineTraceIsTouch = UKismetSystemLibrary::LineTraceSingle(this, randomPoint, playerLocation, ETraceTypeQuery::TraceTypeQuery1, false,
			lineTraceIgnore, EDrawDebugTrace::None, lineTraceHitResult, true);

		if (bIsTouch || bLineTraceIsTouch)
		{
			--infinityBlock;
			continue;
		}

		query.StartLocation = randomPoint;
		query.EndLocation = playerLocation;
		query.NavData = useNavData;
		if (navSys->TestPathSync(query))
			break;

		--infinityBlock;
	} while (infinityBlock >= 0);

	if (infinityBlock <= 0)
		return;

	if (CurrentSkill.SkillData && CurrentSkill.SkillData->SkillEffect[0])
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CurrentSkill.SkillData->SkillEffect[0], location, FRotator(0.0, 0.0, 0.0), FVector(3.5, 3.5, 3.5));

	EnemyOwner->SetActorLocation(randomPoint);
	EnemyOwner->SetActorRotation((playerLocation - location).Rotation());
}
//***********************************************************************************************************
void UEnemySC::UseSkillLifeChainAttack()
{
	if (CheckData())
		return;

	bool bIsTouch = false;
	int32 index = 0;
	ACharacterMaster* playerCharacter = nullptr;
	AEnemyMaster* enemy = nullptr;
	USkillAttackDA* skillDA = nullptr;
	UNiagaraComponent* niagaraComponent = nullptr;
	float enemyHealth = 0.0f;
	float targetEnemyHealth = 0.0f;
	FVector ownerLocation = EnemyOwner->GetActorLocation();
	FVector targetLocation = {};
	FVector oldTargetLocation = {};
	TArray<AEnemyMaster*> targetEnemies = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignores = {};
	TArray<FHitResult> hitResult = {};

	skillDA = GetCurrentSkillDA<USkillAttackDA>();
	CHECK_PTR(skillDA)

	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);
	ignores.Add(EnemyOwner);

	bIsTouch = UKismetSystemLibrary::SphereTraceMultiForObjects(this, ownerLocation, ownerLocation, skillDA->AttackDistance * 3,
		objectTypes, false, ignores, EDrawDebugTrace::None, hitResult, true);

	if (!bIsTouch)
		return;

	// Поиск союзников для отхила
	for (const FHitResult& item : hitResult)
	{
		enemy = Cast<AEnemyMaster>(item.GetActor());
		if (!IsValid(enemy) || enemy && enemy->bIsDead || enemy->GetEnemyStateComponent()->GetStateMapElem(EStateName::Health) >= enemy->GetEnemyStateComponent()->GetStateMapElem(EStateName::HealthMax))
			continue;

		targetEnemies.Add(enemy);
	}
	DamageStruct.Damage = EnemyDA->EnemyAttackDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange();

	if (!targetEnemies.IsEmpty())
	{
		for (int32 i = 0; i < skillDA->SkillEffect.Num(); ++i)
		{
			if (!skillDA->SkillEffect[i])
				continue;

			for (int32 j = 0; j < targetEnemies.Num(); ++j)
			{
				enemyHealth = targetEnemies[j]->GetEnemyStateComponent()->GetStateMapElem(EStateName::HealthMax) - targetEnemies[j]->GetEnemyStateComponent()->GetStateMapElem(EStateName::Health);
				if (targetEnemyHealth < enemyHealth)
				{
					index = j;
					enemy = targetEnemies[j];
					targetEnemyHealth = enemyHealth;
				}
			}
			if (!enemy)
				continue;

			if (targetEnemies.IsValidIndex(index))
				targetEnemies.RemoveAt(index);

			if (i == 0)
				oldTargetLocation = EnemyOwner->GetMesh()->GetSocketLocation(skillDA->SkillSocketBoneName);

			targetLocation = enemy->GetActorLocation();

			niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[i], oldTargetLocation,
				FRotator(0.0f));

			if (!niagaraComponent && !skillDA->SkillEffectColor.IsValidIndex(0))
				continue;

			niagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), skillDA->SkillEffectColor[0]);
			niagaraComponent->SetVariableVec3(FName(TEXT("Target")), targetLocation);

			//Если есть союзник для отхила то хилим его
			enemy->GetStateComponent()->ApplyHeal(DamageStruct.Damage * 2);

			oldTargetLocation = enemy->GetActorLocation();
			targetEnemyHealth = 0.0;
		}
		return;
	}

	//Если нет союзника для отхила то наносим урон игроку
	playerCharacter = TryGetPlayerCharacter(skillDA->AttackDistance * 3, ownerLocation);
	CHECK_PTR(playerCharacter)

		if (!skillDA->SkillEffectColor.IsValidIndex(0) || !skillDA->SkillEffect.IsValidIndex(0) || !skillDA->SkillEffect[0])
			return;

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], EnemyOwner->GetMesh()->GetSocketLocation(skillDA->SkillSocketBoneName),
		FRotator(0.0f));

	CHECK_PTR(niagaraComponent)
	CHECK_PTR(GetEnemyStateComponent())

	niagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), skillDA->SkillEffectColor[0]);

	niagaraComponent->SetVariableVec3(FName(TEXT("Target")), playerCharacter->GetActorLocation());

	DamageStruct.Element1 = skillDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	playerCharacter->DealDamage(DamageStruct);
}
//***********************************************************************************************************
void UEnemySC::UseSkillSircleWave()
{
	if (CheckData())
		return;

	ASkillActor* projectile = nullptr;
	USkillAttackDA* attackDA = GetCurrentSkillDA<USkillAttackDA>();
	FActorSpawnParameters spawnParams = {};
	CHECK_PTR(attackDA)
	CHECK_PTR(GetEnemyStateComponent())

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	projectile = GetWorld()->SpawnActor<ASkillActor>(attackDA->AttackProjectyle, EnemyOwner->GetMesh()->GetBoneLocation(FName(TEXT("root"))), FRotator(), spawnParams);
	CHECK_PTR(projectile)

		DamageStruct.Damage = attackDA->SkillAttackDamage.GetValueFromRange();
	DamageStruct.Element1 = attackDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(attackDA->SkillElement1);

	projectile->InitParam(DamageStruct, attackDA);
}
//***********************************************************************************************************
void UEnemySC::UseSkillDilationUpBuff()
{
	if (CheckData())
		return;

	bool bIsTouch = false;
	int32 index = 0;
	AEnemyMaster* enemy = nullptr;
	USkillDefenseDA* skillDA = nullptr;
	FVector ownerLocation = EnemyOwner->GetActorLocation();
	TArray<AEnemyMaster*> targetEnemies = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignores = {};
	TArray<FHitResult> hitResult = {};

	skillDA = GetCurrentSkillDA<USkillDefenseDA>();
	CHECK_PTR(skillDA)

	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);

	bIsTouch = UKismetSystemLibrary::SphereTraceMultiForObjects(this, ownerLocation, ownerLocation, skillDA->AttackDistance * 3,
		objectTypes, false, ignores, EDrawDebugTrace::None, hitResult, false);

	if (!bIsTouch)
		return;

	// Поиск союзников для отхила
	for (const FHitResult& item : hitResult)
	{
		enemy = Cast<AEnemyMaster>(item.GetActor());
		if (!IsValid(enemy) || enemy && enemy->bIsDead)
			continue;

		targetEnemies.Add(enemy);
	}

	index = FMath::RandRange(0, targetEnemies.Num() - 1);

	if (!targetEnemies.IsValidIndex(index))
		return;

	enemy = targetEnemies[index];
	CHECK_PTR(enemy)

	enemy->GetStateComponent()->ApplyDilationUpBuff(skillDA->SkillPercent, skillDA->LifeTime);
}
//***********************************************************************************************************
void UEnemySC::UseSkillSandStorm()
{
	if (CheckData())
		return;

	ACharacterMaster* character = nullptr;
	UStateMasterComponent* stateComponent = nullptr;
	UNiagaraComponent* niagaraComponent = nullptr;
	USkillDefenseDA* defenseDA = nullptr;
	FVector location = EnemyOwner->GetActorLocation();
	
	CHECK_PTR(CurrentSkill.SkillData)

	character = TryGetPlayerCharacter(CurrentSkill.SkillData->AttackDistance * 2.0, location);

	CHECK_PTR(character)

	stateComponent = character->FindComponentByClass<UStateMasterComponent>();

	CHECK_PTR(stateComponent)

	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(CurrentSkill.SkillData->SkillEffect[0], character->GetMesh(), FName(TEXT("none")),
		FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTarget, true);

	CHECK_PTR(niagaraComponent)

	defenseDA = Cast<USkillDefenseDA>(CurrentSkill.SkillData);

	CHECK_PTR(defenseDA)

	niagaraComponent->SetVariableFloat(FName(TEXT("LifeTime")), defenseDA->LifeTime);

	stateComponent->ApplySandStorm(CurrentSkill.SkillData, EnemyDA->EnemyAttackDamage.GetValueFromRange());
}
//***********************************************************************************************************
void UEnemySC::UseSkillFrostveilMelee()
{
	UseSkillMelee();

	FrostveilPassive();
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::UseSkillFrostveilHand()
{
	if (CheckData())
		return;

	UWorld* world = nullptr;
	UEnemyMasterDA* enemyDA = EnemyDA;
	USkillAttackDA* skillDA = nullptr;
	FVector targetLocation = {};
	FVector ownerLocation = EnemyOwner->GetActorLocation();
	FVector lerpLocation = {};
	FTimerHandle timerHandle = {};
	FDamageStruct damageStruct = DamageStruct;

	world = GetWorld();

	CHECK_PTR(world)
	CHECK_PTR(PawnTarget)
	CHECK_PTR(GetEnemyStateComponent())

	targetLocation = PawnTarget->GetActorLocation();

	skillDA = GetCurrentSkillDA<USkillAttackDA>();
	CHECK_PTR(skillDA)

	lerpLocation = FMath::Lerp(ownerLocation, targetLocation, 0.5f);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], lerpLocation, EnemyOwner->GetActorRotation(), FVector{ 1.0f });

	damageStruct.Damage = (EnemyDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange()) / 5.0f;
	damageStruct.Element1 = skillDA->SkillElement1;
	damageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	lerpLocation = FMath::Lerp(ownerLocation, targetLocation, 0.76f);

	GetWorld()->GetTimerManager().SetTimer(timerHandle, [world, enemyDA, lerpLocation, damageStruct]()
		{
			bool bIsHit = false;
			ACharacterMaster* character = nullptr;
			TArray<AActor*> ignoreActors = {};
			TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
			TArray<FHitResult> outHitResult = {};
			FDamageStruct damage = damageStruct;

			objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

			bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(world, lerpLocation, lerpLocation, enemyDA->AttackSphereRadius * 1.2f, objectType, false, ignoreActors,
				EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0f);

			for (const FHitResult& item : outHitResult)
			{
				if (!item.GetActor() || !item.GetActor()->ActorHasTag(FName(TEXT("Player"))))
					continue;

				character = Cast<ACharacterMaster>(item.GetActor());
				CHECK_PTR(character)

					for (int32 i = 0; i < 5; ++i)
					{
						character->DealDamage(damage);
					}

				break;
			}

		}, 0.25f, false);

	FrostveilPassive();
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::UseSkillFrostveilAura()
{
	if (CheckData())
		return;

	UWorld* world = GetWorld();
	UNiagaraComponent* niagara = nullptr;
	USkillDefenseDA* skillDA = GetCurrentSkillDA<USkillDefenseDA>();
	float radius = 0.0f;
	float lifeTime = 0.0f;
	FDamageStruct damageStruct = DamageStruct;
	FTimerHandle timerHandle = {};

	CHECK_PTR(skillDA)
	CHECK_PTR(GetEnemyStateComponent())

		damageStruct.Element1 = skillDA->SkillElement1;
	damageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(skillDA->SkillEffect[0], EnemyOwner->EnemyArrowComponent, FName(TEXT("")),
		FVector(0.0f, 0.0f, -25.0f), FRotator(0.0f), EAttachLocation::SnapToTarget, true);

	lifeTime = skillDA->LifeTime;
	radius = skillDA->AttackDistance;

	niagara->SetUsingAbsoluteRotation(true);
	niagara->SetFloatParameter(FName("Radius"), radius);
	niagara->SetFloatParameter(FName("LifeTime"), lifeTime);
	niagara->ResetSystem();

	world->GetTimerManager().SetTimer(timerHandle, [this, world, lifeTime, radius, damageStruct]()
		{
			if (CheckData() || EnemyOwner->bIsDead)
				return;

			FrostveilAuraSubFunc(world, lifeTime, radius, damageStruct, EnemyDamage);
		}, 0.5f, false);

	FrostveilPassive();
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::FrostveilAuraSubFunc(UWorld* world, float auraLifeTime, const float auraRadius, const FDamageStruct auraDamage, FStatRange enemyDamage)
{
	if (CheckData())
		return;

	ACharacterMaster* character = nullptr;
	float lifeTime = auraLifeTime;
	float radius = auraRadius;
	FVector location = {};
	FTimerHandle timerHandle = {};
	FDamageStruct damageStruct = auraDamage;

	damageStruct.Damage = enemyDamage.GetValueFromRange() / 10.0f;
	location = EnemyOwner->GetActorLocation();

	character = TryGetPlayerCharacter(radius, location, world);
	if (character)
		character->DealDamage(damageStruct);

	lifeTime -= 0.5f;

	if (lifeTime <= 0.0f)
		return;

	world->GetTimerManager().SetTimer(timerHandle, [this, world, lifeTime, radius, damageStruct, enemyDamage]()
		{
			if (IsValid(this))
				FrostveilAuraSubFunc(world, lifeTime, radius, damageStruct, enemyDamage);
		}, 0.5f, false);
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::UseSkillBlizzard()
{
	if (CheckData())
		return;

	AZoneSA* skillBlizzard = nullptr;
	USkillAttackDA* skillDA = GetCurrentSkillDA<USkillAttackDA>();
	FActorSpawnParameters spawnParams = {};

	CHECK_PTR(skillDA)
	CHECK_PTR(PawnTarget)

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	skillBlizzard = GetWorld()->SpawnActor<AZoneSA>(skillDA->AttackProjectyle, PawnTarget->GetActorLocation(), EnemyOwner->GetActorRotation(), spawnParams);
	CHECK_PTR(skillBlizzard)

	skillBlizzard->InitParam(0.0f, EnemyDA, EnemyOwner, skillDA);
}
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::DealDamageIfNotSpawn(FDamageStruct& damageStruct)
{
	if (CheckData())
		return;

	CHECK_PTR(GetAIBrainComponent())

	ACharacterMaster* character = Cast<ACharacterMaster>(AIBrainComponent->PawnTarget);
	CHECK_PTR(character)
	CHECK_PTR(character->GetStateComponent())

	if ((FVector::Distance(EnemyOwner->GetActorLocation(), PawnTarget->GetActorLocation())) <= 200.0f)
		character->GetStateComponent()->ApplyDamage(damageStruct);
}
//-----------------------------------------------------------------------------------------------------------
void UEnemySC::SpawnSkillProjectile(bool bIsHoming)
{
	if (CheckData())
		return;

	CHECK_PTR(GetAIBrainComponent())

	float damage = 0.0f;
	ACharacter* targetCharacter = nullptr;
	AProjectileSA* projectile = nullptr;
	FActorSpawnParameters spawnParams = {};
	USkillAttackDA* skillDA = GetCurrentSkillDA<USkillAttackDA>();

	CHECK_PTR(skillDA)
	CHECK_PTR(skillDA->AttackProjectyle)

	targetCharacter = Cast<ACharacter>(PawnTarget);
	CHECK_PTR(targetCharacter)
	CHECK_PTR(GetEnemyStateComponent())

		damage = EnemyDamage.GetValueFromRange() + skillDA->SkillAttackDamage.GetValueFromRange();

	// Получаем позицию сокета для спавна снаряда
	FVector spawnLocation = EnemyOwner->GetMesh()->GetSocketByName(skillDA->SkillSocketBoneName)->GetSocketLocation(EnemyOwner->GetMesh());
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	DamageStruct.Damage = damage;
	DamageStruct.Element1 = skillDA->SkillElement1;
	DamageStruct.ElementChanse = EnemyStateComponent->FindElementChanseFromElement(skillDA->SkillElement1);

	projectile = GetWorld()->SpawnActor<AProjectileSA>(skillDA->AttackProjectyle, spawnLocation, EnemyOwner->GetActorRotation(), spawnParams);
	if (!projectile)
	{
		//Если не заспавнился
		DealDamageIfNotSpawn(DamageStruct);
		return;
	}

	projectile->InitParam(DamageStruct, skillDA);

	if (bIsHoming)
		projectile->MakeProjectileHoming(targetCharacter->GetMesh());
}
//-----------------------------------------------------------------------------------------------------------
#pragma region Passive
void UEnemySC::FrostveilPassive()
{
	if (CheckData())
		return;

	if (FMath::RandRange(0.0f, 100.0f) > 40.75f)
		return;

	float enemyHealth = 1.0f;
	UWorld* world = nullptr;
	UWorldRuler* worldRuler = nullptr;
	AEnemyMaster* enemy = nullptr;
	FActorSpawnParameters spawnParams = {};
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	world = GetWorld();
	CHECK_PTR(world)

	worldRuler = world->GetSubsystem<UWorldRuler>();
	CHECK_PTR(worldRuler)

	enemy = world->SpawnActor<AEnemyMaster>(EnemyDA->EnemyClass, EnemyOwner->GetActorLocation(), FRotator{ 0.0f }, spawnParams);

	PTR(enemy)->SetDataAsset(EnemyDA);
	enemy->Tags.Add(FName("Illusion"));
	enemy->InitEnemy(worldRuler->GetPortalStat(), PawnTarget);

	if (enemy->GetDropComponent())
		enemy->DestroyDropComponent();

	CHECK_WEAK_PTR(enemy->GetEnemyStateComponent())

		TMap<EStateName, float>& stateMap = enemy->GetEnemyStateComponent()->GetStateMap();
	if (stateMap.Contains(EStateName::HealthMax) && stateMap.Contains(EStateName::Health))
	{
		*stateMap.Find(EStateName::Health) = enemyHealth;
		*stateMap.Find(EStateName::HealthMax) = enemyHealth;
	}

	enemy->ReactivateAndTeleport(true);
}
//***********************************************************************************************************
#pragma endregion
//-----------------------------------------------------------------------------------------------------------