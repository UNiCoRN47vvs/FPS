#include "ActorComponents/State/HealthStaminaComponent.h"
#include "TimerManager.h"
#include "FPS/FPSCharacter.h"
//-----------------------------------------------------------------------------------------------------------
UHealthStaminaComponent::UHealthStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	StateMap.Add(EStateName::Health, 100.0);
	StateMap.Add(EStateName::HealthMax, 100.0);
	StateMap.Add(EStateName::HealthRegen, 1.0);
	StateMap.Add(EStateName::Stamina, 100.0);
	StateMap.Add(EStateName::StaminaMax, 100.0);
	StateMap.Add(EStateName::StaminaRegen, 1.0);
}
//-----------------------------------------------------------------------------------------------------------
void UHealthStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AFPSCharacter>(GetOwner());
	if (PlayerCharacter)
		PlayerCharacter->OnChangeSprint.AddDynamic(this, &UHealthStaminaComponent::WasteStaminaTimerManager);
	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("HealthStaminaComponent, PlayerCharacter = nullptr!")));

	this->OnChangeState.AddDynamic(this, &UHealthStaminaComponent::RegenTimerManager);
	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));
}
//-----------------------------------------------------------------------------------------------------------
//Getter
double UHealthStaminaComponent::GetStateMapElem(EStateName StateName)
{
	double* LocalValue = StateMap.Find(StateName);
	if (LocalValue)
		return *LocalValue;
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("HealthStaminaComponent, LocalValue = Map Elem not found!")));
		return 0.0;
	}
}
//-----------------------------------------------------------------------------------------------------------
//Regen
void UHealthStaminaComponent::RegenHealth()
{	
	ChangeStateValue(EStateName::Health, GetStateMapElem(EStateName::HealthRegen), true);
}
void UHealthStaminaComponent::RegenStamina()
{
	if(!bStaminaTimerBlock)
		ChangeStateValue(EStateName::Stamina, GetStateMapElem(EStateName::StaminaRegen), true);
}
void UHealthStaminaComponent::RegenTimerManager(EStateName StateName, double CurrentValue, double MaxValue)
{
	double LocalTimerTime = 0.0;
	FTimerHandle* LocalTimerHandle = nullptr;
	FTimerDelegate LocalTimerDel;
	switch (StateName)
	{
	case EStateName::Health:
	{
		LocalTimerHandle = &HealthTimerHandle;
		LocalTimerDel = FTimerDelegate::CreateUObject(this,  &UHealthStaminaComponent::RegenHealth);
		LocalTimerTime = 10.0;
		break;
	}
	
	case EStateName::Stamina:
	{
		LocalTimerHandle = &StaminaTimerHandle;
		LocalTimerDel = FTimerDelegate::CreateUObject(this,  &UHealthStaminaComponent::RegenStamina);
		LocalTimerTime = 1.0;
		break;
	}
	
	default:
		break;
	}
	if (!LocalTimerHandle)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("HealthStaminaComponent, LocalTimerHandle = nullptr!")));
		return;
	}

	if (CurrentValue >= MaxValue)
	{
		GetWorld()->GetTimerManager().ClearTimer(*LocalTimerHandle);
		return;
	}

	if(!GetWorld()->GetTimerManager().TimerExists(*LocalTimerHandle))
		GetWorld()->GetTimerManager().SetTimer(*LocalTimerHandle, LocalTimerDel, LocalTimerTime, true);
}
//-----------------------------------------------------------------------------------------------------------
void UHealthStaminaComponent::WasteStaminaTimerManager(bool bStart)
{
	if (bStart && !GetWorld()->GetTimerManager().TimerExists(WasteStaminaTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(WasteStaminaTimerHandle, this, &UHealthStaminaComponent::WasteStamina, 0.2,  true);
		bStaminaTimerBlock = true;
	}
	else if (!bStart && GetWorld()->GetTimerManager().TimerExists(WasteStaminaTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(WasteStaminaTimerHandle);
		bStaminaTimerBlock = false;
	}
}
void UHealthStaminaComponent::WasteStamina()
{
	double* LocalStamina = StateMap.Find(EStateName::Stamina);
	if (!LocalStamina)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("HealthStaminaComponent, LocalStamina = nullptr!")));
		return;
	}

	*LocalStamina -= 1;
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));

	if (GetStateMapElem(EStateName::Stamina) <= 0.5)
	{
		WasteStaminaTimerManager(false);
		PlayerCharacter->StopSprint();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UHealthStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//-----------------------------------------------------------------------------------------------------------
void UHealthStaminaComponent::ChangeStateValue(EStateName StateName, double Value, bool bIncreaseState)
{
	double* CurrentValue = StateMap.Find(StateName);
	double* MaxValue = nullptr;

	switch (StateName)
	{
	case EStateName::Health:
		MaxValue = StateMap.Find(EStateName::HealthMax);
		break;

	case EStateName::Stamina:
		MaxValue = StateMap.Find(EStateName::StaminaMax); 
		break;

	default:
		break;
	}

	if (CurrentValue && MaxValue)
	{
		if (bIncreaseState)
			*CurrentValue = FMath::Clamp(*CurrentValue + Value, 0.0, *MaxValue);
		else
			*CurrentValue = FMath::Clamp(*CurrentValue - Value, 0.0, *MaxValue);

		OnChangeState.Broadcast(StateName, *CurrentValue, *MaxValue);
	}
}
//-----------------------------------------------------------------------------------------------------------