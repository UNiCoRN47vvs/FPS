#include "Widgets/Weapons/AmmoWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "SubSystem/EventBus.h"
#include "Config/AudusMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetAmmoText(0, 0);

	UEventBus::OnUpdateAmmoWidget.BindUObject(this, &UAmmoWidget::SetAmmoText);
	UEventBus::OnActivateAudus.BindUObject(this, &UAmmoWidget::SetAudusInfo);

	TBFiringRate->SetVisibility(ESlateVisibility::Collapsed);
	AudusIcon->SetVisibility(ESlateVisibility::Collapsed);
}
//-----------------------------------------------------------------------------------------------------------
void UAmmoWidget::NativeDestruct()
{
	UEventBus::OnUpdateAmmoWidget.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
void UAmmoWidget::SetAmmoText(int32 currentAmmo, int32 maxAmmo)
{
	FText text = {};
	if (!TBAmmo)
		return;

	if (maxAmmo <= 0)
		return SetVisibility(ESlateVisibility::Collapsed);

	SetVisibility(ESlateVisibility::Visible);
	text = FText::FromString(FString::FromInt(currentAmmo) + "/" + FString::FromInt(maxAmmo));
	TBAmmo->SetText(text);
}
//-----------------------------------------------------------------------------------------------------------
void UAmmoWidget::SetAudusInfo(UItemMasterDA* itemDA)
{
	UAudusMasterDA* audusDA = Cast<UAudusMasterDA>(itemDA);
	if (!audusDA)
	{
		TBFiringRate->SetVisibility(ESlateVisibility::Collapsed);
		AudusIcon->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	const UEnum* enumPtr = StaticEnum<EFiringMode>();
	TBFiringRate->SetText(enumPtr ? enumPtr->GetDisplayNameTextByValue(static_cast<int64>(audusDA->FiringMode)) : FText::FromString("Unknown"));

	TBFiringRate->SetVisibility(ESlateVisibility::Visible);
	AudusIcon->SetVisibility(ESlateVisibility::Visible);

	UGameplayStatics::PlaySound2D(this, AudusSound);
	AudusIcon->SetBrushFromSoftTexture(audusDA->ItemIcon);	
}
//-----------------------------------------------------------------------------------------------------------