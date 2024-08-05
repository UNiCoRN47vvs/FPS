// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Items/Supplies/SuppliesMaster.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSuppliesMaster() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
FPS_API UClass* Z_Construct_UClass_AItemMaster();
FPS_API UClass* Z_Construct_UClass_ASuppliesMaster();
FPS_API UClass* Z_Construct_UClass_ASuppliesMaster_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class ASuppliesMaster
void ASuppliesMaster::StaticRegisterNativesASuppliesMaster()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASuppliesMaster);
UClass* Z_Construct_UClass_ASuppliesMaster_NoRegister()
{
	return ASuppliesMaster::StaticClass();
}
struct Z_Construct_UClass_ASuppliesMaster_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Items/Supplies/SuppliesMaster.h" },
		{ "ModuleRelativePath", "Public/Items/Supplies/SuppliesMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshComponent_MetaData[] = {
		{ "Category", "Weapon Master" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Items/Supplies/SuppliesMaster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StaticMeshComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASuppliesMaster>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuppliesMaster_Statics::NewProp_StaticMeshComponent = { "StaticMeshComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASuppliesMaster, StaticMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaticMeshComponent_MetaData), NewProp_StaticMeshComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASuppliesMaster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuppliesMaster_Statics::NewProp_StaticMeshComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASuppliesMaster_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASuppliesMaster_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AItemMaster,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASuppliesMaster_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASuppliesMaster_Statics::ClassParams = {
	&ASuppliesMaster::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASuppliesMaster_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASuppliesMaster_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASuppliesMaster_Statics::Class_MetaDataParams), Z_Construct_UClass_ASuppliesMaster_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASuppliesMaster()
{
	if (!Z_Registration_Info_UClass_ASuppliesMaster.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASuppliesMaster.OuterSingleton, Z_Construct_UClass_ASuppliesMaster_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASuppliesMaster.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<ASuppliesMaster>()
{
	return ASuppliesMaster::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASuppliesMaster);
ASuppliesMaster::~ASuppliesMaster() {}
// End Class ASuppliesMaster

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Supplies_SuppliesMaster_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASuppliesMaster, ASuppliesMaster::StaticClass, TEXT("ASuppliesMaster"), &Z_Registration_Info_UClass_ASuppliesMaster, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASuppliesMaster), 3277060038U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Supplies_SuppliesMaster_h_1925665263(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Supplies_SuppliesMaster_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Supplies_SuppliesMaster_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
