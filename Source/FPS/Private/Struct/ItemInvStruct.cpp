#include "Struct/ItemInvStruct.h"
//-----------------------------------------------------------------------------------------------------------
TMap<EStateName, float> FItemInvStruct::GetItemStatFromLevel()
{
	float value = 0.0f;
	TMap<EStateName, float> stat = {};
	TMap<EStateName, float> currentStat = {};
	TMap<EStateName, float> nextStat = {};

	if (!bOccupied || !ItemDA)
		return stat;

	if (!NextUpgradeDA)
	{
		NextUpgradeDA = ItemDA->NextUpgrade.LoadSynchronous();
		if (!NextUpgradeDA)
			return stat;
	}

	currentStat = ItemDA->GetItemStat();
	nextStat = NextUpgradeDA->GetItemStat();

	for (const auto& item : currentStat)
	{
		if (!nextStat.Contains(item.Key))
			continue;

		if (ItemDA->ItemGrade == EItemGrade::Legendary)
			value = ItemLevel / 50.0 * item.Value;
		else
			value = ItemLevel / 10.0 * (*nextStat.Find(item.Key) - item.Value);
		
		stat.Add(item.Key, value + item.Value);
	}

	return stat;
}
//-----------------------------------------------------------------------------------------------------------
FStatRange FItemInvStruct::GetItemDamageFromLevel()
{
	FStatRange value = {};
	FStatRange currentDamage = {};
	FStatRange nextDamage = {};

	if (!bOccupied || !ItemDA)
		return value;

	currentDamage = ItemDA->GetItemDamage();

	if (ItemDA->ItemGrade == EItemGrade::Legendary)
	{
		value.ValueMin = ItemLevel / 50.0f * currentDamage.ValueMin;
		value.ValueMax = ItemLevel / 50.0f * currentDamage.ValueMax;
	}
	else
	{
		if (!NextUpgradeDA)
		{
			NextUpgradeDA = ItemDA->NextUpgrade.LoadSynchronous();
			if (!NextUpgradeDA)
				return value;
		}

		nextDamage = NextUpgradeDA->GetItemDamage();

		value.ValueMin = ItemLevel / 10.0f * (nextDamage.ValueMin - currentDamage.ValueMin);
		value.ValueMax = ItemLevel / 10.0f * (nextDamage.ValueMax - currentDamage.ValueMax);
	}

	value.ValueMin += currentDamage.ValueMin;
	value.ValueMax += currentDamage.ValueMax;

	return value;
}
//-----------------------------------------------------------------------------------------------------------
TMap<FString, FText> FItemInvStruct::GetItemInfo()
{
	TMap<FString, FText> itemInfo = ItemDA->GetItemInfo();

	FStatRange damage = GetItemDamageFromLevel();
	FText text {};
	TMap<EStateName, float> stats = GetItemStatFromLevel();


	if (damage.ValueMin != 0.0f && damage.ValueMax != 0.0f)
		itemInfo.Add(TEXT("Damage")
			, FText::Format(FText::FromString("{0}{1}{2}")
				, FText::AsNumber(damage.ValueMin), FText::FromString(TEXT(" - "))
				, FText::AsNumber(damage.ValueMax)));

	for (const auto& item : StatValue.StatsValue)
	{
		if (stats.Contains(item.Key))
			*stats.Find(item.Key) += item.Value;
		else
			stats.Add(item.Key, item.Value);
	}
	
	for (auto& item : stats)
	{
		ENUM_TO_TEXT(item.Key, EStateName, text)

		itemInfo.Add(text.ToString(), FText::AsNumber(item.Value));
	}

	return itemInfo;
}
//-----------------------------------------------------------------------------------------------------------