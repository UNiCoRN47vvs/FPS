#include "Widgets/ElementalEffects/ElementalEffectSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
//-----------------------------------------------------------------------------------------------------------
void UElementalEffectSlot::UpdateSlot(int32 StackCount, UTexture2D* Icon)
{
	if (Icon)
		ImageIcon->SetBrushFromTexture(Icon);
	
	if(StackCount > 0)
		StackCountTB->SetText(FText::AsNumber(StackCount));
}
