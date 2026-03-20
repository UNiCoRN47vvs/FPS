#include "Widgets/Craft/CraftWidget.h"
#include "Components/Button.h"
#include "ActorComponents/Craft/CraftComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UCraftWidget::InitStorageWidget(UStorageComponent* StorageComponent)
{
	Super::InitStorageWidget(StorageComponent);

	CraftButton->OnClicked.AddDynamic(this, &UCraftWidget::ClickCraftButton);
}
//-----------------------------------------------------------------------------------------------------------
void UCraftWidget::ClickCraftButton()
{
	UCraftComponent* craftComponent = Cast<UCraftComponent>(StorageComp);
	CHECK_PTR(craftComponent)

	craftComponent->Craft(this);
}
//-----------------------------------------------------------------------------------------------------------
void UCraftWidget::CraftEvent(bool bIsSuccess)
{
	if (bIsSuccess)
		PlayAnimation(SuccessCraftAnimation);
	else
		PlayAnimation(FailCraftAnimation);
}
