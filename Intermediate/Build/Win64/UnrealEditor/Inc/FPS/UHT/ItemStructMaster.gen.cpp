// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Structures/ItemStructMaster.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItemStructMaster() {}

// Begin Cross Module References
FPS_API UScriptStruct* Z_Construct_UScriptStruct_FItemStructMaster();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin ScriptStruct FItemStructMaster
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ItemStructMaster;
class UScriptStruct* FItemStructMaster::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ItemStructMaster.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ItemStructMaster.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FItemStructMaster, (UObject*)Z_Construct_UPackage__Script_FPS(), TEXT("ItemStructMaster"));
	}
	return Z_Registration_Info_UScriptStruct_ItemStructMaster.OuterSingleton;
}
template<> FPS_API UScriptStruct* StaticStruct<FItemStructMaster>()
{
	return FItemStructMaster::StaticStruct();
}
struct Z_Construct_UScriptStruct_FItemStructMaster_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/Structures/ItemStructMaster.h" },
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemStructMaster>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
	nullptr,
	&NewStructOps,
	"ItemStructMaster",
	nullptr,
	0,
	sizeof(FItemStructMaster),
	alignof(FItemStructMaster),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemStructMaster_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FItemStructMaster_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FItemStructMaster()
{
	if (!Z_Registration_Info_UScriptStruct_ItemStructMaster.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ItemStructMaster.InnerSingleton, Z_Construct_UScriptStruct_FItemStructMaster_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ItemStructMaster.InnerSingleton;
}
// End ScriptStruct FItemStructMaster

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FItemStructMaster::StaticStruct, Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewStructOps, TEXT("ItemStructMaster"), &Z_Registration_Info_UScriptStruct_ItemStructMaster, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FItemStructMaster), 1403928055U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_3590999311(TEXT("/Script/FPS"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
