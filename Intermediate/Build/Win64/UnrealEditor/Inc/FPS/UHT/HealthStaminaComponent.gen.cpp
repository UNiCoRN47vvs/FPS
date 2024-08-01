// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/ActorComponents/State/HealthStaminaComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHealthStaminaComponent() {}

// Begin Cross Module References
FPS_API UClass* Z_Construct_UClass_UHealthStaminaComponent();
FPS_API UClass* Z_Construct_UClass_UHealthStaminaComponent_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStateMasterComponent();
FPS_API UEnum* Z_Construct_UEnum_FPS_EStateName();
FPS_API UFunction* Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Delegate FChangeState
struct Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics
{
	struct _Script_FPS_eventChangeState_Parms
	{
		EStateName StateName;
		double CurrentValue;
		double MaxValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_StateName_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StateName;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CurrentValue;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_StateName_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_StateName = { "StateName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FPS_eventChangeState_Parms, StateName), Z_Construct_UEnum_FPS_EStateName, METADATA_PARAMS(0, nullptr) }; // 2250722387
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_CurrentValue = { "CurrentValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FPS_eventChangeState_Parms, CurrentValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FPS_eventChangeState_Parms, MaxValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_StateName_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_StateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_CurrentValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FPS, nullptr, "ChangeState__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::_Script_FPS_eventChangeState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::_Script_FPS_eventChangeState_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FChangeState_DelegateWrapper(const FMulticastScriptDelegate& ChangeState, EStateName StateName, double CurrentValue, double MaxValue)
{
	struct _Script_FPS_eventChangeState_Parms
	{
		EStateName StateName;
		double CurrentValue;
		double MaxValue;
	};
	_Script_FPS_eventChangeState_Parms Parms;
	Parms.StateName=StateName;
	Parms.CurrentValue=CurrentValue;
	Parms.MaxValue=MaxValue;
	ChangeState.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FChangeState

// Begin Class UHealthStaminaComponent Function ChangeStateValue
struct Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics
{
	struct HealthStaminaComponent_eventChangeStateValue_Parms
	{
		EStateName StateName;
		double Value;
		bool bIncrease;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_StateName_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StateName;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_Value;
	static void NewProp_bIncrease_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncrease;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_StateName_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_StateName = { "StateName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthStaminaComponent_eventChangeStateValue_Parms, StateName), Z_Construct_UEnum_FPS_EStateName, METADATA_PARAMS(0, nullptr) }; // 2250722387
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthStaminaComponent_eventChangeStateValue_Parms, Value), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_bIncrease_SetBit(void* Obj)
{
	((HealthStaminaComponent_eventChangeStateValue_Parms*)Obj)->bIncrease = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_bIncrease = { "bIncrease", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HealthStaminaComponent_eventChangeStateValue_Parms), &Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_bIncrease_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_StateName_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_StateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::NewProp_bIncrease,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthStaminaComponent, nullptr, "ChangeStateValue", nullptr, nullptr, Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::HealthStaminaComponent_eventChangeStateValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::HealthStaminaComponent_eventChangeStateValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthStaminaComponent::execChangeStateValue)
{
	P_GET_ENUM(EStateName,Z_Param_StateName);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_Value);
	P_GET_UBOOL(Z_Param_bIncrease);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ChangeStateValue(EStateName(Z_Param_StateName),Z_Param_Value,Z_Param_bIncrease);
	P_NATIVE_END;
}
// End Class UHealthStaminaComponent Function ChangeStateValue

// Begin Class UHealthStaminaComponent Function RegenTimerManager
struct Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics
{
	struct HealthStaminaComponent_eventRegenTimerManager_Parms
	{
		EStateName StateName;
		double CurrentValue;
		double MaxValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_StateName_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StateName;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CurrentValue;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_StateName_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_StateName = { "StateName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthStaminaComponent_eventRegenTimerManager_Parms, StateName), Z_Construct_UEnum_FPS_EStateName, METADATA_PARAMS(0, nullptr) }; // 2250722387
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_CurrentValue = { "CurrentValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthStaminaComponent_eventRegenTimerManager_Parms, CurrentValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthStaminaComponent_eventRegenTimerManager_Parms, MaxValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_StateName_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_StateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_CurrentValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthStaminaComponent, nullptr, "RegenTimerManager", nullptr, nullptr, Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::HealthStaminaComponent_eventRegenTimerManager_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::HealthStaminaComponent_eventRegenTimerManager_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthStaminaComponent::execRegenTimerManager)
{
	P_GET_ENUM(EStateName,Z_Param_StateName);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_CurrentValue);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_MaxValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegenTimerManager(EStateName(Z_Param_StateName),Z_Param_CurrentValue,Z_Param_MaxValue);
	P_NATIVE_END;
}
// End Class UHealthStaminaComponent Function RegenTimerManager

// Begin Class UHealthStaminaComponent Function WasteStaminaTimerManager
struct Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics
{
	struct HealthStaminaComponent_eventWasteStaminaTimerManager_Parms
	{
		bool bStart;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bStart_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bStart;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::NewProp_bStart_SetBit(void* Obj)
{
	((HealthStaminaComponent_eventWasteStaminaTimerManager_Parms*)Obj)->bStart = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::NewProp_bStart = { "bStart", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HealthStaminaComponent_eventWasteStaminaTimerManager_Parms), &Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::NewProp_bStart_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::NewProp_bStart,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthStaminaComponent, nullptr, "WasteStaminaTimerManager", nullptr, nullptr, Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::HealthStaminaComponent_eventWasteStaminaTimerManager_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::HealthStaminaComponent_eventWasteStaminaTimerManager_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthStaminaComponent::execWasteStaminaTimerManager)
{
	P_GET_UBOOL(Z_Param_bStart);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->WasteStaminaTimerManager(Z_Param_bStart);
	P_NATIVE_END;
}
// End Class UHealthStaminaComponent Function WasteStaminaTimerManager

// Begin Class UHealthStaminaComponent
void UHealthStaminaComponent::StaticRegisterNativesUHealthStaminaComponent()
{
	UClass* Class = UHealthStaminaComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ChangeStateValue", &UHealthStaminaComponent::execChangeStateValue },
		{ "RegenTimerManager", &UHealthStaminaComponent::execRegenTimerManager },
		{ "WasteStaminaTimerManager", &UHealthStaminaComponent::execWasteStaminaTimerManager },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHealthStaminaComponent);
UClass* Z_Construct_UClass_UHealthStaminaComponent_NoRegister()
{
	return UHealthStaminaComponent::StaticClass();
}
struct Z_Construct_UClass_UHealthStaminaComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "ActorComponents/State/HealthStaminaComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnChangeState_MetaData[] = {
		{ "Category", "Health Stamina Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateMap_MetaData[] = {
		{ "Category", "Health Stamina Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/State/HealthStaminaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnChangeState;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_StateMap_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_StateMap_Key_KeyProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StateMap_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_StateMap;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHealthStaminaComponent_ChangeStateValue, "ChangeStateValue" }, // 3146546052
		{ &Z_Construct_UFunction_UHealthStaminaComponent_RegenTimerManager, "RegenTimerManager" }, // 1320142474
		{ &Z_Construct_UFunction_UHealthStaminaComponent_WasteStaminaTimerManager, "WasteStaminaTimerManager" }, // 3633250824
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthStaminaComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_OnChangeState = { "OnChangeState", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthStaminaComponent, OnChangeState), Z_Construct_UDelegateFunction_FPS_ChangeState__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnChangeState_MetaData), NewProp_OnChangeState_MetaData) }; // 2054396982
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_ValueProp = { "StateMap", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_Key_KeyProp = { "StateMap_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_FPS_EStateName, METADATA_PARAMS(0, nullptr) }; // 2250722387
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap = { "StateMap", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthStaminaComponent, StateMap), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateMap_MetaData), NewProp_StateMap_MetaData) }; // 2250722387
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHealthStaminaComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_OnChangeState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_Key_KeyProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthStaminaComponent_Statics::NewProp_StateMap,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthStaminaComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UHealthStaminaComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UStateMasterComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthStaminaComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthStaminaComponent_Statics::ClassParams = {
	&UHealthStaminaComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UHealthStaminaComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UHealthStaminaComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthStaminaComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthStaminaComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UHealthStaminaComponent()
{
	if (!Z_Registration_Info_UClass_UHealthStaminaComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthStaminaComponent.OuterSingleton, Z_Construct_UClass_UHealthStaminaComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHealthStaminaComponent.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UHealthStaminaComponent>()
{
	return UHealthStaminaComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UHealthStaminaComponent);
UHealthStaminaComponent::~UHealthStaminaComponent() {}
// End Class UHealthStaminaComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHealthStaminaComponent, UHealthStaminaComponent::StaticClass, TEXT("UHealthStaminaComponent"), &Z_Registration_Info_UClass_UHealthStaminaComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthStaminaComponent), 1006714974U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_4056764376(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
