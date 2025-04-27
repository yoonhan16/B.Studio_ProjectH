// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InterrogationOptionWidget.h"
#include "WJ_InterrogationWidget.h"
#include "../WJ_Object.h"


void UWJ_InterrogationOptionWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UWJ_Object* QuestionData = Cast<UWJ_Object>(ListItemObject))
	{
		OptionText->SetText(FText::FromString(QuestionData->ActionName));
		DialogueScripts = QuestionData->Scripts;
		ParentInterrogationWidget = Cast<UWJ_InterrogationWidget>(QuestionData->ParentWidget);

		if (OptionButton)
		{
			OptionButton->OnClicked.AddDynamic(this, &UWJ_InterrogationOptionWidget::OnOptionClicked);
		}
	}
}

void UWJ_InterrogationOptionWidget::OnOptionClicked()
{
	if (ParentInterrogationWidget)
	{
		ParentInterrogationWidget->SelectQuestion(DialogueScripts);
	}
}
