// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/FPSCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFPSCharacter() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
FPS_API UClass* Z_Construct_UClass_AFPSCharacter();
FPS_API UClass* Z_Construct_UClass_AFPSCharacter_NoRegister();
FPS_API UClass* Z_Construct_UClass_UPlayerInteract_NoRegister();
FPS_API UFunction* Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Delegate FChangeSprint
struct Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics
{
	struct _Script_FPS_eventChangeSprint_Parms
	{
		bool bStart;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bStart_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bStart;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::NewProp_bStart_SetBit(void* Obj)
{
	((_Script_FPS_eventChangeSprint_Parms*)Obj)->bStart = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::NewProp_bStart = { "bStart", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_FPS_eventChangeSprint_Parms), &Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::NewProp_bStart_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::NewProp_bStart,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FPS, nullptr, "ChangeSprint__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::_Script_FPS_eventChangeSprint_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::_Script_FPS_eventChangeSprint_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FChangeSprint_DelegateWrapper(const FMulticastScriptDelegate& ChangeSprint, bool bStart)
{
	struct _Script_FPS_eventChangeSprint_Parms
	{
		bool bStart;
	};
	_Script_FPS_eventChangeSprint_Parms Parms;
	Parms.bStart=bStart ? true : false;
	ChangeSprint.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FChangeSprint

// Begin Class AFPSCharacter
void AFPSCharacter::StaticRegisterNativesAFPSCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFPSCharacter);
UClass* Z_Construct_UClass_AFPSCharacter_NoRegister()
{
	return AFPSCharacter::StaticClass();
}
struct Z_Construct_UClass_AFPSCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "FPSCharacter.h" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnChangeSprint_MetaData[] = {
		{ "Category", "Health Stamina Component" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh1P_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// End of APawn interface\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "End of APawn interface" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnChangeSprint;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh1P;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FirstPersonCameraComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SprintAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFPSCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_OnChangeSprint = { "OnChangeSprint", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, OnChangeSprint), Z_Construct_UDelegateFunction_FPS_ChangeSprint__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnChangeSprint_MetaData), NewProp_OnChangeSprint_MetaData) }; // 986528405
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_Mesh1P = { "Mesh1P", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, Mesh1P), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh1P_MetaData), NewProp_Mesh1P_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_FirstPersonCameraComponent = { "FirstPersonCameraComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, FirstPersonCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstPersonCameraComponent_MetaData), NewProp_FirstPersonCameraComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_SprintAction = { "SprintAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, SprintAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintAction_MetaData), NewProp_SprintAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_InteractAction = { "InteractAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, InteractAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractAction_MetaData), NewProp_InteractAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFPSCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_OnChangeSprint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_Mesh1P,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_FirstPersonCameraComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_SprintAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_InteractAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSCharacter_Statics::NewProp_LookAction,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFPSCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AFPSCharacter_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UPlayerInteract_NoRegister, (int32)VTABLE_OFFSET(AFPSCharacter, IPlayerInteract), false },  // 2036397871
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFPSCharacter_Statics::ClassParams = {
	&AFPSCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AFPSCharacter_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AFPSCharacter_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AFPSCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFPSCharacter()
{
	if (!Z_Registration_Info_UClass_AFPSCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFPSCharacter.OuterSingleton, Z_Construct_UClass_AFPSCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFPSCharacter.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<AFPSCharacter>()
{
	return AFPSCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFPSCharacter);
AFPSCharacter::~AFPSCharacter() {}
// End Class AFPSCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFPSCharacter, AFPSCharacter::StaticClass, TEXT("AFPSCharacter"), &Z_Registration_Info_UClass_AFPSCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFPSCharacter), 304875101U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSCharacter_h_2890579069(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
