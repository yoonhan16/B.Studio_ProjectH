// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InterrogationWidget.h"
#include "../WJ_PlayerState.h"
#include "../WJ_InterrogationObject.h"

void UWJ_InterrogationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NextButton)
	{
		NextButton->OnClicked.AddDynamic(this, &UWJ_InterrogationWidget::ShowNextDialogue);
	}

	if (EndButton)
	{
		EndButton->OnClicked.AddDynamic(this, &UWJ_InterrogationWidget::EndInterrogation);
	}

	OnDialogueEnded.AddDynamic(this, &UWJ_InterrogationWidget::RestoreQustionSelectionUi);
}

void UWJ_InterrogationWidget::InitializeInterrogation(const TArray<FInterrogationScriptEntry>& InQuestions)
{
	AllInterrogationQuestions = InQuestions;
	RefreshQuestionListView();
}

void UWJ_InterrogationWidget::UpdateAvailableQuestions(const TArray<FInterrogationScriptEntry> AllQuestions)
{
	if (!QuestionListView) return;
	
	QuestionListView->ClearListItems();

	AWJ_PlayerState* PlayerState = GetOwningPlayerState<AWJ_PlayerState>();
	if (!PlayerState) return;

	for (const FInterrogationScriptEntry& QuestionEntry : AllQuestions)
	{
		if (QuestionEntry.bRequiresCondition)
		{
			bool bConditionMet = PlayerState->IsConditionMet(QuestionEntry.RequiredClues);
			if (!bConditionMet)
			{
				continue;
			}
		}

		UWJ_InterrogationObject* NewQuestionObject = NewObject<UWJ_InterrogationObject>(this);
		NewQuestionObject->QuestionText = QuestionEntry.Dialogue.DialogueText;
		NewQuestionObject->InterrogationData = QuestionEntry;

		QuestionListView->AddItem(NewQuestionObject);
	}

	

}

void UWJ_InterrogationWidget::SelectQuestion(const TArray<FDialogueEntry>& DialogueScripts)
{
	if (DialogueScripts.Num() == 0 || !DialogueText || !NextButton || !QuestionListView) return;

	CurrentDialogue = DialogueScripts;
	CurrentDialogueIndex = 0;

	DialogueText->SetRenderOpacity(0.0f);
	UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}


	DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));

	QuestionListView->SetVisibility(ESlateVisibility::Collapsed);

	EnableNextButton();
}

void UWJ_InterrogationWidget::ShowNextDialogue()
{
	if (CurrentDialogue.Num() == 0 || !DialogueText) return;

	if (CurrentDialogueIndex + 1 < CurrentDialogue.Num())
	{
		CurrentDialogueIndex++;
		DialogueText->SetText(FText::FromString(CurrentDialogue[CurrentDialogueIndex].DialogueText));
	
		HandleDialogueUpdated();

		GetWorld()->GetTimerManager().SetTimer(AutoProceedTimer, this, &UWJ_InterrogationWidget::ShowNextDialogue, 4.0f, false);
	
		NextButton->SetIsEnabled(true);
	}
	else
	{

		EndInterrogation();
	}
}

void UWJ_InterrogationWidget::EndInterrogation()
{
	CurrentDialogue.Empty();
	CurrentDialogueIndex = 0;

	if (NextButton)
	{
		NextButton->SetIsEnabled(false);
	}

	ResetInterrogationUi();

	OnDialogueEnded.Broadcast();

	RemoveFromParent();
	MarkAsGarbage();
}

void UWJ_InterrogationWidget::HandleDialogueUpdated()
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

void UWJ_InterrogationWidget::RefreshQuestionListView()
{
	if (!QuestionListView) return;

	QuestionListView->ClearListItems();

	AWJ_PlayerState* PlayerState = GetOwningPlayerState<AWJ_PlayerState>();
	if (!PlayerState) return;

	for (const FInterrogationScriptEntry& Question : AllInterrogationQuestions)
	{
		if (PlayerState->IsConditionMet(Question.RequiredClues))
		{
			UWJ_InterrogationObject* NewQuestionObject = NewObject<UWJ_InterrogationObject>(this);
			NewQuestionObject->QuestionText = Question.Dialogue.DialogueText;
			NewQuestionObject->InterrogationData = Question;

			QuestionListView->AddItem(NewQuestionObject);

		}
	}

}

void UWJ_InterrogationWidget::ResetInterrogationUi()
{
	if (!QuestionListView || !DialogueText || !NextButton)
	{
		return;
	}

	if (QuestionListView)
	{
		QuestionListView->SetVisibility(ESlateVisibility::Visible);
	}

	if (DialogueText)
	{
		DialogueText->SetText(FText::GetEmpty());
	}

	if (NextButton)
	{
		NextButton->SetIsEnabled(false);
	}
}

void UWJ_InterrogationWidget::RestoreQustionSelectionUi()
{
	if (NextButton)
	{
		NextButton->SetIsEnabled(true);
	}

	if (DialogueText)
	{
		DialogueText->SetText(FText::GetEmpty());
	}

	if (QuestionListView)
	{
		QuestionListView->SetVisibility(ESlateVisibility::Visible);
	}
}
