// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ClueItemWidget.h"
#include "Components/TextBlock.h"

void UWJ_ClueItemWidget::Setup(const FLinkedClue& InClue)
{
	ClueData = InClue;

	if (ClueNameText)
	{
		ClueNameText->SetText(FText::FromString(InClue.ClueName));
	}
}
