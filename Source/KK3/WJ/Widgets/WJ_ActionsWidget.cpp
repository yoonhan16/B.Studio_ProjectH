// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionsWidget.h"
#include "../WJ_PlayerState.h"
#include "../WJ_Object.h"
#include "Animation/WidgetAnimation.h"
#include "UObject/UnrealType.h"
#include "WJ_ActionItemWidget.h"

void UWJ_ActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UWJ_ActionsWidget::UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct)
{
	AWJ_PlayerState* PlayerState = GetOwningPlayerState<AWJ_PlayerState>();
	if (!PlayerState || !ActionListView || !ActionItemWidgetClass) return;

	ActionListView->ClearListItems();

	int32 Count = 0;

	bool Available = true;
	bool bHasValidActions = false;

	for (FActionRequirements ActionScript : NewActionScriptStruct.ActionValidator)
	{
		Available = true;

		for (int32 RequiredClueID : ActionScript.CheckList)
		{
			if (!PlayerState->IsClueActive(RequiredClueID))
			{
				Available = false;
				break;
			}
			// Get PlayerState and check clue is active 
			// if not active clue , break this
		}

		if (NewActionScriptStruct.ActionScripts.IsValidIndex(Count) && Available)
		{
			UWJ_Object* NewActionData = NewObject<UWJ_Object>(this);
			NewActionData->ActionName = NewActionScriptStruct.ActionScripts[Count].ActionName;
			NewActionData->Scripts = NewActionScriptStruct.ActionScripts[Count].Descriptions;			

			ActionListView->AddItem(NewActionData);

		}

		Count++;

	}

	if (!bHasValidActions)
	{
		UWJ_Object* EmptyActionData = NewObject<UWJ_Object>(this);
		EmptyActionData->ActionName = TEXT("조사를 마쳤습니다.");
		EmptyActionData->Scripts.Add(FDialogueEntry{ TEXT("더 이상 조사할 것이 없습니다."), EDialogueType::End });
		ActionListView->AddItem(EmptyActionData);
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

void UWJ_ActionsWidget::HideListView()
{
	if (ActionListView)
	{
		ActionListView->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWJ_ActionsWidget::ShowListView()
{
	if (ActionListView)
	{
		ActionListView->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWJ_ActionsWidget::DisplayScript(TArray<FDialogueEntry> NewScripts)
{
	if (NewScripts.Num() == 0) return;

	CurrentScripts = NewScripts;
	CurrentScriptIndex = 0;

	if (ScriptText)
	{
		ScriptText->SetText(FText::FromString(CurrentScripts[CurrentScriptIndex].DialogueText));
		ScriptText->SetRenderOpacity(0.0f);

		UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
		
		if (FadeInAnimation)
		{
			PlayAnimation(FadeInAnimation);
		}
	}

	if (NextButton)
	{
		NextButton->SetVisibility(ESlateVisibility::Visible);
		NextButton->OnClicked.AddDynamic(this, &UWJ_ActionsWidget::NextScript);

	}
}

void UWJ_ActionsWidget::NextScript()
{
	CurrentScriptIndex++;

	if (CurrentScriptIndex < CurrentScripts.Num())
	{
		if (ScriptText)
		{
			ScriptText->SetText(FText::FromString(CurrentScripts[CurrentScriptIndex].DialogueText));
			ScriptText->SetRenderOpacity(0.0f);

			UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");

			if (FadeInAnimation)
			{
				PlayAnimation(FadeInAnimation);
			}
		
		}
	}
	else
	{
		HandleEndOfDialogue();
	}

}

void UWJ_ActionsWidget::HandleEndOfDialogue()
{
	if (ScriptText)
	{
		ScriptText->SetText(FText::FromString(""));
		ScriptText->SetRenderOpacity(0.0f);
	}

	if (NextButton)
	{
		NextButton->SetVisibility(ESlateVisibility::Collapsed);
		NextButton->OnClicked.Clear();
	}

	ShowListView();
}

UWidgetAnimation* UWJ_ActionsWidget::FindAnimation(const FName& AnimationName)
{
	FProperty* Prop = GetClass()->FindPropertyByName(AnimationName);

	if (Prop)
	{
		FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop);

		if (ObjProp)
		{
			UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
			return (Obj && Obj->IsA<UWidgetAnimation>()) ? Cast<UWidgetAnimation>(Obj) : nullptr ;
		}
	}

	return nullptr;
}