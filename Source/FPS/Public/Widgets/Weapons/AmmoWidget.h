#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetAmmoText(int32 currentAmmo, int32 maxAmmo);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo Widget", meta = (BindWidget)) UTextBlock* TBAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo Widget", meta = (BindWidget)) UTextBlock* TBFiringRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo Widget", meta = (BindWidget)) UImage* AudusIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo Widget") USoundWave* AudusSound;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetAudusInfo(UItemMasterDA* itemDA);
};
//-----------------------------------------------------------------------------------------------------------