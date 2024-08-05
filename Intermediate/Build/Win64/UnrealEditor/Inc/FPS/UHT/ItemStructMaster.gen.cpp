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
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemName_MetaData[] = {
		{ "Category", "Item Struct Master" },
		{ "ModuleRelativePath", "Public/Structures/ItemStructMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemDesc_MetaData[] = {
		{ "Category", "Item Struct Master" },
		{ "ModuleRelativePath", "Public/Structures/ItemStructMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemIcon_MetaData[] = {
		{ "Category", "Item Struct Master" },
		{ "ModuleRelativePath", "Public/Structures/ItemStructMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemSkeletalMesh_MetaData[] = {
		{ "Category", "Item Struct Master" },
		{ "ModuleRelativePath", "Public/Structures/ItemStructMaster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_ItemDesc;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ItemIcon;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ItemSkeletalMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemStructMaster>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemName = { "ItemName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemStructMaster, ItemName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemName_MetaData), NewProp_ItemName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemDesc = { "ItemDesc", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemStructMaster, ItemDesc), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemDesc_MetaData), NewProp_ItemDesc_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemIcon = { "ItemIcon", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemStructMaster, ItemIcon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemIcon_MetaData), NewProp_ItemIcon_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemSkeletalMesh = { "ItemSkeletalMesh", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemStructMaster, ItemSkeletalMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemSkeletalMesh_MetaData), NewProp_ItemSkeletalMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FItemStructMaster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemDesc,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemIcon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemSkeletalMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemStructMaster_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemStructMaster_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
	nullptr,
	&NewStructOps,
	"ItemStructMaster",
	Z_Construct_UScriptStruct_FItemStructMaster_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemStructMaster_Statics::PropPointers),
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
		{ FItemStructMaster::StaticStruct, Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewStructOps, TEXT("ItemStructMaster"), &Z_Registration_Info_UScriptStruct_ItemStructMaster, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FItemStructMaster), 1162395408U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_3726179594(TEXT("/Script/FPS"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Structures_ItemStructMaster_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
