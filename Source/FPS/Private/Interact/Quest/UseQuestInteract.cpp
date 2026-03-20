#include "Interact/Quest/UseQuestInteract.h"
#include "Components/BoxComponent.h"
#include "SubSystem/WorldRuler.h"
//-----------------------------------------------------------------------------------------------------------
AUseQuestInteract::AUseQuestInteract()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AUseQuestInteract::InitInteractQuest()
{
	PTR(CollisionBox)->OnComponentBeginOverlap.AddDynamic(this, &AUseQuestInteract::OnComponentBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AUseQuestInteract::OnComponentEndOverlap);
}
//-----------------------------------------------------------------------------------------------------------
void AUseQuestInteract::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(FName(TEXT("Player"))))
		return;

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	WorldRuler->QuestTargets.Add(QuestInteractDA);
}
//-----------------------------------------------------------------------------------------------------------
void AUseQuestInteract::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->ActorHasTag(FName(TEXT("Player"))))
		return;

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	bool bIsQuestFind = false;
	int32 questIndex = 0;

	bIsQuestFind = WorldRuler->FindQuestTarget(QuestInteractDA, questIndex);

	if (bIsQuestFind)
		WorldRuler->QuestTargets.RemoveAt(questIndex);
}
//-----------------------------------------------------------------------------------------------------------