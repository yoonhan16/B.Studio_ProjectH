// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionsWidget.h"
#include "../WJ_PlayerState.h"
#include "../WJ_Object.h"
#include "../WJ_PlayerController.h"
#include "Components/ListView.h"
#include "Animation/WidgetAnimation.h"
#include "UObject/UnrealType.h"
#include "WJ_ActionItemWidget.h"

void UWJ_ActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NextButton)
	{
		NextButton->SetIsEnabled(false);
		NextButton->OnClicked.AddDynamic(this, &UWJ_ActionsWidget::OnNextButtonClicked);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UWJ_ActionsWidget::OnCloseButtonClicked);
	}

	OnDialogueEnded.AddDynamic(this, &UWJ_ActionsWidget::RestoreActionSelectionUi);
}

void UWJ_ActionsWidget::InitializeWidget(AWJ_PlayerController* InPlayerController)
{
	OwnerPlayerController = InPlayerController;
}

void UWJ_ActionsWidget::UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("UpdateAvailableActions is Called"));

	AWJ_PlayerState* PlayerState = GetOwningPlayerState<AWJ_PlayerState>();
	if (!PlayerState || !ActionListView || !ActionItemWidgetClass) return;

	ActionListView->ClearListItems();

	int32 Count = 0;

	bool Available = true;
	bool bHasValidActions = false;

	for (const FActionEntry& ActionEntry : NewActionScriptStruct.ActionScripts)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Check the ActionEntry"));

		Available = true;

		if (PlayerState->IsConditionMet(ActionEntry.RequiredClues))
		{
			UWJ_Object* NewActionData = NewObject<UWJ_Object>(this);
			NewActionData->ActionName = ActionEntry.ActionName;
			NewActionData->Scripts = ActionEntry.Descriptions;		
			NewActionData->ParentWidget = this;

			ActionListView->AddItem(NewActionData);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ActionData is Add!"));
		}

		Count++;

	}

	if (ActionListView->GetNumItems() == 0)
	{
		UWJ_Object* NoActionData = NewObject<UWJ_Object>(this);
		NoActionData->ActionName = TEXT("조사를 마쳤습니다.");
		NoActionData->Scripts.Add(FDialogueEntry{ TEXT("더 이상 조사할 것이 없습니다."), EDialogueType::End });
		ActionListView->AddItem(NoActionData);
	}

	if (NextButton)
	{
		EnableNextButton(false);
	}
}

void UWJ_ActionsWidget::UpdateSelectedAction(UWJ_ActionItemWidget* SelectedItem)
{
	if (!SelectedItem) return;

	for (UObject* ItemObject : ActionListView->GetListItems())
	{
		UWJ_ActionItemWidget* ItemWidget = Cast<UWJ_ActionItemWidget>(ItemObject);
		if (ItemWidget && (ItemWidget != SelectedItem))
		{
			ItemWidget->ResetStyle();
		}
	}

	SelectedItem->HighlightStyle();
}

void UWJ_ActionsWidget::OnActionHovered(UWJ_ActionItemWidget* HoveredItem)
{
	if (!HoveredItem) return;

	HoveredItem->HighlightStyle();
}

void UWJ_ActionsWidget::OnActionUnhovered(UWJ_ActionItemWidget* UnhoveredItem)
{
	if (!UnhoveredItem) return;

	UnhoveredItem->ResetStyle();
}

void UWJ_ActionsWidget::OnNextButtonClicked()
{
}

void UWJ_ActionsWidget::OnCloseButtonClicked()
{
	if (OwnerPlayerController)
	{
		OwnerPlayerController->ActionsWidget = nullptr;
	}

	this->RemoveFromParent();
	MarkAsGarbage();
}

void UWJ_ActionsWidget::EnableNextButton(bool bEnable)
{
	if (NextButton)
	{
		NextButton->SetIsEnabled(bEnable);
	}
}

void UWJ_ActionsWidget::HideListView()
{
	if (ActionListView)
	{
		ActionListView->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWJ_ActionsWidget::ShowListView()
{
	if (ActionListView)
	{
		ActionListView->SetVisibility(ESlateVisibility::Visible);
	}
}

//void UWJ_ActionsWidget::DisplayScript(TArray<FDialogueEntry> NewScripts)
//{
//	Super::DisplayScript(NewScripts);
//
//	if (NewScripts.Num() == 0) return;
//
//	CurrentScripts = NewScripts;
//	CurrentScriptIndex = 0;
//
//	if (ScriptText)
//	{
//		ScriptText->SetText(FText::FromString(CurrentScripts[CurrentScriptIndex].DialogueText));
//		ScriptText->SetRenderOpacity(0.0f);
//
//		UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
//		
//		if (FadeInAnimation)
//		{
//			PlayAnimation(FadeInAnimation);
//		}
//	}
//
//	if (NextButton)
//	{
//		NextButton->SetVisibility(ESlateVisibility::Visible);
//		NextButton->OnClicked.AddDynamic(this, &UWJ_ActionsWidget::NextScript);
//
//	}
//}

//void UWJ_ActionsWidget::NextScript()
//{
//	Super::NextScript();
//
//	CurrentScriptIndex++;
//
//	if (CurrentScriptIndex < CurrentScripts.Num())
//	{
//		if (ScriptText)
//		{
//			ScriptText->SetText(FText::FromString(CurrentScripts[CurrentScriptIndex].DialogueText));
//			ScriptText->SetRenderOpacity(0.0f);
//
//			UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
//
//			if (FadeInAnimation)
//			{
//				PlayAnimation(FadeInAnimation);
//			}
//		
//		}
//	}
//	else
//	{
//		HandleEndOfDialogue();
//	}
//
//}

//void UWJ_ActionsWidget::HandleEndOfDialogue()
//{
//	Super::HandleEndOfDialogue();
//
//	//if (ScriptText)
//	//{
//	//	ScriptText->SetText(FText::FromString(""));
//	//	ScriptText->SetRenderOpacity(0.0f);
//	//}
//
//	RestoreActionSelectionUi();
//
//	if (NextButton)
//	{
//		EnableNextButton(false);
//		NextButton->OnClicked.Clear();
//	}
//
//	OnDialogueEnded.Broadcast();
//}

void UWJ_ActionsWidget::RestoreActionSelectionUi()
{
	Super::RestoreActionSelectionUi();

	//if (ActionListView)
	//{
	//	ShowListView();
	//}

	//if (ScriptText)
	//{
	//	ScriptText->SetText(FText::GetEmpty());
	//}

	//if (NextButton)
	//{
	//	EnableNextButton(false);
	//}

	if (CloseButton)
	{
		CloseButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWJ_ActionsWidget::ResetActionList()
{
	if (ActionListView)
	{
		ActionListView->ClearListItems();
	}
}
