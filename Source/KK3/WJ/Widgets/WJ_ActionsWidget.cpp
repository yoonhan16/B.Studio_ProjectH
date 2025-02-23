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
			//if()
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

void UWJ_ActionsWidget::DisplayScript(const FString& Script)
{
	if (ScriptText)
	{
		ScriptText->SetText(FText::FromString(Script));

		ScriptText->SetRenderOpacity(0.0f);
		UWidgetAnimation* FadeInAnimation = FindAnimation("FadeIn");
	}
}

void UWJ_ActionsWidget::NextScript()
{

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