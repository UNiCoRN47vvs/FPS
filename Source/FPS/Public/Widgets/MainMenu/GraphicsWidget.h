
#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
class UGameUserSettings;
class UFramePerSecondWidget;
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EGraphicsSettings : uint8
{
	ViewDistance UMETA(DisplayName = "View Distance"),
	AntiAliasing UMETA(DisplayName = "Anti Aliasing"),
	PostProcessing UMETA(DisplayName = "Post Processing"),
	Shadows UMETA(DisplayName = "Shadows"),
	GlobalIllumination UMETA(DisplayName = "Global Illumination"),
	Reflections UMETA(DisplayName = "Reflections"),
	Textures UMETA(DisplayName = "Textures"),
	Effects UMETA(DisplayName = "Effects"),
	Foliage UMETA(DisplayName = "Foliage"),
	Shading UMETA(DisplayName = "Shading"),
	VSync UMETA(DisplayName = "VSync"),
	FPSLimit UMETA(DisplayName = "FPSLimit"),
	FrameRate UMETA(DisplayName = "Frame Rate"),
	SoundMaster UMETA(DisplayName = "Sound Master"),
	SoundEffect UMETA(DisplayName = "Sound Effect"),
	SoundMusic UMETA(DisplayName = "Sound Music"),
	AntiAliasingMethod UMETA(DisplayName = "Anti Aliasing Method"),
	MSAACount UMETA(DisplayName = "MSAA Count")
	
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UGraphicsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTittleText(int32 Index);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graphics Widget") EGraphicsSettings GraphicsSettings;

	UPROPERTY(BlueprintReadWrite, Category = "Graphics Widget", meta = (BindWidget)) UButton* LeftButton;
	UPROPERTY(BlueprintReadWrite, Category = "Graphics Widget", meta = (BindWidget)) UButton* RightButton;
	UPROPERTY(BlueprintReadWrite, Category = "Graphics Widget", meta = (BindWidget)) UTextBlock* TittleTB;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void UseLeftButton();
	UFUNCTION() void UseRightButton();
	void ChooseSettings(bool bIsRight);

	UPROPERTY() UGameUserSettings* UserSettings;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") FText Low;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") FText Medium;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") FText High;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") FText Epic;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") FText Cinematic;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graphics Widget") TMap<int32, FText> FPS;
private:
	void SetSoundVolume(bool bIsRight, float& volumeParam);
	TMap<int32, FString> AntiAliasingMap;
	TMap<int32, FString> MSAAMap;
};
//-----------------------------------------------------------------------------------------------------------