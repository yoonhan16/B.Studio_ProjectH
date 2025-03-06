// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InterrogationWidget.h"
#include "../WJ_PlayerState.h"

void UWJ_InterrogationWidget::UpdateAvailableQuestions(FActionScriptStruct NewQuestionData)
{
	if (!QuestionListView) return;

	QuestionListView->ClearListItems();
	AWJ_PlayerState* PlayerState = GetOwningPlayerState<AWJ_PlayerState>();

	if (!PlayerState) return;

	bool bIsAvailable = true;

	for (const FActionEntry& Question : NewQuestionData.ActionScripts)
	{
		bIsAvailable = true;

		for (int32 RequiredClueID : Question.RequiredClues)
		{
			if (!PlayerState->IsClueActive(RequiredClueID))
			{
				bIsAvailable = false;
				break;
			}
		}

		if (bIsAvailable)
		{
			UWJ_Object* NewQuestionData = NewObject<UWJ_Object>(this);
			NewQuestionData->ActionName = Question.ActionName;
			NewQuestionData->Scripts = Question.Descriptions;
			QuestionListView->AddItem(NewQuestionData);
		}
	}

}

void UWJ_InterrogationWidget::OnQuestionSelected(UWJ_Object* SelectedQuestion)
{
	if (!SelectedQuestion || !DialogueText) return;

	CurrentDialogue = SelectedQuestion->Scripts;
	CurrentDialogueIndex = 0;

	DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));
	QuestionListView->SetVisibility(ESlateVisibility::Collapsed);
}

void UWJ_InterrogationWidget::NextDialogue()
{
	if (CurrentDialogueIndex + 1 < CurrentDialogue.Num())
	{
		CurrentDialogueIndex++;
		DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));
	}
	else
	{
		OnDialogueEnded.Broadcast();
	}
}

void UWJ_InterrogationWidget::EndInterrogation()
{
	RemoveFromParent();
	MarkAsGarbage();
}
