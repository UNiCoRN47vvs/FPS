// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Interfaces/StorageInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStorageInterface() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FPS_API UClass* Z_Construct_UClass_UStorageInterface();
FPS_API UClass* Z_Construct_UClass_UStorageInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Interface UStorageInterface
void UStorageInterface::StaticRegisterNativesUStorageInterface()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStorageInterface);
UClass* Z_Construct_UClass_UStorageInterface_NoRegister()
{
	return UStorageInterface::StaticClass();
}
struct Z_Construct_UClass_UStorageInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/StorageInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IStorageInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UStorageInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStorageInterface_Statics::ClassParams = {
	&UStorageInterface::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UStorageInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStorageInterface()
{
	if (!Z_Registration_Info_UClass_UStorageInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStorageInterface.OuterSingleton, Z_Construct_UClass_UStorageInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStorageInterface.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UStorageInterface>()
{
	return UStorageInterface::StaticClass();
}
UStorageInterface::UStorageInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStorageInterface);
UStorageInterface::~UStorageInterface() {}
// End Interface UStorageInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_StorageInterface_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStorageInterface, UStorageInterface::StaticClass, TEXT("UStorageInterface"), &Z_Registration_Info_UClass_UStorageInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStorageInterface), 1333442267U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_StorageInterface_h_1248455698(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_StorageInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_StorageInterface_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
