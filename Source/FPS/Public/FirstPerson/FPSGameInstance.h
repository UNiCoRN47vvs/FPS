#pragma once

#include "FPS/FPS.h"
#include "Engine/GameInstance.h"
#include "FPS/FPSCharacter.h"
#include "FPSGameInstance.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInputMappingContext;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFPSGameInstance();
	const FString& GetSaveName();
	TMap<FName, bool>& GetSaveInfoMap();

	void SetSaveName(const FString& name);

	static TDelegate<UInputMappingContext* ()> OnGetInputMapingContext;

	UPROPERTY(BlueprintReadOnly, Category = "FPS_G_I") bool bIsNewGame;
	UPROPERTY(Config) bool bShowFPS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_I") UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G_I") USoundClass* SoundMaster;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G_I") USoundClass* SoundEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G_I") USoundClass* SoundMusic;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "G_I") bool bIsDebug;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "G_I") FString DebugSaveName;
protected:
	virtual void Init() override;

	TMap<FName, bool> TempMap;
	UPROPERTY() FString SaveName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_I") TSoftObjectPtr<UDataTable> StatDataDT;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_I") TSoftObjectPtr<UDataTable> StatGradeDataDT;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_I") TSoftObjectPtr<UDataTable> CraftCreationDT;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_I") TSoftObjectPtr<UDataTable> CraftModificationDT;
private:
	template<typename StructClass> void InitStat(TArray<StructClass>& statArray, TSoftObjectPtr<UDataTable> dataTable);

	void CraftCreationSort();
	void CraftModificationSort();
};
//-----------------------------------------------------------------------------------------------------------

