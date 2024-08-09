// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/ActorComponents/Chest/ChestComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeChestComponent() {}

// Begin Cross Module References
FPS_API UClass* Z_Construct_UClass_UChestComponent();
FPS_API UClass* Z_Construct_UClass_UChestComponent_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStorageComponent();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UChestComponent
void UChestComponent::StaticRegisterNativesUChestComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UChestComponent);
UClass* Z_Construct_UClass_UChestComponent_NoRegister()
{
	return UChestComponent::StaticClass();
}
struct Z_Construct_UClass_UChestComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "ActorComponents/Chest/ChestComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ActorComponents/Chest/ChestComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UChestComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UChestComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UStorageComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UChestComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UChestComponent_Statics::ClassParams = {
	&UChestComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UChestComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UChestComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UChestComponent()
{
	if (!Z_Registration_Info_UClass_UChestComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UChestComponent.OuterSingleton, Z_Construct_UClass_UChestComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UChestComponent.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UChestComponent>()
{
	return UChestComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UChestComponent);
UChestComponent::~UChestComponent() {}
// End Class UChestComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Chest_ChestComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UChestComponent, UChestComponent::StaticClass, TEXT("UChestComponent"), &Z_Registration_Info_UClass_UChestComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UChestComponent), 1924613158U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Chest_ChestComponent_h_2168307637(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Chest_ChestComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Chest_ChestComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
