// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RichTextKeywordHandler.h"
#include "WJ_PlayerState.h"
#include "Components/RichTextBlock.h"

void UWJ_RichTextKeywordHandler::BindTo(URichTextBlock* TargetRichText)
{
	if (TargetRichText)
	{
		//TargetRichText->OnHyperlinkClicked.AddDynamic
	}
}

void UWJ_RichTextKeywordHandler::HandleKeywordClicked(const FString& KeywordId)
{
	if (!KeywordEventMap.Contains(KeywordId))
	{
		UE_LOG(LogTemp, Warning, TEXT("Keyword [%s] not found."), *KeywordId);
		return;
	}

	const FKeywordEventEntry& Entry = KeywordEventMap[KeywordId];

	if (Entry.bRequiresCondition && PlayerState)
	{
		for (int32 ClueId : Entry.RequiredClueIds)
		{
			if (!PlayerState->IsClueActive(ClueId))
			{
				return;
			}
		}
	}

	for (const FDialogueEntry& Line : Entry.TriggeredDialogue)
	{
		UE_LOG(LogTemp, Log, TEXT("[Keyword Trigger] %s"), *Line.DialogueText);
	}

	for (const FDialogueEntry& Line : Entry.TriggeredDialogue)
	{
		UE_LOG(LogTemp, Log, TEXT("[Keyword Trigger] %s"), *Line.DialogueText);
	}
}

void UWJ_RichTextKeywordHandler::HandleHyperlinkClicked(const FTextRunInfo& RunInfo)
{

}
