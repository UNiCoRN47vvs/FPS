// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/ActorComponents/StorageComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStorageComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
FPS_API UClass* Z_Construct_UClass_AItemMaster_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStorageComponent();
FPS_API UClass* Z_Construct_UClass_UStorageComponent_NoRegister();
FPS_API UFunction* Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature();
FPS_API UScriptStruct* Z_Construct_UScriptStruct_FItemInvStruct();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Delegate FInitInvWidget
struct Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics
{
	struct _Script_FPS_eventInitInvWidget_Parms
	{
		UStorageComponent* StorageComponent;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StorageComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StorageComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::NewProp_StorageComponent = { "StorageComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FPS_eventInitInvWidget_Parms, StorageComponent), Z_Construct_UClass_UStorageComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StorageComponent_MetaData), NewProp_StorageComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::NewProp_StorageComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FPS, nullptr, "InitInvWidget__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::_Script_FPS_eventInitInvWidget_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::_Script_FPS_eventInitInvWidget_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FInitInvWidget_DelegateWrapper(const FMulticastScriptDelegate& InitInvWidget, UStorageComponent* StorageComponent)
{
	struct _Script_FPS_eventInitInvWidget_Parms
	{
		UStorageComponent* StorageComponent;
	};
	_Script_FPS_eventInitInvWidget_Parms Parms;
	Parms.StorageComponent=StorageComponent;
	InitInvWidget.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FInitInvWidget

// Begin ScriptStruct FItemInvStruct
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ItemInvStruct;
class UScriptStruct* FItemInvStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ItemInvStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ItemInvStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FItemInvStruct, (UObject*)Z_Construct_UPackage__Script_FPS(), TEXT("ItemInvStruct"));
	}
	return Z_Registration_Info_UScriptStruct_ItemInvStruct.OuterSingleton;
}
template<> FPS_API UScriptStruct* StaticStruct<FItemInvStruct>()
{
	return FItemInvStruct::StaticStruct();
}
struct Z_Construct_UScriptStruct_FItemInvStruct_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOccupied_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemCount_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemCountMax_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemValue_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemName_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemDesc_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemIcon_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemClass_MetaData[] = {
		{ "Category", "Item Inv Struct" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bOccupied_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOccupied;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ItemCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ItemCountMax;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_ItemValue;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_ItemDesc;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ItemIcon;
	static const UECodeGen_Private::FSoftClassPropertyParams NewProp_ItemClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemInvStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
void Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_bOccupied_SetBit(void* Obj)
{
	((FItemInvStruct*)Obj)->bOccupied = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_bOccupied = { "bOccupied", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FItemInvStruct), &Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_bOccupied_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOccupied_MetaData), NewProp_bOccupied_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemCount = { "ItemCount", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemCount_MetaData), NewProp_ItemCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemCountMax = { "ItemCountMax", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemCountMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemCountMax_MetaData), NewProp_ItemCountMax_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemValue = { "ItemValue", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemValue_MetaData), NewProp_ItemValue_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemName = { "ItemName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemName_MetaData), NewProp_ItemName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemDesc = { "ItemDesc", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemDesc), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemDesc_MetaData), NewProp_ItemDesc_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemIcon = { "ItemIcon", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemIcon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemIcon_MetaData), NewProp_ItemIcon_MetaData) };
const UECodeGen_Private::FSoftClassPropertyParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemClass = { "ItemClass", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftClass, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FItemInvStruct, ItemClass), Z_Construct_UClass_AItemMaster_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemClass_MetaData), NewProp_ItemClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FItemInvStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_bOccupied,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemCountMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemDesc,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemIcon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewProp_ItemClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemInvStruct_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemInvStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
	nullptr,
	&NewStructOps,
	"ItemInvStruct",
	Z_Construct_UScriptStruct_FItemInvStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemInvStruct_Statics::PropPointers),
	sizeof(FItemInvStruct),
	alignof(FItemInvStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemInvStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FItemInvStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FItemInvStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ItemInvStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ItemInvStruct.InnerSingleton, Z_Construct_UScriptStruct_FItemInvStruct_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ItemInvStruct.InnerSingleton;
}
// End ScriptStruct FItemInvStruct

// Begin Class UStorageComponent
void UStorageComponent::StaticRegisterNativesUStorageComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStorageComponent);
UClass* Z_Construct_UClass_UStorageComponent_NoRegister()
{
	return UStorageComponent::StaticClass();
}
struct Z_Construct_UClass_UStorageComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "ActorComponents/StorageComponent.h" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitInvWidget_MetaData[] = {
		{ "Category", "Inventory Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InvMaxSlots_MetaData[] = {
		{ "Category", "Inventory Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InvSlotsPerRow_MetaData[] = {
		{ "Category", "Inventory Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Storage_MetaData[] = {
		{ "Category", "Inventory Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/StorageComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_InitInvWidget;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InvMaxSlots;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InvSlotsPerRow;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Storage_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Storage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStorageComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UStorageComponent_Statics::NewProp_InitInvWidget = { "InitInvWidget", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageComponent, InitInvWidget), Z_Construct_UDelegateFunction_FPS_InitInvWidget__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitInvWidget_MetaData), NewProp_InitInvWidget_MetaData) }; // 1822952603
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UStorageComponent_Statics::NewProp_InvMaxSlots = { "InvMaxSlots", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageComponent, InvMaxSlots), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InvMaxSlots_MetaData), NewProp_InvMaxSlots_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UStorageComponent_Statics::NewProp_InvSlotsPerRow = { "InvSlotsPerRow", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageComponent, InvSlotsPerRow), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InvSlotsPerRow_MetaData), NewProp_InvSlotsPerRow_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UStorageComponent_Statics::NewProp_Storage_Inner = { "Storage", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FItemInvStruct, METADATA_PARAMS(0, nullptr) }; // 2114804959
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UStorageComponent_Statics::NewProp_Storage = { "Storage", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageComponent, Storage), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Storage_MetaData), NewProp_Storage_MetaData) }; // 2114804959
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStorageComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageComponent_Statics::NewProp_InitInvWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageComponent_Statics::NewProp_InvMaxSlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageComponent_Statics::NewProp_InvSlotsPerRow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageComponent_Statics::NewProp_Storage_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageComponent_Statics::NewProp_Storage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UStorageComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStorageComponent_Statics::ClassParams = {
	&UStorageComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UStorageComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UStorageComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UStorageComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStorageComponent()
{
	if (!Z_Registration_Info_UClass_UStorageComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStorageComponent.OuterSingleton, Z_Construct_UClass_UStorageComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStorageComponent.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UStorageComponent>()
{
	return UStorageComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStorageComponent);
UStorageComponent::~UStorageComponent() {}
// End Class UStorageComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FItemInvStruct::StaticStruct, Z_Construct_UScriptStruct_FItemInvStruct_Statics::NewStructOps, TEXT("ItemInvStruct"), &Z_Registration_Info_UScriptStruct_ItemInvStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FItemInvStruct), 2114804959U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStorageComponent, UStorageComponent::StaticClass, TEXT("UStorageComponent"), &Z_Registration_Info_UClass_UStorageComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStorageComponent), 4177712705U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_2757053730(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
