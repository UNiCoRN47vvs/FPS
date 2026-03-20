#include "ActorComponents/AI/AIBrainComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "FPS/FPSGameMode.h"
#include "ActorComponents/Skill/EnemySC.h"
#include "Config/SkillDefenseDA.h"
#include "Enemies/EnemyMaster.h"
#include "Enemies/EnemyAIController.h"
//-----------------------------------------------------------------------------------------------------------
UAIBrainComponent::UAIBrainComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MovementInterval = 5.0;
	bIsAttacking = false;
	bHasTarget = false;
	bSkillIsActive = false;
	SkillsTypeValue.Add(EEnemySkillType::Tier1, 25.0f);
	SkillsTypeValue.Add(EEnemySkillType::Tier2, 12.5f);
	SkillsTypeValue.Add(EEnemySkillType::Tier3, 6.25f);
	SkillsTypeValue.Add(EEnemySkillType::Tier4, 3.125f);
	SkillsTypeValue.Add(EEnemySkillType::Tier5, 1.5125f);
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastAction += DeltaTime;
	if (TimeSinceLastAction >= MovementInterval)
	{
		if(!bHasTarget)
			MoveToRandomPoint();
		TimeSinceLastAction = 0.0;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::BeginDestroy()
{
	if(GetWorld())
		GetWorld()->GetTimerManager().ClearTimer(TriggetFollowHandle);

	Super::BeginDestroy();
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::InitAIBrain(AEnemyMaster* EnemyMaster, UEnemyMasterDA* EnemyMasterDA)
{
	AICharacter = EnemyMaster;
	EnemyDA = EnemyMasterDA;
	if (EnemyDA)
		AttackDistance = EnemyDA->AttackDistance;
}
//-----------------------------------------------------------------------------------------------------------
UEnemySC* UAIBrainComponent::GetEnemySC()
{
	if (!EnemySC)
		EnemySC = GetOwner()->FindComponentByClass<UEnemySC>();
	
	return EnemySC;
}
//-----------------------------------------------------------------------------------------------------------
bool UAIBrainComponent::AICharacterIsValid()
{
	if (AICharacter)
		return true;
	
	AICharacter = Cast<AEnemyMaster>(GetOwner());
	if (!AICharacter)
	{
		ALARM_LOG
		return false;
	}
	return true;
}
bool UAIBrainComponent::AIControllerIsValid()
{
	if (AIController)
		return true;

	if (!AICharacter)
	{
		AICharacter = Cast<AEnemyMaster>(GetOwner());
		if (!AICharacter)
		{
			ALARM_LOG
			return false;
		}
	}

	AIController = Cast<AEnemyAIController>(AICharacter->GetController());
	if (!AIController)
	{
		ALARM_LOG
		GetOwner()->Destroy();
		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::AITrigger(APawn* Pawn)
{
	if (!IsValid(Pawn) || !IsValid(this))
	{
		ALARM_LOG
		return;
	}

	if (bIsAttacking || bIsMoving || !AICharacterIsValid() || !AIControllerIsValid() || !EnemyDA)
		return;

	if (bSkillIsActive)
	{
		MoveToRandomPoint();
		return;
	}

	FTimerHandle enemyTimer = {};

	bHasTarget = true;
	PawnTarget = Pawn;

	CurrentEnemySkill = EnemySkillChoice();

	if (CurrentEnemySkill.SkillType == EEnemySkillType::None || !CurrentEnemySkill.SkillData)
	{
		GetWorld()->GetTimerManager().SetTimer(enemyTimer, [this, Pawn] { AITrigger(Pawn); }, 0.65, false);
		return;
	}
	
	SkillDistance = CurrentEnemySkill.SkillData->AttackDistance;

	bIsMoving = true;
	CheckOpportunityAttack();
}
//-----------------------------------------------------------------------------------------------------------
FEnemySkillsData UAIBrainComponent::EnemySkillChoice()
{
	EEnemySkillType enemySkillType = EEnemySkillType::None;
	int32 stopNumber = 500;
	int32 randomSkill = 0.0;
	float randomType = 0.0f;
	TArray<FEnemySkillsData> typeSkills = {};
	if (!AICharacterIsValid())
		return FEnemySkillsData{};
	do
	{
		--stopNumber;
		for (auto& item : SkillsTypeValue)
		{
			randomType = FMath::RandRange(0.0f, 100.0f);

			if (randomType <= item.Value)
			{
				enemySkillType = item.Key;
				item.Value = item.Value / 2;
				
				for (const FEnemySkillsData& subItem : EnemyDA->EnemySkills) //ѕроверка на наличие такого же типа скила
				{
					if (Cast<USkillDefenseDA>(subItem.SkillData) && AICharacter->IsDefenseSkillActive()) //ѕровер€ем выбранный скилл это защитный и активен ли защитный скилл
						continue;

					if (subItem.SkillType == enemySkillType)
						typeSkills.Add(subItem);
				}

				if (typeSkills.IsEmpty()) //≈сли отсутствует нужный тип скила то мы продолжаем поиски иного скила
				{
					enemySkillType = EEnemySkillType::None;
					continue;
				}

				break;
			}
		}
	} while (enemySkillType == EEnemySkillType::None && stopNumber > 0);

	if (typeSkills.IsEmpty())
		typeSkills.Add(GetTier1Skill());

	randomSkill = FMath::RandRange(0, typeSkills.Num() - 1);

	return typeSkills[randomSkill];
}
//-----------------------------------------------------------------------------------------------------------
FEnemySkillsData UAIBrainComponent::GetTier1Skill()
{
	TArray<FEnemySkillsData> skillsData = {};

	for (FEnemySkillsData& item : EnemyDA->EnemySkills)
	{
		if (item.SkillType == EEnemySkillType::Tier1)
			skillsData.Add(item);	
	}
	if(skillsData.IsEmpty())
		return FEnemySkillsData{};

	return skillsData[FMath::RandRange(0, skillsData.Num() - 1)];
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::AttackEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(TriggetFollowHandle);

	bIsAttacking = false;
	bIsMoving = false;
	if (FMath::RandBool())
		MoveToRandomPoint();
	else
		AITrigger(PawnTarget);
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::MoveToRandomPoint()
{
	bool onNavMesh = false;
	UNavigationPath* path = nullptr;
	FTimerHandle handle = {};

	if (!AICharacterIsValid() || !AIControllerIsValid())
	{
		AITrigger(PawnTarget);
		return;
	}

	bHasTarget = false;
	bIsMoving = true;
	
	RandomLocation = GetRandomLocationInRadius(900.0);

	path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), GetOwner()->GetActorLocation(), RandomLocation);
	
	if (!path || !path->IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UAIBrainComponent::MoveToRandomPoint, 0.5, false);
		return;
	}

	AIController->MoveToLocation(RandomLocation);
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::CheckOpportunityAttack()
{
	UNavigationPath* path = nullptr;
	FVector ownerLocation = {};
	FVector targetLocation = {};
	FNavLocation randomPoint(targetLocation);
	if (!AIControllerIsValid())
	{
		ALARM_LOG
		return;
	}

	if (!NavSys)
		NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	CHECK_PTR(NavSys)
	CHECK_PTR(PawnTarget)

	if (!UseNavData)
		UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);

	CHECK_PTR(UseNavData)

	targetLocation = PawnTarget->GetActorLocation();
	ownerLocation = GetOwner()->GetActorLocation();

	path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ownerLocation, targetLocation);
	if (path && path->IsValid())
	{
		AIController->MoveToActor(PawnTarget, FMath::RandRange(SkillDistance - (SkillDistance * 0.12), SkillDistance + (SkillDistance * 0.12)));
		return;
	}

	for (int32 i = 0; i < 50; i++)
	{
		NavSys->GetRandomPointInNavigableRadius(targetLocation, CurrentEnemySkill.SkillData->AttackDistance, randomPoint, UseNavData);

		path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ownerLocation, randomPoint.Location);

		if (path && path->IsValid())
		{
			AIController->MoveToLocation(randomPoint.Location);
			return;
		}
	}

	MoveToRandomPoint();
}
void UAIBrainComponent::SkillImpact(EEnemySkillType skillType, float value)
{
	if(SkillsTypeValue.Contains(skillType))
		*SkillsTypeValue.Find(skillType) += value;
}
//-----------------------------------------------------------------------------------------------------------
FVector UAIBrainComponent::GetRandomLocationInRadius(float radius)
{
	bool bFound = false;
	FNavLocation randomLocation = {};

	if (!NavSys)
		NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys)
	{
		bFound = NavSys->GetRandomReachablePointInRadius(GetOwner()->GetActorLocation(), radius, randomLocation);

		if (bFound)
			return randomLocation.Location;
	}

	return GetOwner()->GetActorLocation();
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::AttackAfterMove()
{
	if (bIsAttacking)
		return;

	if (!bHasTarget)
	{
		bIsMoving = false;
		AITrigger(PawnTarget);
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			bool bIsTouch = false;
			bool bIsLineTraceTouch = false;
			bool temp1 = false;
			bool temp2 = false;
			bool temp3 = false;

			int32 infinityBlock = 500;
			float spawnRadius = 0.0f;

			UWorld* mainWorld = nullptr;

			FHitResult hitResult = {};
			FVector startLocation = {};
			FVector lineTraceOffset = {};
			FVector spawnCenterLocation = {};
			FVector randomPoint = {};
			FNavLocation navRandomPoint(spawnCenterLocation);
			FPathFindingQuery query = {};
			TArray<AActor*> sphereTraceIgnore = {};

			FHitResult lineTraceHitResult = {};
			TArray<AActor*> lineTraceIgnore = {};

			CHECK_PTR(PawnTarget)

			mainWorld = PawnTarget->GetWorld();

			CHECK_PTR(mainWorld)
			CHECK_PTR(CurrentEnemySkill.SkillData)
			
			startLocation = GetOwner()->GetActorLocation();
			spawnCenterLocation = PawnTarget->GetActorLocation();
			lineTraceOffset = startLocation + (spawnCenterLocation - startLocation).GetSafeNormal() * 100.0f;

			bIsLineTraceTouch = UKismetSystemLibrary::LineTraceSingle(mainWorld, lineTraceOffset, spawnCenterLocation, ETraceTypeQuery::TraceTypeQuery3,
				false, lineTraceIgnore, EDrawDebugTrace::None, lineTraceHitResult, true);

			if (!bIsLineTraceTouch)
			{
				AsyncTask(ENamedThreads::GameThread, [this]() 
					{
						if(this)
							AITriggerSubFunc();
					});
				return;
			}

			spawnRadius = CurrentEnemySkill.SkillData->AttackDistance;

			sphereTraceIgnore.Add(PawnTarget);

			if(!NavSys)
				NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(mainWorld);

			CHECK_PTR(NavSys)

			if(!UseNavData)
				UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);

			CHECK_PTR(UseNavData)

			do
			{
				NavSys->GetRandomReachablePointInRadius(spawnCenterLocation, spawnRadius, navRandomPoint, UseNavData,
					UNavigationQueryFilter::GetQueryFilter(*UseNavData, mainWorld, UNavigationQueryFilter::StaticClass()));

				randomPoint = navRandomPoint.Location + FVector(0.0f, 0.0f, 65.0f); //TODO : ѕересмотреть положение

				bIsLineTraceTouch = UKismetSystemLibrary::LineTraceSingle(mainWorld, randomPoint, spawnCenterLocation, ETraceTypeQuery::TraceTypeQuery3,
					false, lineTraceIgnore, EDrawDebugTrace::None, lineTraceHitResult, true);

				if (bIsLineTraceTouch)
				{
					--infinityBlock;
					continue;
				}

				bIsTouch = UKismetSystemLibrary::SphereTraceSingle(mainWorld, randomPoint + FVector(0.0f, 0.0f, 90.0f), randomPoint + FVector(0.0, 0.0, 200.0), 60.0,
					ETraceTypeQuery::TraceTypeQuery1, false, sphereTraceIgnore, EDrawDebugTrace::None, hitResult, true);

				//ѕроверка найден ли путь между местом и игроком
				query.StartLocation = randomPoint;
				query.EndLocation = spawnCenterLocation;
				query.NavData = UseNavData;

				temp1 = FVector::Distance(randomPoint, spawnCenterLocation) <= 75.0f;
				temp2 = !NavSys->TestPathSync(query);
				
				if (bIsTouch || temp1 || temp2)
				{
					--infinityBlock;
					continue;
				}	

				break;
			} while (infinityBlock > 0);

			AsyncTask(ENamedThreads::GameThread, [this, randomPoint]()
				{
					if (this)
						AIController->MoveToLocation(randomPoint);
				});
		});
}
//-----------------------------------------------------------------------------------------------------------
void UAIBrainComponent::AITriggerSubFunc()
{
	UAnimInstance* animInstance = nullptr;
	UNiagaraComponent* niagara = nullptr;
	FRotator rotator = {};

	if (!IsValid(this) || !IsValid(PawnTarget) || !AICharacterIsValid())
		return;

	if (!CurrentEnemySkill.SkillData || !CurrentEnemySkill.SkillData->AttackMontage)
	{
		MoveToRandomPoint();
		return;
	}

	// ѕоворачиваемс€ в сторону цели и начинаем анимацию атаки
	rotator.Yaw = UKismetMathLibrary::MakeRotFromX(PawnTarget->GetActorLocation() - AICharacter->GetActorLocation()).Yaw;
	AICharacter->SetActorRotation(rotator);
	//AIController->StopMovement();
	animInstance = AICharacter->GetMesh()->GetAnimInstance();
	CHECK_PTR(animInstance)
	CHECK_PTR(GetEnemySC())

	bIsAttacking = true;
	EnemySC->CurrentSkill = CurrentEnemySkill;	
	animInstance->Montage_Play(CurrentEnemySkill.SkillData->AttackMontage);
	if (FMath::RandBool() && IsValid(this))
	{
		GetWorld()->GetTimerManager().SetTimer(TriggetFollowHandle, [this]()
			{
				if (!IsValid(PawnTarget) || !IsValid(this) || !IsValid(AIController))
				{
					GetWorld()->GetTimerManager().ClearTimer(TriggetFollowHandle);
					return;
				}

				AIController->MoveToActor(PawnTarget, FMath::RandRange(SkillDistance - (SkillDistance * 0.12), SkillDistance + (SkillDistance * 0.12)));
			}, 0.1, true);
	}
	if (!CurrentEnemySkill.SkillData->SkillEffectColor.IsValidIndex(0))
		return;

	CHECK_PTR(CurrentEnemySkill.SkillData->SkillMontageEffect)

	niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(CurrentEnemySkill.SkillData->SkillMontageEffect, AICharacter->GetMesh(), FName(TEXT("")),
		FVector(0.0, 0.0, 0.0), FRotator(0.0, 0.0, 0.0), EAttachLocation::SnapToTarget, true);

	CHECK_PTR(niagara)

	niagara->SetVariableFloat(FName(TEXT("NS LifeTime")), CurrentEnemySkill.SkillData->AttackMontage->GetPlayLength());

	niagara->SetVariableLinearColor(FName(TEXT("Color")), CurrentEnemySkill.SkillData->SkillEffectColor[0]);
}