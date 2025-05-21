// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RichTextKeywordHandler.h"
#include "WJ_PlayerState.h"
#include "WJ_RichTextClickableDecorator.h"
#include "WJ_ClickableTextDecorator.h"
#include "Components/RichTextBlock.h"

void UWJ_RichTextKeywordHandler::BindTo(URichTextBlock* TargetRichText)
{
	if (!TargetRichText) return;

	PlayerState = Cast<AWJ_PlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	//TargetRichText->OnHyperlinkClicked.AddDynamic(this, &UWJ_RichTextKeywordHandler::HandleHyperlinkClicked);

	//for (auto& Pair : KeywordEventMap)
	//{
	//	TargetRichText->Decorators.Add(
	//		MakeKeywordDecorator(TargetRichText, Pair.Key)
	//	);
	//}
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
}

void UWJ_RichTextKeywordHandler::InitializeDummyData()
{
	FKeywordEventEntry DummyEntry;
	DummyEntry.bRequiresCondition = false;
	DummyEntry.TriggeredDialogue = {};

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Dummy Data is Readied"));
}

void UWJ_RichTextKeywordHandler::HandleHyperlinkClicked(const FTextRunInfo& RunInfo)
{
	const FString KeywordId = RunInfo.Name;
	HandleKeywordClicked(KeywordId);
}

TSharedRef<ITextDecorator> UWJ_RichTextKeywordHandler::MakeKeywordDecorator(URichTextBlock* Owner, const FString& KeywordId)
{
	return MakeShareable(new FWJ_ClickableTextDecorator(Owner, KeywordId));
}
