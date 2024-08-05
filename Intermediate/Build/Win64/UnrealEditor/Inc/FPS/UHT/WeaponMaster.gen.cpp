// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Items/Weapons/WeaponMaster.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWeaponMaster() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
FPS_API UClass* Z_Construct_UClass_AItemMaster();
FPS_API UClass* Z_Construct_UClass_AWeaponMaster();
FPS_API UClass* Z_Construct_UClass_AWeaponMaster_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class AWeaponMaster
void AWeaponMaster::StaticRegisterNativesAWeaponMaster()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWeaponMaster);
UClass* Z_Construct_UClass_AWeaponMaster_NoRegister()
{
	return AWeaponMaster::StaticClass();
}
struct Z_Construct_UClass_AWeaponMaster_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Items/Weapons/WeaponMaster.h" },
		{ "ModuleRelativePath", "Public/Items/Weapons/WeaponMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshComponent_MetaData[] = {
		{ "Category", "Weapon Master" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Items/Weapons/WeaponMaster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMeshComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWeaponMaster>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWeaponMaster_Statics::NewProp_SkeletalMeshComponent = { "SkeletalMeshComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponMaster, SkeletalMeshComponent), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshComponent_MetaData), NewProp_SkeletalMeshComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWeaponMaster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponMaster_Statics::NewProp_SkeletalMeshComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponMaster_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AWeaponMaster_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AItemMaster,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponMaster_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AWeaponMaster_Statics::ClassParams = {
	&AWeaponMaster::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AWeaponMaster_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponMaster_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponMaster_Statics::Class_MetaDataParams), Z_Construct_UClass_AWeaponMaster_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AWeaponMaster()
{
	if (!Z_Registration_Info_UClass_AWeaponMaster.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWeaponMaster.OuterSingleton, Z_Construct_UClass_AWeaponMaster_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AWeaponMaster.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<AWeaponMaster>()
{
	return AWeaponMaster::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AWeaponMaster);
AWeaponMaster::~AWeaponMaster() {}
// End Class AWeaponMaster

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AWeaponMaster, AWeaponMaster::StaticClass, TEXT("AWeaponMaster"), &Z_Registration_Info_UClass_AWeaponMaster, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWeaponMaster), 2584761726U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_3005021752(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
