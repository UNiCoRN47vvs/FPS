#include "Widgets/MainMenu/DeleteSaveGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FirstPerson/FPSGameInstance.h"
#include "MainMenu/MainMenuController.h"
#include "Widgets/MainMenu/MainMenuWidget.h"
#include "Widgets/MainMenu/SignboardWidget.h"
#include "Widgets/MainMenu/LoadGameWidget.h"
#include "Save/MasterSave.h"
#include "MainMenu/MainMenuController.h"
#include "Widgets/MainMenu/MainMenuWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UDeleteSaveGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SignboardWidget->ButtonSignboard->OnClicked.AddDynamic(this, &UDeleteSaveGameWidget::LoadGame);
	DeleteButton->OnClicked.AddDynamic(this, &UDeleteSaveGameWidget::DeleteSave);
}
//-----------------------------------------------------------------------------------------------------------
void UDeleteSaveGameWidget::LoadGame()
{
	AMainMenuController* controller = Cast<AMainMenuController>(GetOwningPlayer());
	UFPSGameInstance* gameInstance = Cast<UFPSGameInstance>(GetGameInstance());
	CHECK_PTR(controller)
	CHECK_PTR(gameInstance)

	controller->CreateLoadScreen();
	gameInstance->SetSaveName(SignboardWidget->TextTB->GetText().ToString());
	gameInstance->bIsNewGame = false;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, controller->MainMenuWidget->MainWorld);
}
//-----------------------------------------------------------------------------------------------------------
void UDeleteSaveGameWidget::DeleteSave()
{
	FString saveName = SignboardWidget->TextTB->GetText().ToString();
	UMasterSave* masterSave = nullptr;
	
	if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
	{
		ALARM_LOG
		return;
	}
		
	masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
	CHECK_PTR(masterSave)
	
	if (!masterSave->MasterSave.Contains(saveName))
	{
		ALARM_LOG
		return;
	}

	//TODO : ѕредупреждение об удалении сохранени€

	masterSave->MasterSave.Remove(saveName);
	UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);
	this->RemoveFromParent();

	//?????
	if (!masterSave->MasterSave.IsEmpty())
		return;

	AMainMenuController* controller = GetOwningPlayer<AMainMenuController>();
	CHECK_PTR(controller)

	controller->MainMenuWidget->UseButton(controller->MainMenuWidget->LoadGameVB, controller->MainMenuWidget->MainVB);
}
