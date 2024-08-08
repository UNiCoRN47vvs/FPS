// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Interfaces/InventorySlot.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInventorySlot() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FPS_API UClass* Z_Construct_UClass_UInventorySlot();
FPS_API UClass* Z_Construct_UClass_UInventorySlot_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Interface UInventorySlot
void UInventorySlot::StaticRegisterNativesUInventorySlot()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInventorySlot);
UClass* Z_Construct_UClass_UInventorySlot_NoRegister()
{
	return UInventorySlot::StaticClass();
}
struct Z_Construct_UClass_UInventorySlot_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/InventorySlot.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IInventorySlot>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UInventorySlot_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlot_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventorySlot_Statics::ClassParams = {
	&UInventorySlot::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlot_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventorySlot_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventorySlot()
{
	if (!Z_Registration_Info_UClass_UInventorySlot.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventorySlot.OuterSingleton, Z_Construct_UClass_UInventorySlot_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventorySlot.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UInventorySlot>()
{
	return UInventorySlot::StaticClass();
}
UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventorySlot);
UInventorySlot::~UInventorySlot() {}
// End Interface UInventorySlot

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_InventorySlot_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventorySlot, UInventorySlot::StaticClass, TEXT("UInventorySlot"), &Z_Registration_Info_UClass_UInventorySlot, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventorySlot), 91359442U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_InventorySlot_h_610070789(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_InventorySlot_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_InventorySlot_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
