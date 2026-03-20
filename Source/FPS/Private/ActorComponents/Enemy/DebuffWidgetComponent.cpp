#include "ActorComponents/Enemy/DebuffWidgetComponent.h"
#include "Enemies/EnemyMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Widgets/Enemy/EnemyStateWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UDebuffWidgetComponent::InitWidgetComponent(UStateMasterComponent* stateComponent)
{
	UEnemyStateWidget* widget = Cast<UEnemyStateWidget>(GetWidget());
	CHECK_PTR(widget)

	widget->InitParams(stateComponent);
}
