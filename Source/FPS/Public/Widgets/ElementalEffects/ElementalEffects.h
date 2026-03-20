#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "ElementalEffects.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UHorizontalBox;
class UStateMasterComponent;
class UElementalEffectSlot;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UElementalEffects : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitParams(UStateMasterComponent* stateMasterComponent);
	UPROPERTY(BlueprintReadOnly, Category = "E_E", meta = (BindWidget)) UHorizontalBox* ElementalSlotsSpaceHB;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_E") TSubclassOf<UElementalEffectSlot> WBPSlot;
protected:
	virtual void NativeConstruct() override;
	UElementalEffectSlot* CreateElementalSlot(int32 stackEffect, UTexture2D* icon);
	UFUNCTION() void TriggerPhysicalIcon(const bool bIsCreate, UTexture2D* icon);
	UFUNCTION() void TriggerFireIcon(const bool bIsCreate, const int32 index, UTexture2D* icon);
	UFUNCTION() void TriggerColdIcon(const bool bIsCreate, const int32 stackEffect, UTexture2D* icon);
	UFUNCTION() void TriggerPoisonIcon(const bool bIsCreate, const int32 stackEffect, UTexture2D* icon);

	UPROPERTY() UStateMasterComponent* StateComponent;
	TWeakObjectPtr<UElementalEffectSlot> PhysicalSlot;
	TWeakObjectPtr<UElementalEffectSlot> ColdSlot;
	TWeakObjectPtr<UElementalEffectSlot> PoisonSlot;
	TArray<TWeakObjectPtr<UElementalEffectSlot>> FireArray;
	FTimerHandle PhysicalTimer;
};
//-----------------------------------------------------------------------------------------------------------