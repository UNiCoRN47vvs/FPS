#include "Widgets/PopUp/PopUpMasterWidget.h"
#include "Animation/WidgetAnimationEvents.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
//-----------------------------------------------------------------------------------------------------------
void UPopUpMasterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimationForward(PopUpAnimation);
	FWidgetAnimationDynamicEvent delegate = {};
	delegate.BindUFunction(this, FName("RemoveFromParent"));
	
	BindToAnimationFinished(PopUpAnimation, delegate);
}
//-----------------------------------------------------------------------------------------------------------
void UPopUpMasterWidget::InitPopUp(const FText& name, const int32 currentGoal, TSoftObjectPtr<UTexture2D> image)
{
	CurrentGoalTB->SetText(FText::AsNumber(currentGoal));
	NameTB->SetText(name);

	Image->SetBrushFromSoftTexture(image);
}
//-----------------------------------------------------------------------------------------------------------