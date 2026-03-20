#include "Widgets/MainMenu/MainMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Animation/WidgetAnimation.h"
#include "FirstPerson/FPSGameInstance.h"
#include "MainMenu/MainMenuController.h"
#include "Widgets/MainMenu/SignboardWidget.h"
#include "Widgets/MainMenu/CreateNewGameWidget.h"
#include "Widgets/MainMenu/LoadGameWidget.h"
#include "Widgets/MainMenu/GraphicsBoxWidget.h"
#include "Widgets/MainMenu/SoundMenuWidget.h"
#include "Widgets/MainMenu/ControlSettingsWidget.h"
#include "Save/MasterSave.h"
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameVB->SetVisibility(ESlateVisibility::Collapsed);
	LoadGameVB->SetVisibility(ESlateVisibility::Collapsed);
	SettingsVB->SetVisibility(ESlateVisibility::Collapsed);
	
	NewGameSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseNewGameButton);
	LoadGameSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseLoadGameButton);
	SettingsSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseSettingsButton);
	GraphicsSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseGraphicsButton);
	SoundSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseSoundButton);
	ControlSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseControlButton);
	SettingsBackSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseSettingsBackButton);
	ExitSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseExitButton);

	MainMenuController = Cast<AMainMenuController>(GetOwningPlayer());
	CHECK_PTR(MainMenuController)
	CHECK_PTR(MainMenuController->LoadScreenWidget)
	MainMenuController->LoadScreenWidget->RemoveFromParent();
	MainMenuController->LoadScreenWidget = nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::UseButton(UVerticalBox* currentVerticalBox, UVerticalBox* futureVerticalBox)
{
	CHECK_PTR(currentVerticalBox)
	CHECK_PTR(futureVerticalBox)

	ShowHideVerticalBox(currentVerticalBox, false);

	currentVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	ShowHideVerticalBox(futureVerticalBox, true);
	futureVerticalBox->SetVisibility(ESlateVisibility::Visible);
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::ShowHideVerticalBox(UVerticalBox* VerticalBox, bool bIsShow)
{
	UMasterMenuWidget* signboardWidget = nullptr;
	for (UWidget* item : VerticalBox->GetAllChildren())
	{
		if (!item)
			continue;

		signboardWidget = Cast<UMasterMenuWidget>(item);
		if (!signboardWidget)
		{
			ALARM_LOG
			continue;
		}

		signboardWidget->InitSignboardWidget(bIsShow);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::UseNewGameButton()
{
	if (NewGameVB->GetAllChildren().Num() <= 0)
	{
		CreateNewGameMenu = CreateWidget<UCreateNewGameWidget>(this, NewGameWClass);
		CHECK_PTR(CreateNewGameMenu)
		NewGameVB->AddChild(CreateNewGameMenu);

		CreateNewGameMenu->EnterSignboardWidget->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseNewGameEnterButton);
		CreateNewGameMenu->BackSignboardWidget->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseNewGameBackButton);
	}


	UseButton(MainVB, NewGameVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseNewGameEnterButton()
{
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
		MasterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));	
	else
		MasterSave = Cast<UMasterSave>(UGameplayStatics::CreateSaveGameObject(UMasterSave::StaticClass()));
	
	CHECK_PTR(MasterSave)

	if (CreateNewGameMenu->GetGameName().IsEmpty() || MasterSave->MasterSave.Contains(CreateNewGameMenu->GetGameName()))
	{
		CreateNewGameMenu->PlayAnimation(CreateNewGameMenu->ErrorAnimation);
		return;
	}

	MasterSave->MasterSave.Add(CreateNewGameMenu->GetGameName(), FSaveStruct{});
	UGameplayStatics::SaveGameToSlot(MasterSave, FString(TEXT("MasterSave")), 0);
	if (!MainMenuController)
	{
		MainMenuController = Cast<AMainMenuController>(GetOwningPlayer());
		CHECK_PTR(MainMenuController)
	}

	MainMenuController->CreateLoadScreen();
	//TODO : Открытие уровня

	UFPSGameInstance* gameInstance = GetGameInstance<UFPSGameInstance>();
	if (!gameInstance || !MainWorld)
	{
		ALARM_LOG
		MainMenuController->LoadScreenWidget->RemoveFromParent();
		MainMenuController->LoadScreenWidget = nullptr;
		UseNewGameBackButton();
	}

	gameInstance->SetSaveName(CreateNewGameMenu->GetGameName());
	gameInstance->bIsNewGame = true;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainWorld);
}
//***********************************************************************************************************
void UMainMenuWidget::UseNewGameBackButton()
{
	UseButton(NewGameVB, MainVB);
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::UseLoadGameButton()
{
	if (LoadGameVB->GetAllChildren().Num() <= 0)
	{
		LoadGameWidget = CreateWidget<ULoadGameWidget>(this, LoadGameWClass);
		CHECK_PTR(LoadGameWidget)
		LoadGameVB->AddChild(LoadGameWidget);

		LoadGameWidget->BackSignboardWidget->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseLoadGameBackButton);
	}

	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
		MasterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

	CHECK_PTR(MasterSave)
	
	if (MasterSave->MasterSave.IsEmpty())
		return;
	CHECK_PTR(LoadGameWidget)

	LoadGameWidget->InitLoadGameWidget(MasterSave);
	UseButton(MainVB, LoadGameVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseLoadGameBackButton()
{
	CHECK_PTR(LoadGameWidget)

	UseButton(LoadGameVB, MainVB);
	LoadGameWidget->ClearLoadGameWidget();
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::UseSettingsButton()
{
	UseButton(MainVB, SettingsVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseGraphicsButton()
{
	if (GraphicsVB->GetAllChildren().Num() <= 0)
	{
		GraphicsBox = CreateWidget<UGraphicsBoxWidget>(this, GraphicsClass);
		CHECK_PTR(GraphicsBox)
		GraphicsVB->AddChild(GraphicsBox);

		GraphicsBox->BackSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseGraphicsBackButton);
	}

	UseButton(SettingsVB, GraphicsVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseGraphicsBackButton()
{
	UseButton(GraphicsVB, SettingsVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseSoundButton()
{
	if (SoundVB->GetAllChildren().Num() <= 0)
	{
		SoundBox = CreateWidget<USoundMenuWidget>(this, SoundClass);
		CHECK_PTR(SoundBox)
		SoundVB->AddChild(SoundBox);

		SoundBox->BackSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseSoundBackButton);
	}

	UseButton(SettingsVB, SoundVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseSoundBackButton()
{
	UseButton(SoundVB, SettingsVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseControlButton()
{
	if (ControlVB->GetAllChildren().Num() <= 0)
	{
		ControlBox = CreateWidget<UControlSettingsWidget>(this, ControlClass);
		CHECK_PTR(ControlBox)
		ControlVB->AddChild(ControlBox);

		ControlBox->BackSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UMainMenuWidget::UseControlBackButton);
	}

	ControlBox->InitControlWidget();
	UseButton(SettingsVB, ControlVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseControlBackButton()
{
	UseButton(ControlVB, SettingsVB);
}
//***********************************************************************************************************
void UMainMenuWidget::UseSettingsBackButton()
{
	UseButton(SettingsVB, MainVB);
}
//-----------------------------------------------------------------------------------------------------------
void UMainMenuWidget::UseExitButton()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

