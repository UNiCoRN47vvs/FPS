#include "Widgets/MainMenu/CreateNewGameWidget.h"
#include "Components/EditableTextBox.h"
//-----------------------------------------------------------------------------------------------------------
void UCreateNewGameWidget::NativeConstruct()
{
	EditableTB->OnTextChanged.AddDynamic(this, &UCreateNewGameWidget::TextChanged);
}
//-----------------------------------------------------------------------------------------------------------
const FString& UCreateNewGameWidget::GetGameName()
{
	return GameName;
}
//-----------------------------------------------------------------------------------------------------------
void UCreateNewGameWidget::TextChanged(const FText& Text)
{
	if (Text.ToString().Len() > NameSize)
	{
		EditableTB->SetText(FText::FromString(GameName));
		PlayAnimation(ErrorAnimation);
		return;
	}

	GameName = Text.ToString();
}
//-----------------------------------------------------------------------------------------------------------