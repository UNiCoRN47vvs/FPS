// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Interfaces/ItemInteract.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItemInteract() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FPS_API UClass* Z_Construct_UClass_UItemInteract();
FPS_API UClass* Z_Construct_UClass_UItemInteract_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Interface UItemInteract
void UItemInteract::StaticRegisterNativesUItemInteract()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UItemInteract);
UClass* Z_Construct_UClass_UItemInteract_NoRegister()
{
	return UItemInteract::StaticClass();
}
struct Z_Construct_UClass_UItemInteract_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/ItemInteract.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IItemInteract>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UItemInteract_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UItemInteract_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UItemInteract_Statics::ClassParams = {
	&UItemInteract::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UItemInteract_Statics::Class_MetaDataParams), Z_Construct_UClass_UItemInteract_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UItemInteract()
{
	if (!Z_Registration_Info_UClass_UItemInteract.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UItemInteract.OuterSingleton, Z_Construct_UClass_UItemInteract_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UItemInteract.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UItemInteract>()
{
	return UItemInteract::StaticClass();
}
UItemInteract::UItemInteract(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UItemInteract);
UItemInteract::~UItemInteract() {}
// End Interface UItemInteract

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UItemInteract, UItemInteract::StaticClass, TEXT("UItemInteract"), &Z_Registration_Info_UClass_UItemInteract, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UItemInteract), 3650581592U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_2369791956(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
