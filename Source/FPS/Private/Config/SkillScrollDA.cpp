#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------

TMap<FString, FText> USkillScrollDA::GetItemInfo()
{
	TMap<FString, FText> itemInfo = Super::GetItemInfo();

	itemInfo.Add(TEXT("Damage")
		, FText::Format(FText::FromString("{0}{1}{2}")
			, FText::AsNumber(SkillAttackDamage.ValueMin), FText::FromString(TEXT(" - "))
			, FText::AsNumber(SkillAttackDamage.ValueMax)));

	itemInfo.Add(TEXT("Mana Cost"), FText::AsNumber(Cooldown));
	itemInfo.Add(TEXT("Cooldown"), FText::AsNumber(Cooldown));

	itemInfo.Add(TEXT("Skill Element"), StaticEnum<EElementsType>() ? StaticEnum<EElementsType>()->GetDisplayNameTextByValue(static_cast<int32>(SkillElement1)) : FText::FromString(TEXT("Invalid")));


	return itemInfo;
}
