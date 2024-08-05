// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Items/ItemMaster.h"
#include "Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItemMaster() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
FPS_API UClass* Z_Construct_UClass_AItemMaster();
FPS_API UClass* Z_Construct_UClass_AItemMaster_NoRegister();
FPS_API UClass* Z_Construct_UClass_UItemInteract_NoRegister();
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
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemName_MetaData[] = {
		{ "Category", "Item Struct" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemDesc_MetaData[] = {
		{ "Category", "Item Struct" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemIcon_MetaData[] = {
		{ "Category", "Item Struct" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_ItemDesc;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ItemIcon;
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
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FItemStructMaster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemDesc,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewProp_ItemIcon,
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
	EStructFlags(0x00000001),
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

// Begin Class AItemMaster Function OnOverlapBegin
struct Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics
{
	struct ItemMaster_eventOnOverlapBegin_Parms
	{
		UPrimitiveComponent* OverlappedComp;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapBegin_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComp_MetaData), NewProp_OverlappedComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapBegin_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapBegin_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapBegin_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit(void* Obj)
{
	((ItemMaster_eventOnOverlapBegin_Parms*)Obj)->bFromSweep = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ItemMaster_eventOnOverlapBegin_Parms), &Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapBegin_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // 4100991306
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OverlappedComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AItemMaster, nullptr, "OnOverlapBegin", nullptr, nullptr, Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::PropPointers), sizeof(Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::ItemMaster_eventOnOverlapBegin_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::Function_MetaDataParams), Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::ItemMaster_eventOnOverlapBegin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AItemMaster_OnOverlapBegin()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AItemMaster_OnOverlapBegin_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AItemMaster::execOnOverlapBegin)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOverlapBegin(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// End Class AItemMaster Function OnOverlapBegin

// Begin Class AItemMaster Function OnOverlapEnd
struct Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics
{
	struct ItemMaster_eventOnOverlapEnd_Parms
	{
		UPrimitiveComponent* OverlappedComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		int32 OtherBodyIndex;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapEnd_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComponent_MetaData), NewProp_OverlappedComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapEnd_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapEnd_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemMaster_eventOnOverlapEnd_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OverlappedComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::NewProp_OtherBodyIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AItemMaster, nullptr, "OnOverlapEnd", nullptr, nullptr, Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::PropPointers), sizeof(Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::ItemMaster_eventOnOverlapEnd_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::ItemMaster_eventOnOverlapEnd_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AItemMaster_OnOverlapEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AItemMaster_OnOverlapEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AItemMaster::execOnOverlapEnd)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOverlapEnd(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex);
	P_NATIVE_END;
}
// End Class AItemMaster Function OnOverlapEnd

// Begin Class AItemMaster
void AItemMaster::StaticRegisterNativesAItemMaster()
{
	UClass* Class = AItemMaster::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnOverlapBegin", &AItemMaster::execOnOverlapBegin },
		{ "OnOverlapEnd", &AItemMaster::execOnOverlapEnd },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AItemMaster);
UClass* Z_Construct_UClass_AItemMaster_NoRegister()
{
	return AItemMaster::StaticClass();
}
struct Z_Construct_UClass_AItemMaster_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Items/ItemMaster.h" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemSphereComponent_MetaData[] = {
		{ "Category", "Item Master" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemScene_MetaData[] = {
		{ "Category", "Item Master" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemInfo_MetaData[] = {
		{ "Category", "Item Master" },
		{ "ModuleRelativePath", "Public/Items/ItemMaster.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemSphereComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemScene;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ItemInfo;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AItemMaster_OnOverlapBegin, "OnOverlapBegin" }, // 1659270121
		{ &Z_Construct_UFunction_AItemMaster_OnOverlapEnd, "OnOverlapEnd" }, // 1087522748
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AItemMaster>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemSphereComponent = { "ItemSphereComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItemMaster, ItemSphereComponent), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemSphereComponent_MetaData), NewProp_ItemSphereComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemScene = { "ItemScene", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItemMaster, ItemScene), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemScene_MetaData), NewProp_ItemScene_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemInfo = { "ItemInfo", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItemMaster, ItemInfo), Z_Construct_UScriptStruct_FItemStructMaster, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemInfo_MetaData), NewProp_ItemInfo_MetaData) }; // 3057577344
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AItemMaster_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemSphereComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemScene,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItemMaster_Statics::NewProp_ItemInfo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AItemMaster_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AItemMaster_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AItemMaster_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AItemMaster_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UItemInteract_NoRegister, (int32)VTABLE_OFFSET(AItemMaster, IItemInteract), false },  // 3650581592
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AItemMaster_Statics::ClassParams = {
	&AItemMaster::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AItemMaster_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AItemMaster_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AItemMaster_Statics::Class_MetaDataParams), Z_Construct_UClass_AItemMaster_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AItemMaster()
{
	if (!Z_Registration_Info_UClass_AItemMaster.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AItemMaster.OuterSingleton, Z_Construct_UClass_AItemMaster_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AItemMaster.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<AItemMaster>()
{
	return AItemMaster::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AItemMaster);
AItemMaster::~AItemMaster() {}
// End Class AItemMaster

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FItemStructMaster::StaticStruct, Z_Construct_UScriptStruct_FItemStructMaster_Statics::NewStructOps, TEXT("ItemStructMaster"), &Z_Registration_Info_UScriptStruct_ItemStructMaster, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FItemStructMaster), 3057577344U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AItemMaster, AItemMaster::StaticClass, TEXT("AItemMaster"), &Z_Registration_Info_UClass_AItemMaster, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AItemMaster), 3141220402U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_3347650835(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
