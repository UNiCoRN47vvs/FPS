#include "Enemies/EnemyMaster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "SubSystem/EventBus.h"
#include "SubSystem/WorldRuler.h"
#include "ActorComponents/State/EnemyStateComponent.h"
#include "ActorComponents/State/PlayerStateComponent.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Chest/ChestComponent.h"
#include "ActorComponents/AI/AIBrainComponent.h"
#include "ActorComponents/Enemy/DebuffWidgetComponent.h"
#include "ActorComponents/Drop/DropComponent.h"
#include "ActorComponents/Skill/EnemySC.h"
#include "Enemies/EnemyAIController.h"
#include "Interact/InteractMaster.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
#define ENEMY_DA\
	if (!EnemyDA){\
		EnemyDA = GetConfigDA<UEnemyMasterDA>();\
		if (!EnemyDA){\
			ALARM_LOG\
				Destroy();\
			return;}}\
//-----------------------------------------------------------------------------------------------------------
AEnemyMaster::AEnemyMaster()
{
	PrimaryActorTick.bCanEverTick = true;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	EnemyArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));

	NiagaraComponent->SetupAttachment(GetMesh());
	NiagaraComponent->SetAbsolute(false, true, false);
	NiagaraComponent->SetWorldRotation(FRotator(90.0, 0.0, 0.0));
	NiagaraComponent->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	NiagaraComponent->SetRelativeLocation(FVector(0.0, 0.0, 100.0));	
	EnemyArrowComponent->SetupAttachment(GetMesh());

	bIsDead = false;
	EnemyUpdateRate = 0.1;

	for (FEnemySkillPoints& item : EnemySkillPoints)
	{
		item.SkillPoints *= EnemyUpdateRate;
	}

	Tags.Add(FName("Enemy"));
	GetMesh()->ComponentTags.Add(FName("BulletTarget"));
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if(GetConfigDA<UEnemyMasterDA>())
		GetMesh()->SetSkeletalMesh(GetConfigDA<UEnemyMasterDA>()->SkeletalMesh);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	if (GetChestComponent())
	{
		GetChestComponent()->InvSlotsPerRow = 5;
		GetChestComponent()->InvMaxSlots = 10;
		GetChestComponent()->InitStorage();
	}

	if (GetDebuffWidgetComponent().IsValid())
		GetDebuffWidgetComponent()->InitWidgetComponent(GetStateComponent());

	GetCharacterMovement()->MaxWalkSpeed += FMath::RandRange(0.0f, GetCharacterMovement()->MaxWalkSpeed * 0.1f);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FTimerManager& timerManager = GetWorld()->GetTimerManager();

	timerManager.ClearTimer(EnemyHandle);
	timerManager.ClearTimer(DeathTimerHandle);
	timerManager.ClearTimer(DeleteComponentsHandle);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::InitEnemyDA()
{
	ENEMY_DA

	if (GetEnemyStateComponent().IsValid())
		GetEnemyStateComponent()->SetEnemyStateMap(EnemyDA->EnemyStateMap);

	CHECK_PTR(GetEnemySC())
	EnemySC->SetEnemyDamage(EnemyDA->EnemyAttackDamage);
	//*******************************
	//Тестово
	SpawnDefaultController();
	GetAIBrainComponent()->InitAIBrain(this, EnemyDA);
	GetAIBrainComponent()->AITrigger(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//*******************************
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::AttackAfterMove()
{
	CHECK_WEAK_PTR(GetAIBrainComponent())

	AIBrainComponent->AttackAfterMove();
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::TESTING_Activate_Enemy(APawn* Pawn, UEnemyMasterDA* EnemyDataAsset, int32 portalLevel, EItemGrade portalGrade)
{
	EnemyDA = EnemyDataAsset;

	ENEMY_DA
		
	if (!GetAIBrainComponent().IsValid() || !GetStateComponent() || !GetChestComponent())
	{
		ALARM_LOG
			Destroy();
		return;
	}

	PawnTarget = Pawn;
	InitEnemyDA();
	SpawnDefaultController();
	AIBrainComponent->InitAIBrain(this, EnemyDA);
	AIBrainComponent->AITrigger(Pawn);	
	GetWorld()->GetTimerManager().SetTimer(EnemyHandle, this, &AEnemyMaster::EnemyUpdate, EnemyUpdateRate, true);

	UWorldRuler* worldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
	CHECK_PTR(worldRuler)
		
	worldRuler->TESTING_Set_Portal_Stat(portalLevel, portalGrade);

	PTR(GetStateComponent())->InitStateComponent(worldRuler->GetPortalStat());
	CHECK_PTR(GetEnemySC())

	EnemySC->InitEnemySC(this, EnemyDA, PawnTarget);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::InitEnemy(const FPortalStat& PortalStat, APawn* Pawn)
{
	ENEMY_DA

	if (!GetAIBrainComponent().IsValid() || !GetStateComponent() || !GetChestComponent())
	{
		ALARM_LOG
		Destroy();
		return;
	}

	PawnTarget = Pawn;
	
	SpawnDefaultController();
	AIBrainComponent->InitAIBrain(this, EnemyDA);
	
	EnemyStateComponent->InitStateComponent(PortalStat);

	AIBrainComponent->AITrigger(Pawn);

	CHECK_PTR(GetEnemySC())

	EnemySC->InitEnemySC(this, EnemyDA, PawnTarget);

	GetWorld()->GetTimerManager().SetTimer(EnemyHandle, this, &AEnemyMaster::EnemyUpdate, EnemyUpdateRate, true);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::EnemyUpdate()
{			
	if (bIsDead)
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemyHandle);
		return;
	}
	
	if (GetAIBrainComponent().IsValid())
	{
		for (const FEnemySkillPoints& item : EnemySkillPoints)
		{
			AIBrainComponent->SkillImpact(item.SkillType, item.SkillPoints);
		}
	}

	 // Снижение реакции на попадание
	for (int32 i = PhysicsBodiesArray.Num() - 1; i >= 0; --i)
	{
		PhysicsBodiesArray[i].PhysicsBlendWeight -= 0.25;
		GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(PhysicsBodiesArray[i].BoneName, PhysicsBodiesArray[i].PhysicsBlendWeight);

		if (PhysicsBodiesArray[i].PhysicsBlendWeight <= 0.0)
		{
			GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(PhysicsBodiesArray[i].BoneName, 0.0);
			GetMesh()->SetAllBodiesBelowSimulatePhysics(PhysicsBodiesArray[i].BoneName, false);
			PhysicsBodiesArray.RemoveAt(i);
		}
	}

	if (PawnTarget)
	{
		FVector startLocation = GetActorLocation();
		FVector playerLocation = PawnTarget->GetActorLocation();
		FRotator rotation = (playerLocation - startLocation).Rotation();

		if(GetDebuffWidgetComponent().IsValid())
			DebuffWidgetComponent->SetWorldRotation(rotation);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, PlayerLocation.ToString());
	}
}
//-----------------------------------------------------------------------------------------------------------
TWeakObjectPtr<UDebuffWidgetComponent> AEnemyMaster::GetDebuffWidgetComponent()
{
	if (!DebuffWidgetComponent.IsValid())
		DebuffWidgetComponent = FindComponentByClass<UDebuffWidgetComponent>();
	
	return DebuffWidgetComponent;
}
TWeakObjectPtr<UAIBrainComponent> AEnemyMaster::GetAIBrainComponent()
{
	if(!AIBrainComponent.IsValid())
		AIBrainComponent = FindComponentByClass<UAIBrainComponent>();
	return AIBrainComponent;
}
TWeakObjectPtr<UEnemyStateComponent> AEnemyMaster::GetEnemyStateComponent()
{
	if (!EnemyStateComponent.IsValid())
		EnemyStateComponent = FindComponentByClass<UEnemyStateComponent>();

	return EnemyStateComponent;
}
ACharacterMaster* AEnemyMaster::TryGetPlayerCharacter(float radius, const FVector& location, UWorld* world)
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
UDropComponent* AEnemyMaster::GetDropComponent()
{
	if (!DropComponent)
		DropComponent = FindComponentByClass<UDropComponent>();
	return DropComponent;
}
UEnemySC* AEnemyMaster::GetEnemySC()
{
	if (!EnemySC)
		EnemySC = FindComponentByClass<UEnemySC>();
	return EnemySC;
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::ApplyDeath()
{
	ENEMY_DA

	Super::ApplyDeath();

	bIsDead = true;

	if (ActorHasTag(FName("Illusion")))
	{
		ApplyIllusionDeathEffect();
		return;
	}

	// Включаем физическую симуляцию и отключаем компоненты, не нужные после смерти
	if (GetMesh())
	{
		if(GetMesh()->GetAnimInstance())
			GetMesh()->GetAnimInstance()->StopAllMontages(0.0);

		GetMesh()->SetSimulatePhysics(true);
	}


	if (GetCapsuleComponent())
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (GetAIBrainComponent().IsValid())
	{
		AIBrainComponent->Deactivate();
		AIBrainComponent->DestroyComponent();
	}

	if (GetEnemySC())
	{
		EnemySC->Deactivate();
		EnemySC->DestroyComponent();
		EnemySC = nullptr;
	}

	if (GetMovementComponent())
	{
		GetMovementComponent()->Deactivate();
		GetMovementComponent()->DestroyComponent();
	}

	if (GetEnemyStateComponent().IsValid())
	{
		EnemyStateComponent->Deactivate();
		EnemyStateComponent->DestroyComponent();
	}

	if (GetDebuffWidgetComponent().IsValid())
	{
		DebuffWidgetComponent->Deactivate();
		DebuffWidgetComponent->DestroyComponent();
	}

	if (GetController())
		GetController()->Destroy();
	
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &AEnemyMaster::CheckAndDisablePhysics, 3.0, true);

	if(GetDropComponent())
		DropComponent->SearchDrop(EnemyDA->DTSpecialDrop);

	//Реализация БОРОСА (Ник: Get_Boros)
	GetWorld()->GetTimerManager().SetTimer(DeleteComponentsHandle, [this]()
		{ 
			GetWorld()->GetTimerManager().SetTimer(DeleteComponentsHandle, [this]() 
				{
					if (IsValid(GetChestComponent()) && GetChestComponent()->IsStorageEmpty())
					{
						DeleteEnemyComponents();
						GetWorld()->GetTimerManager().ClearTimer(DeleteComponentsHandle);
					}
				}, 0.5, true);
		}, 3.0, false);

	UEventBus::OnEnemyDeath.Broadcast(EnemyDA);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::ApplyIllusionDeathEffect()
{
	ENEMY_DA

	if (!EnemyDA->IllusionDeathEffect.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(EnemyDA->IllusionDeathEffect.ToSoftObjectPath(), [this]
			{
				AsyncTask(ENamedThreads::GameThread, [this]
					{
						if(this)
							ApplyIllusionDeathEffect();
					});
			});
		return;
	}

	GetMesh()->SetVisibility(false);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EnemyDA->IllusionDeathEffect.Get(), GetActorLocation(), FRotator{}, FVector{ 1.0f });

	Destroy();
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::CheckAndDisablePhysics()
{
	CHECK_PTR(GetMesh())

	UDropComponent* dropComponent = nullptr;
	const float velocityThreshold = 1.0;
	FVector linearVelocity = GetMesh()->GetPhysicsLinearVelocity();
	FVector angularVelocity = GetMesh()->GetPhysicsAngularVelocityInDegrees();

	if (linearVelocity.Size() < velocityThreshold && angularVelocity.Size() < velocityThreshold)
	{
		GetMesh()->bPauseAnims = true;         
		GetMesh()->bNoSkeletonUpdate = true;
		GetMesh()->SetComponentTickEnabled(false);

		GetMesh()->SetSimulatePhysics(false);
		GetWorld()->GetTimerManager().ClearTimer(DeathTimerHandle);

		dropComponent = FindComponentByClass<UDropComponent>();
		CHECK_PTR(dropComponent)

		dropComponent->Deactivate();
		dropComponent->DestroyComponent();
	}
}
//-----------------------------------------------------------------------------------------------------------
USkeletalMeshComponent* AEnemyMaster::GetCharacterMesh()
{
	return GetMesh();
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::DealDamage(FDamageStruct& damageStruct, FHitResult hitResult)
{
	if (bIsDead)
		return;

	UNiagaraComponent* niagara = nullptr;

	ENEMY_DA

	if (hitResult.BoneName != FName("pelvis"))
	{
		//Реакция на попадание
		int32 boneIndex = GetMesh()->GetBoneIndex(hitResult.BoneName);
		FPhysicsBody physicsBody = {};
		FVector impact = hitResult.ImpactNormal * FVector(-1.0, -1.0, -1.0);
		if (boneIndex != INDEX_NONE)
		{
			physicsBody.BoneName = hitResult.BoneName;
			physicsBody.PhysicsBlendWeight = 0.5f;
			GetMesh()->SetAllBodiesBelowSimulatePhysics(hitResult.BoneName, true);
			GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(hitResult.BoneName, physicsBody.PhysicsBlendWeight);
			GetMesh()->AddImpulseToAllBodiesBelow(hitResult.ImpactNormal * -1450.0f, hitResult.BoneName);
			PhysicsBodiesArray.Add(physicsBody);
		}
	}

	GetStateComponent()->ApplyDamage(damageStruct);

	CHECK_PTR(EnemyDA->TakingHitEffect)

	FTransform transform = {};
	transform.SetLocation(hitResult.Location);
	transform.SetRotation(UKismetMathLibrary::MakeRotFromX(this->GetActorLocation() - hitResult.Location).Quaternion());
	transform.SetScale3D(FVector(1.0f));

	niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EnemyDA->TakingHitEffect, transform.GetLocation(),
		transform.GetRotation().Rotator(), transform.GetScale3D());

	niagara->SetVariableLinearColor(FName(TEXT("Color")), EnemyDA->TakingHitEffectColor);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::DeleteEnemyComponents()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
		{
			PrimaryActorTick.bCanEverTick = false;

			if (NiagaraComponent)
			{
				NiagaraComponent->Deactivate();
				NiagaraComponent->DestroyComponent();
				NiagaraComponent = nullptr;
			}

			if (GetChestComponent())
			{
				ChestComponent->Deactivate();
				ChestComponent->DestroyComponent();
				ChestComponent = nullptr;
			}
		});
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	if (!PlayerCharacter || !IsValid(GetChestComponent()) || !bIsDead || bIsDead && IsValid(GetChestComponent()) && GetChestComponent()->IsStorageEmpty())
		return;

	PlayerCharacter->ApplyInteract(EStorageType::TreasureInventory, GetChestComponent());
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::ApplyDrop(FItemInvStruct& Item, UNiagaraSystem* Niagara, FLinearColor Color)
{
	CHECK_PTR(Niagara)
	CHECK_PTR(GetChestComponent())
	CHECK_PTR(NiagaraComponent)
	
	ChestComponent->PickUpItem(Item.ItemCount, Item.ItemDA, 0, Item.StatValue);
	
	if (ChestComponent->IsStorageEmpty())
		return;

	NiagaraComponent->SetAsset(Niagara);
	NiagaraComponent->SetRelativeLocation(FVector(0.0, 0.0, 100.0));
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	bCanInteract = true;

	NiagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), Color);
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct AEnemyMaster::GetInteractInfo()
{
	FInteractStruct interactStruct = {};
	if (!bCanInteract)
		return interactStruct;

	if (!EnemyDA)
	{
		EnemyDA = GetConfigDA<UEnemyMasterDA>();
		if (!EnemyDA)
		{
			ALARM_LOG
			return interactStruct;
		}
	}

	interactStruct.InteractButton = EnemyDA->InteractButton.ToString();
	interactStruct.ItemName = EnemyDA->EnemyName.ToString();
	interactStruct.IteractAction = EnemyDA->IteractAction.ToString();
	return interactStruct;
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::HitReaction()
{
	Super::HitReaction();
	ENEMY_DA

	CHECK_PTR(EnemyDA->SoundHit)
	UGameplayStatics::PlaySoundAtLocation(this, EnemyDA->SoundHit, GetActorLocation());
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::PickUpEnemyLoot(UInventoryComponent* inventoryComponent)
{
	if (!IsValid(GetChestComponent()) || !bIsDead || !inventoryComponent)
		return;
	
	FItemInvStruct currentItem = {};
	TArray<FItemInvStruct> storage = ChestComponent->GetStorage();

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		if (!storage[i].bOccupied)
			continue;

		currentItem = storage[i];

		inventoryComponent->PickUpItem(storage[i].ItemCount, storage[i].ItemDA, storage[i].ItemLevel, storage[i].StatValue);
		
		if (currentItem.ItemCount == storage[i].ItemCount)
			continue;

		currentItem.ItemCount -= storage[i].ItemCount;

		UEventBus::OnFastPickUp.ExecuteIfBound(currentItem);

		ChestComponent->SetItemFromIndex(storage[i], ChestComponent->CurrentActiveInvTab, i);
	}
}
//-----------------------------------------------------------------------------------------------------------
bool AEnemyMaster::IsDefenseSkillActive()
{
	if (GetEnemyStateComponent().IsValid())
		return EnemyStateComponent->IsDefenseSkillActive();

	return false;
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::EnemyClearing()
{
	bool tempBool1 = !IsValid(GetChestComponent()) || GetChestComponent()->IsStorageEmpty();

	if (bIsDead && tempBool1)
		this->Destroy();
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::SetDataAsset(UCharacterMasterDA* DataAsset)
{
	DataAssetConfig = DataAsset;

	InitEnemyDA();
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::Reactivate()
{
	FNavLocation navLocation = {};

	if (GetMovementComponent() && GetMovementComponent()->IsFalling())
	{
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AEnemyMaster::Reactivate, 1.0, false);
		return;
	}

	if (!NavSys)
	{
		NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		CHECK_PTR(NavSys)
	}

	if (!NavSys->ProjectPointToNavigation(GetActorLocation(), navLocation))
	{
		ReactivateAndTeleport();
		return;
	}

	CHECK_WEAK_PTR(GetAIBrainComponent())

	AIBrainComponent->MoveToRandomPoint();
}
void AEnemyMaster::ReactivateAndTeleport(bool bIsSelfCenter)
{
	bool bIsTouch = false;

	int32 infinityBlock = 60;
	float spawnRadius = 30000.0;

	FHitResult hitResult = {};
	FVector spawnCenterLocation = {};
	FVector randomPoint = {};
	FNavLocation navRandomPoint(spawnCenterLocation);
	FPathFindingQuery query = {};
	FTimerHandle timerHandle = {};
	TArray<AActor*> sphereTraceIgnore = {};
	TArray<AActor*> lineTraceIgnore = {};

	if (bIsSelfCenter)
		spawnCenterLocation = GetActorLocation();
	else
		spawnCenterLocation = PawnTarget->GetActorLocation();

	sphereTraceIgnore.Add(PawnTarget);

	if (!NavSys)
	{
		NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		CHECK_PTR(NavSys)
	}
	if (!UseNavData)
	{
		UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
		CHECK_PTR(UseNavData)
	}

	do
	{
		NavSys->GetRandomReachablePointInRadius(spawnCenterLocation, spawnRadius, navRandomPoint, UseNavData,
			UNavigationQueryFilter::GetQueryFilter(*UseNavData, GetWorld(), UNavigationQueryFilter::StaticClass()));
		randomPoint = navRandomPoint.Location + FVector(0.0, 0.0, 65.0); //TODO : Пересмотреть положение

		bIsTouch = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), randomPoint + FVector(0.0, 0.0, 90.0), randomPoint + FVector(0.0, 0.0, 200.0), 60.0,
			ETraceTypeQuery::TraceTypeQuery1, false, sphereTraceIgnore, EDrawDebugTrace::None, hitResult, true);

		//Проверка найден ли путь между местом спавна и игроком`
		query.StartLocation = randomPoint;
		query.EndLocation = spawnCenterLocation;
		query.NavData = UseNavData;

		if (bIsTouch || FVector::Distance(randomPoint, spawnCenterLocation) <= 975.0f || !NavSys->TestPathSync(query))
		{
			--infinityBlock;
			continue;
		}

		break;
		
	} while (infinityBlock > 0);

	if (infinityBlock <= 0)
	{
		GetWorld()->GetTimerManager().SetTimer(timerHandle, [this, randomPoint]()
			{
				Reactivate();
			}, 1.25, false);
	}
	else
	{
		TeleportTo(randomPoint, FRotator{});
		Reactivate();
	}
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::DestroyDropComponent()
{
	GetDropComponent()->Deactivate();
	GetDropComponent()->DestroyComponent();
	DropComponent = nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyMaster::ApplySkillMontageEffect()
{
	
}