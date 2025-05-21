// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RichTextDisplayWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlockDecorator.h"

//UWJ_RichTextDisplayWidget::UWJ_RichTextDisplayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
//{
//}

void UWJ_RichTextDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DialogueRichText && TextStyleSet)
	{
		DialogueRichText->SetTextStyleSet(TextStyleSet);
	}
}

void UWJ_RichTextDisplayWidget::SetDialogueText(const FText& InText)
{
	if (DialogueRichText)
	{
		DialogueRichText->SetText(InText);
	}
}
