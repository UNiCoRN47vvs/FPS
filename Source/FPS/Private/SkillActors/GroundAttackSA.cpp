#include "SkillActors/GroundAttackSA.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Components/BoxComponent.h"
#include "Character/CharacterMaster.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
AGroundAttackSA::AGroundAttackSA()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("Box Component")));

	RootComponent = NiagaraComponent;
	BoxComponent->SetupAttachment(NiagaraComponent);

	LengthSize = 2000.0f;
	WidthSize = 180.0f;
}
//-----------------------------------------------------------------------------------------------------------
void AGroundAttackSA::InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner)
{
	if (!scrollDA || !owner)
	{
		ALARM_LOG
		Destroy();
		return;
	}

	if (!scrollDA->ProjectileNiagara.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(scrollDA->ProjectileNiagara.ToSoftObjectPath(), [&]()
			{
				AsyncTask(ENamedThreads::GameThread, [&]()
					{
						InitParam(scrollDA, elementChance, owner);
					});
			});
		return;
	}

	float value = 0.0f;
	float timerTime = 0.09f;

	ScrollDA = scrollDA;
	DamageStruct.ElementChanse = elementChance;
	DamageStruct.DamageOwner = owner;
	DamageStruct.Element1 = ScrollDA->ElementType;

	NiagaraComponent->SetAsset(ScrollDA->ProjectileNiagara.Get());

	NiagaraComponent->SetFloatParameter(FName("Width"), WidthSize);
	NiagaraComponent->SetFloatParameter(FName("Long"), LengthSize);

	NiagaraComponent->ResetSystem();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGroundAttackSA::BeginOverlap);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AGroundAttackSA::DestroyAfterNiagara);

	if (!World)
	{
		World = GetWorld();
		CHECK_PTR(World)
	}

	value = LengthSize / 10.0f;

	for (int32 i = 0; i < 5; ++i)
	{
		FTimerHandle timerHandle = {};
		World->GetTimerManager().SetTimer(timerHandle, [this, value]()
			{
				ApplyTimerSize(value);
			}, timerTime, false);

		timerTime += 0.09f;
	}
}
//-----------------------------------------------------------------------------------------------------------
void AGroundAttackSA::ApplyTimerSize(float value)
{
	float lengthSize = 0.0f;
	FVector boxSize = BoxComponent->GetUnscaledBoxExtent();

	lengthSize = boxSize.X + value;

	BoxComponent->SetBoxExtent(FVector(lengthSize, WidthSize, boxSize.Z));
	BoxComponent->SetRelativeLocation(FVector(lengthSize, 0.0f, 0.0f));
}
//-----------------------------------------------------------------------------------------------------------
void AGroundAttackSA::BeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	int32 index = 0;
	ACharacterMaster* character = nullptr;

	if (CharacterArray.Find(otherActor, index))
		return;

	character = Cast<ACharacterMaster>(otherActor);
	CHECK_PTR(character)
	CHECK_PTR(ScrollDA)

	DamageStruct.Damage = ScrollDA->SkillAttackDamage.GetValueFromRange();
	character->DealDamage(DamageStruct, sweepResult);

	CharacterArray.Add(otherActor);
}
//-----------------------------------------------------------------------------------------------------------
