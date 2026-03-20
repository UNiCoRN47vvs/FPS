#include "Widgets/MainMenu/GraphicsWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "Save/MasterSave.h"
#include "Sound/SoundClass.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "FirstPerson/FPSGameInstance.h"
#include "MainMenu/MainMenuController.h"
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	int32 sountValueText = 0;
	int32 mapInt = 0;
	UFPSGameInstance* gameInstance = nullptr;
	UMasterSave* masterSave = nullptr;
	
	UserSettings = UGameUserSettings::GetGameUserSettings();
	CHECK_PTR(UserSettings)

	LeftButton->OnClicked.AddDynamic(this, &UGraphicsWidget::UseLeftButton);
	RightButton->OnClicked.AddDynamic(this, &UGraphicsWidget::UseRightButton);

	switch (GraphicsSettings)
	{
	case EGraphicsSettings::ViewDistance:
		SetTittleText(UserSettings->GetViewDistanceQuality());
		break;

	case EGraphicsSettings::AntiAliasing:
		SetTittleText(UserSettings->GetAntiAliasingQuality());
		break;

	case EGraphicsSettings::PostProcessing:
		SetTittleText(UserSettings->GetPostProcessingQuality());
		break;

	case EGraphicsSettings::Shadows:
		SetTittleText(UserSettings->GetShadowQuality());
		break;

	case EGraphicsSettings::GlobalIllumination:
		SetTittleText(UserSettings->GetGlobalIlluminationQuality());
		break;

	case EGraphicsSettings::Reflections:
		SetTittleText(UserSettings->GetReflectionQuality());
		break;

	case EGraphicsSettings::Textures:
		SetTittleText(UserSettings->GetTextureQuality());
		break;

	case EGraphicsSettings::Effects:
		SetTittleText(UserSettings->GetVisualEffectQuality());
		break;

	case EGraphicsSettings::Foliage:
		SetTittleText(UserSettings->GetFoliageQuality());
		break;

	case EGraphicsSettings::Shading:
		SetTittleText(UserSettings->GetShadingQuality());
		break;

	case EGraphicsSettings::VSync:
		TittleTB->SetText(UserSettings->IsVSyncEnabled() ? FText::FromString(FString(TEXT("On"))) : FText::FromString(FString(TEXT("Off"))));
		break;

	case EGraphicsSettings::FPSLimit:
		TittleTB->SetText(FText::AsNumber(UserSettings->GetFrameRateLimit()));
		break;

	case EGraphicsSettings::FrameRate:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)
		
		masterSave->SettingsSave.bIsShowFPS ? TittleTB->SetText(FText::FromString(FString("On"))) : TittleTB->SetText(FText::FromString(FString("Off")));
		break;

	case EGraphicsSettings::SoundMaster:
		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundMaster)

		sountValueText = gameInstance->SoundMaster->Properties.Volume * 10;
		TittleTB->SetText(FText::AsNumber(sountValueText));
		break;

	case EGraphicsSettings::SoundEffect:
		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundEffect)

		sountValueText = gameInstance->SoundEffect->Properties.Volume * 10;
		TittleTB->SetText(FText::AsNumber(sountValueText));
		break;

	case EGraphicsSettings::SoundMusic:
		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundMusic)

		sountValueText = gameInstance->SoundMusic->Properties.Volume * 10;
		TittleTB->SetText(FText::AsNumber(sountValueText));
		break;

	case EGraphicsSettings::AntiAliasingMethod:
		AntiAliasingMap.Add(0, "None");
		AntiAliasingMap.Add(1, "FXAA");
		AntiAliasingMap.Add(2, "TAA");
		AntiAliasingMap.Add(3, "MSAA");
		AntiAliasingMap.Add(4, "TSR");

		mapInt = UKismetSystemLibrary::GetConsoleVariableIntValue(TEXT("r.AntiAliasingMethod"));
		
		if(AntiAliasingMap.Contains(mapInt))
			TittleTB->SetText(FText::FromString(*AntiAliasingMap.Find(mapInt)));

		break;
	case EGraphicsSettings::MSAACount:
		MSAAMap.Add(1, "OFF");
		MSAAMap.Add(2, "2x MSAA");
		MSAAMap.Add(4, "4x MSAA");
		MSAAMap.Add(8, "8x MSAA");
		
		mapInt = UKismetSystemLibrary::GetConsoleVariableIntValue(TEXT("r.MSAACount"));

		if(MSAAMap.Contains(mapInt))
			TittleTB->SetText(FText::FromString(*MSAAMap.Find(mapInt)));
		break;

	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::UseLeftButton()
{
	ChooseSettings(false);
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::UseRightButton()
{
	ChooseSettings(true);
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::ChooseSettings(bool bIsRight)
{
	int32 quality = -1;
	int32 mapInt = 0;
	UFPSGameInstance* gameInstance = nullptr;
	AMainMenuController* controllerMainMenu = nullptr;
	UMasterSave* masterSave = nullptr;

	if (!UserSettings)
	{
		UserSettings = UGameUserSettings::GetGameUserSettings();
		CHECK_PTR(UserSettings)
	}

	switch (GraphicsSettings)
	{
	case EGraphicsSettings::ViewDistance:
		bIsRight ? UserSettings->SetViewDistanceQuality(UserSettings->GetViewDistanceQuality() + 1 <= 4 ? UserSettings->GetViewDistanceQuality() + 1 : UserSettings->GetViewDistanceQuality())
					: UserSettings->SetViewDistanceQuality(UserSettings->GetViewDistanceQuality() - 1 >= 0 ? UserSettings->GetViewDistanceQuality() - 1 : UserSettings->GetViewDistanceQuality());

		quality = UserSettings->GetViewDistanceQuality();
		break;

	case EGraphicsSettings::AntiAliasing:
		bIsRight ? UserSettings->SetAntiAliasingQuality(UserSettings->GetAntiAliasingQuality() + 1 <= 4 ? UserSettings->GetAntiAliasingQuality() + 1 : UserSettings->GetAntiAliasingQuality())
					: UserSettings->SetAntiAliasingQuality(UserSettings->GetAntiAliasingQuality() - 1 >= 0 ? UserSettings->GetAntiAliasingQuality() - 1 : UserSettings->GetAntiAliasingQuality());

		quality = UserSettings->GetAntiAliasingQuality();
		break;

	case EGraphicsSettings::PostProcessing:
		bIsRight ? UserSettings->SetPostProcessingQuality(UserSettings->GetPostProcessingQuality() + 1 <= 4 ? UserSettings->GetPostProcessingQuality() + 1 : UserSettings->GetPostProcessingQuality())
					: UserSettings->SetPostProcessingQuality(UserSettings->GetPostProcessingQuality() - 1 >= 0 ? UserSettings->GetPostProcessingQuality() - 1 : UserSettings->GetPostProcessingQuality());
		
		quality = UserSettings->GetPostProcessingQuality();
		break;

	case EGraphicsSettings::Shadows:
		bIsRight ? UserSettings->SetShadowQuality(UserSettings->GetShadowQuality() + 1 <= 4 ? UserSettings->GetShadowQuality() + 1 : UserSettings->GetShadowQuality())
					: UserSettings->SetShadowQuality(UserSettings->GetShadowQuality() - 1 >= 0 ? UserSettings->GetShadowQuality() - 1 : UserSettings->GetShadowQuality());
		
		quality = UserSettings->GetShadowQuality();
		break;

	case EGraphicsSettings::GlobalIllumination:
		bIsRight ? UserSettings->SetGlobalIlluminationQuality(UserSettings->GetGlobalIlluminationQuality() + 1 <= 4 ? UserSettings->GetGlobalIlluminationQuality() + 1 : UserSettings->GetGlobalIlluminationQuality())
					: UserSettings->SetGlobalIlluminationQuality(UserSettings->GetGlobalIlluminationQuality() - 1 >= 0 ? UserSettings->GetGlobalIlluminationQuality() - 1 : UserSettings->GetGlobalIlluminationQuality());
		
		quality = UserSettings->GetGlobalIlluminationQuality();
		break;

	case EGraphicsSettings::Reflections:
		bIsRight ? UserSettings->SetReflectionQuality(UserSettings->GetReflectionQuality() + 1 <= 4 ? UserSettings->GetReflectionQuality() + 1 : UserSettings->GetReflectionQuality())
					: UserSettings->SetReflectionQuality(UserSettings->GetReflectionQuality() - 1 >= 0 ? UserSettings->GetReflectionQuality() - 1 : UserSettings->GetReflectionQuality());
		
		quality = UserSettings->GetReflectionQuality();
		break;

	case EGraphicsSettings::Textures:
		bIsRight ? UserSettings->SetTextureQuality(UserSettings->GetTextureQuality() + 1 <= 4 ? UserSettings->GetTextureQuality() + 1 : UserSettings->GetTextureQuality())
					: UserSettings->SetTextureQuality(UserSettings->GetTextureQuality() - 1 >= 0 ? UserSettings->GetTextureQuality() - 1 : UserSettings->GetTextureQuality());
		
		quality = UserSettings->GetTextureQuality();
		break;

	case EGraphicsSettings::Effects:
		bIsRight ? UserSettings->SetVisualEffectQuality(UserSettings->GetVisualEffectQuality() + 1 <= 4 ? UserSettings->GetVisualEffectQuality() + 1 : UserSettings->GetVisualEffectQuality())
					: UserSettings->SetVisualEffectQuality(UserSettings->GetVisualEffectQuality() - 1 >= 0 ? UserSettings->GetVisualEffectQuality() - 1 : UserSettings->GetVisualEffectQuality());
		
		quality = UserSettings->GetVisualEffectQuality();
		break;

	case EGraphicsSettings::Foliage:
		bIsRight ? UserSettings->SetFoliageQuality(UserSettings->GetFoliageQuality() + 1 <= 4 ? UserSettings->GetFoliageQuality() + 1 : UserSettings->GetFoliageQuality())
					: UserSettings->SetFoliageQuality(UserSettings->GetFoliageQuality() - 1 >= 0 ? UserSettings->GetFoliageQuality() - 1 : UserSettings->GetFoliageQuality());
		
		quality = UserSettings->GetFoliageQuality();
		break;

	case EGraphicsSettings::Shading:
		bIsRight ? UserSettings->SetShadingQuality(UserSettings->GetShadingQuality() + 1 <= 4 ? UserSettings->GetShadingQuality() + 1 : UserSettings->GetShadingQuality())
					: UserSettings->SetShadingQuality(UserSettings->GetShadingQuality() - 1 >= 0 ? UserSettings->GetShadingQuality() - 1 : UserSettings->GetShadingQuality());
		
		quality = UserSettings->GetShadingQuality();
		break;

	case EGraphicsSettings::VSync:
		bIsRight ? UserSettings->SetVSyncEnabled(true) : UserSettings->SetVSyncEnabled(false);

		TittleTB->SetText(UserSettings->IsVSyncEnabled() ? FText::FromString(FString(TEXT("On"))) : FText::FromString(FString(TEXT("Off"))));
		break;

	case EGraphicsSettings::FPSLimit:
		bIsRight ? UserSettings->GetFrameRateLimit() >= 240.0f ? UserSettings->SetFrameRateLimit(240.0f) : UserSettings->SetFrameRateLimit(UserSettings->GetFrameRateLimit() + 10.0f)
					: UserSettings->GetFrameRateLimit() <= 30.0f ? UserSettings->SetFrameRateLimit(30.0f) : UserSettings->SetFrameRateLimit(UserSettings->GetFrameRateLimit() - 10.0f);

		TittleTB->SetText(FText::AsNumber(UserSettings->GetFrameRateLimit()));
		break;

	case EGraphicsSettings::FrameRate:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		masterSave->SettingsSave.bIsShowFPS = bIsRight;

		bIsRight ? TittleTB->SetText(FText::FromString(FString("On"))) : TittleTB->SetText(FText::FromString(FString("Off")));

		UEventBus::OnShowFPS.ExecuteIfBound(bIsRight);

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);
		break;

	case EGraphicsSettings::SoundMaster:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundMaster)

		SetSoundVolume(bIsRight, gameInstance->SoundMaster->Properties.Volume);

		masterSave->SettingsSave.SoundMasterValue = gameInstance->SoundMaster->Properties.Volume;

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);

		break;																											 

	case EGraphicsSettings::SoundEffect:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundEffect)

		SetSoundVolume(bIsRight, gameInstance->SoundEffect->Properties.Volume);

		masterSave->SettingsSave.SoundEffectValue = gameInstance->SoundEffect->Properties.Volume;

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);

		break;

	case EGraphicsSettings::SoundMusic:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		gameInstance = GetGameInstance<UFPSGameInstance>();
		CHECK_PTR(gameInstance)
		CHECK_PTR(gameInstance->SoundMusic)
			
		SetSoundVolume(bIsRight, gameInstance->SoundMusic->Properties.Volume);

		masterSave->SettingsSave.SoundMusicValue = gameInstance->SoundMusic->Properties.Volume;

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);
		break;
	case EGraphicsSettings::AntiAliasingMethod:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		mapInt = UKismetSystemLibrary::GetConsoleVariableIntValue(TEXT("r.AntiAliasingMethod"));
		bIsRight ? mapInt >= 4 ? mapInt = 0 : ++mapInt 
					: mapInt <= 0 ? mapInt = 4 : --mapInt; //Что это?

		GEngine->Exec(GetWorld(), *(FString(TEXT("r.AntiAliasingMethod ")) + FString::FromInt(mapInt)));
		if (AntiAliasingMap.Contains(mapInt))
			TittleTB->SetText(FText::FromString(*AntiAliasingMap.Find(mapInt)));

		masterSave->SettingsSave.AntiAliasingMethod = mapInt;

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);
		break;
	case EGraphicsSettings::MSAACount:
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		CHECK_PTR(masterSave)

		mapInt = UKismetSystemLibrary::GetConsoleVariableIntValue(TEXT("r.MSAACount"));

		bIsRight ? mapInt >= 8 ? mapInt = 1 : mapInt *= 2 
					: mapInt <= 1 ? mapInt = 8 : mapInt /= 2; //Что это?

		GEngine->Exec(GetWorld(), *(FString(TEXT("r.MSAACount ")) + FString::FromInt(mapInt)));
		if(MSAAMap.Contains(mapInt))
			TittleTB->SetText(FText::FromString(*MSAAMap.Find(mapInt)));

		masterSave->SettingsSave.MSAACount = mapInt;

		UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);
		break;
	default:
		break;
	}

	SetTittleText(quality);
	UserSettings->ApplySettings(false);
	UserSettings->SaveConfig();
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::SetSoundVolume(bool bIsRight, float& volumeParam)
{
	int32 soundVolumeText = 0;
	float soundVolume = volumeParam;

	bIsRight ? soundVolume >= 1.0f ? soundVolume += 0.0f
		: soundVolume += 0.1f
		: soundVolume <= 0.1f ? soundVolume -= 0.0f
		: soundVolume -= 0.1f;

	volumeParam = soundVolume;
	soundVolumeText = soundVolume * 10;
	TittleTB->SetText(FText::AsNumber(soundVolumeText));
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsWidget::SetTittleText(int32 Index)
{
	switch (Index)
	{
	case 0 :
		TittleTB->SetText(Low);
		break;
	case 1 :
		TittleTB->SetText(Medium);
		break;
	case 2 :
		TittleTB->SetText(High);
		break;
	case 3 :
		TittleTB->SetText(Epic);
		break;
	case 4 :
		TittleTB->SetText(Cinematic);
		break;
		
	default:
		break;
	}
}
