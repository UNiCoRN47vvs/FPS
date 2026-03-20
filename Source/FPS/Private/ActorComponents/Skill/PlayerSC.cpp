#include "ActorComponents/Skill/PlayerSC.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "SubSystem/EventBus.h"
#include "SkillActors/SkillActor.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
UPlayerSC::UPlayerSC()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::BeginPlay()
{
	Super::BeginPlay();

	UEventBus::OnPlayerSkill.AddUObject(this, &UPlayerSC::SetCurrentSkill);

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UEventBus::OnPlayerSkill.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::InitSkillComponent(USkeletalMeshComponent* skeletalMeshComponent, UCameraComponent* cameraComponent)
{
	SkeletalMeshComponent = skeletalMeshComponent;
	PlayerCameraComponent = cameraComponent;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::SetCurrentSkill(USkillScrollDA* scrollDA)
{
	ScrollDA = scrollDA;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::UseMagicBall()
{
	CHECK_PTR(ScrollDA)
	CHECK_PTR(SkeletalMeshComponent)
	CHECK_PTR(PlayerCameraComponent)

	bool bIsTouch = false;
	float elementsChance = 0.0f;
	ASkillActor* skillProjectile = nullptr;
	FVector startLocation = {};
	FVector endLocation = {};
	FVector socketLocation = {};
	FHitResult hitResult = {};
	FRotator rotation = {};
	TArray<AActor*> ignores = {};

	UEventBus::OnApplySelectedScroll.ExecuteIfBound();
	startLocation = PlayerCameraComponent->GetComponentLocation();
	endLocation = PlayerCameraComponent->GetForwardVector() * 19999.0 + startLocation;

	bIsTouch = UKismetSystemLibrary::LineTraceSingle(this, startLocation, endLocation, ETraceTypeQuery::TraceTypeQuery3, false, ignores,
		EDrawDebugTrace::None, hitResult, true);

	socketLocation = SkeletalMeshComponent->GetSocketLocation(ScrollDA->SkillSocketBoneName);

	if(bIsTouch)
		rotation = FRotationMatrix::MakeFromX(hitResult.Location - socketLocation).Rotator();
	else
		rotation = FRotationMatrix::MakeFromX(hitResult.TraceEnd - socketLocation).Rotator();

	skillProjectile = GetWorld()->SpawnActor<ASkillActor>(ScrollDA->AttackProjectile, socketLocation, rotation, SpawnParams);
	CHECK_PTR(skillProjectile)

	if (UEventBus::OnPlayerElementsChance.IsBound())
		elementsChance = UEventBus::OnPlayerElementsChance.Execute(ScrollDA->SkillElement1);

	skillProjectile->InitParam(ScrollDA, elementsChance, GetOwner());
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::UseLightningWall()
{
	CHECK_PTR(ScrollDA)
	CHECK_PTR(SkeletalMeshComponent)
	CHECK_PTR(PlayerCameraComponent)

	bool bIsTouch = false;
	ASkillActor* skillProjectile = nullptr;
	float elementsChance = 0.0f;
	FVector socketLocation = {};
	FVector startLocation = {};
	FVector endLocation = {};
	FRotator rotation = {};
	FHitResult hitResult = {};
	TArray<AActor*> ignores = {};

	UEventBus::OnApplySelectedScroll.ExecuteIfBound();

	startLocation = PlayerCameraComponent->GetComponentLocation();
	endLocation = PlayerCameraComponent->GetForwardVector() * 19999.0 + startLocation;

	socketLocation = SkeletalMeshComponent->GetSocketLocation(ScrollDA->SkillSocketBoneName);
	
	bIsTouch = UKismetSystemLibrary::LineTraceSingle(this, startLocation, endLocation, ETraceTypeQuery::TraceTypeQuery3, false, ignores,
		EDrawDebugTrace::None, hitResult, true);

	if (bIsTouch)
		rotation = FRotationMatrix::MakeFromX(hitResult.Location - socketLocation).Rotator();
	else
		rotation = FRotationMatrix::MakeFromX(hitResult.TraceEnd - socketLocation).Rotator();


	skillProjectile = GetWorld()->SpawnActor<ASkillActor>(ScrollDA->AttackProjectile, socketLocation, rotation, SpawnParams);
	CHECK_PTR(skillProjectile)

	if (UEventBus::OnPlayerElementsChance.IsBound())
		elementsChance = UEventBus::OnPlayerElementsChance.Execute(ScrollDA->SkillElement1);

	skillProjectile->InitParam(ScrollDA, elementsChance, GetOwner());
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerSC::UseIceGroundAttack()
{
	AActor* owner = GetOwner();
	ASkillActor* skillActor = nullptr;
	float elementsChance = 0.0f;
	FVector location = {};

	CHECK_PTR(owner)
	UEventBus::OnApplySelectedScroll.ExecuteIfBound();

	location = owner->GetActorLocation() - FVector(0.0f, 0.0f, 90.0f);

	skillActor = GetWorld()->SpawnActor<ASkillActor>(ScrollDA->AttackProjectile, location, owner->GetActorRotation(), SpawnParams);

	CHECK_PTR(skillActor)

	if (UEventBus::OnPlayerElementsChance.IsBound())
		elementsChance = UEventBus::OnPlayerElementsChance.Execute(ScrollDA->SkillElement1);

	skillActor->InitParam(ScrollDA, elementsChance, owner);
}
//-----------------------------------------------------------------------------------------------------------


