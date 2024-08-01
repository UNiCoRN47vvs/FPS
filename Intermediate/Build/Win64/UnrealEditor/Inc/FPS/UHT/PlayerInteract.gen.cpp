// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Interfaces/PlayerInteract.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerInteract() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FPS_API UClass* Z_Construct_UClass_UPlayerInteract();
FPS_API UClass* Z_Construct_UClass_UPlayerInteract_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Interface UPlayerInteract
void UPlayerInteract::StaticRegisterNativesUPlayerInteract()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPlayerInteract);
UClass* Z_Construct_UClass_UPlayerInteract_NoRegister()
{
	return UPlayerInteract::StaticClass();
}
struct Z_Construct_UClass_UPlayerInteract_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/PlayerInteract.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IPlayerInteract>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UPlayerInteract_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPlayerInteract_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPlayerInteract_Statics::ClassParams = {
	&UPlayerInteract::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPlayerInteract_Statics::Class_MetaDataParams), Z_Construct_UClass_UPlayerInteract_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPlayerInteract()
{
	if (!Z_Registration_Info_UClass_UPlayerInteract.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPlayerInteract.OuterSingleton, Z_Construct_UClass_UPlayerInteract_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPlayerInteract.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UPlayerInteract>()
{
	return UPlayerInteract::StaticClass();
}
UPlayerInteract::UPlayerInteract(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPlayerInteract);
UPlayerInteract::~UPlayerInteract() {}
// End Interface UPlayerInteract

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPlayerInteract, UPlayerInteract::StaticClass, TEXT("UPlayerInteract"), &Z_Registration_Info_UClass_UPlayerInteract, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPlayerInteract), 2036397871U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_993895574(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
