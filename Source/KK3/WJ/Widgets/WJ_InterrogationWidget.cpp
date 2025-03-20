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
			UWJ_Object* QuestionData = NewObject<UWJ_Object>(this);
			QuestionData->ActionName = Question.ActionName;
			QuestionData->Scripts = Question.Descriptions;
			QuestionListView->AddItem(QuestionData);
		}
	}

}

void UWJ_InterrogationWidget::OnQuestionSelected(UWJ_Object* SelectedQuestion)
{
	if (!SelectedQuestion || !DialogueText) return;

	CurrentDialogue = SelectedQuestion->Scripts;
	CurrentDialogueIndex = 0;

	DialogueText->SetRenderOpacity(0.0f);
	UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}

	DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));
	QuestionListView->SetVisibility(ESlateVisibility::Collapsed);

	HighlightSelectedQuestion(SelectedQuestion, QuestionListView);
}

void UWJ_InterrogationWidget::NextDialogue()
{
	if (CurrentDialogueIndex + 1 < CurrentDialogue.Num())
	{
		CurrentDialogueIndex++;
		DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));
	
		OnDialogueUpdated();

		GetWorld()->GetTimerManager().SetTimer(AutoProceedTimer, this, &UWJ_InterrogationWidget::NextDialogue, 4.0f, false);
	}
	else
	{

		EndInterrogation();
	}
}

void UWJ_InterrogationWidget::EndInterrogation()
{
	OnDialogueEnded.Broadcast();

	CurrentDialogue.Empty();
	CurrentDialogueIndex = 0;

	RemoveFromParent();
	MarkAsGarbage();
}

void UWJ_InterrogationWidget::OnDialogueUpdated()
{
	if(!DialogueText || !NextButton) return;

	NextButton->SetIsEnabled(false);

	DialogueText->SetRenderOpacity(0.0f);
	UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}

	GetWorld()->GetTimerManager().SetTimer(NextButtonEnableTimer, this, &UWJ_InterrogationWidget::EnableNextButton, 1.5f, false);
}

void UWJ_InterrogationWidget::EnableNextButton()
{
	if (NextButton)
	{
		NextButton->SetIsEnabled(true);
	}
}
