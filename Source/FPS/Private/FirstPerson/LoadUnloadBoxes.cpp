#include "FirstPerson/LoadUnloadBoxes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
//-----------------------------------------------------------------------------------------------------------
ALoadUnloadBoxes::ALoadUnloadBoxes()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	LoadBox			= CreateDefaultSubobject<UBoxComponent>(TEXT("Load Box"));

	ArrowLoad		= CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Load"));
	ArrowUnload		= CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Unload"));

	RootComponent = SceneComponent;

	LoadBox->SetupAttachment(SceneComponent);
	ArrowLoad->SetupAttachment(SceneComponent);
	ArrowUnload->SetupAttachment(SceneComponent);

	PrimaryActorTick.bCanEverTick = true;
	LevelIndexLoad = 0;
	LevelIndexUnload = 0;
}
//-----------------------------------------------------------------------------------------------------------
void ALoadUnloadBoxes::BeginPlay()
{
	Super::BeginPlay();

	PTR(LoadBox)->OnComponentEndOverlap.AddDynamic(this, &ALoadUnloadBoxes::EndOverlapLoadBox);
}
//-----------------------------------------------------------------------------------------------------------
void ALoadUnloadBoxes::EndOverlapLoadBox(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if(!otherActor->ActorHasTag(FName(TEXT("Player"))))
		return;

	FVector relativeWorld = otherActor->GetActorLocation() - LoadBox->GetComponentLocation();

	FVector relativeLocal = LoadBox->GetComponentTransform().InverseTransformVectorNoScale(relativeWorld);

	if (relativeLocal.Y > 0)
		LoadLevels();
	else
		UnloadLevels();
}
//-----------------------------------------------------------------------------------------------------------
void ALoadUnloadBoxes::LoadLevels()
{
	if (!Levels.IsValidIndex(LevelIndexLoad))
	{
		LevelIndexLoad = 0;
		return;
	}

	FLatentActionInfo latentInfo = {};
	latentInfo.CallbackTarget = this;
	latentInfo.ExecutionFunction = "LoadLevels";
	latentInfo.Linkage = 0;
	latentInfo.UUID = __LINE__;
	
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Levels[LevelIndexLoad], true, false, latentInfo);

	++LevelIndexLoad;
	
}
//-----------------------------------------------------------------------------------------------------------
void ALoadUnloadBoxes::UnloadLevels()
{
	if (!Levels.IsValidIndex(LevelIndexUnload))
	{
		LevelIndexUnload = 0;
		return;
	}

	FLatentActionInfo latentInfo = {};
	latentInfo.CallbackTarget = this;
	latentInfo.ExecutionFunction = "UnloadLevels";
	latentInfo.Linkage = 0;
	latentInfo.UUID = __LINE__;

	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, Levels[LevelIndexUnload], latentInfo, false);
	++LevelIndexUnload;
}
//-----------------------------------------------------------------------------------------------------------