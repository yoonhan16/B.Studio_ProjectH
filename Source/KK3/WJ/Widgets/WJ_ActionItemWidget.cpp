// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "WJ_ActionsWidget.h"
#include "Components/Button.h"
#include "../WJ_ItemStruct.h"
#include "../WJ_Object.h"

void UWJ_ActionItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UWJ_ActionItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UWJ_Object* ActionData = Cast<UWJ_Object>(ListItemObject);
	if (ActionData)
	{

		Scripts = ActionData->Scripts;
		ParentActionsWidget = Cast<UWJ_ActionsWidget>(ActionData->ParentWidget);

		if(ActionText)
		{
			ActionText->SetText(FText::FromString(ActionData->ActionName));
		}

		if (ActionButton)
		{
			ActionButton->OnClicked.AddDynamic(this, &UWJ_ActionItemWidget::OnActionSelected);
			ActionButton->OnHovered.AddDynamic(this, &UWJ_ActionItemWidget::OnHoveredEffect);
			ActionButton->OnUnhovered.AddDynamic(this, &UWJ_ActionItemWidget::OnUnhoveredEffect);
		}
	}
}

void UWJ_ActionItemWidget::OnActionSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("OnActionSelected is Called"));

	if (ParentActionsWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("ParentActionsWidget is Collect"));

		ParentActionsWidget->UpdateSelectedAction(this);
		ParentActionsWidget->HideListView();

		if (Scripts.Num() > 0)
		{
			ParentActionsWidget->DisplayScript(Scripts);
			ParentActionsWidget->EnableNextButton(true);
		}
	}

}


void UWJ_ActionItemWidget::OnHoveredEffect()
{
	if (ParentActionsWidget)
	{
		ParentActionsWidget->OnActionHovered(this);
	}
}

void UWJ_ActionItemWidget::OnUnhoveredEffect()
{
	if (ParentActionsWidget)
	{
		ParentActionsWidget->OnActionUnhovered(this);
	}
}

void UWJ_ActionItemWidget::HighlightStyle()
{
	if (ActionText)
	{
		FLinearColor TargetColor = FLinearColor(1.0f, 0.8f, 0.2f, 1.0f);
		ActionText->SetRenderScale(FVector2D(1.1f, 1.1f));

		ActionText->SetColorAndOpacity(TargetColor);
	}

	if (ActionButton)
	{
		FButtonStyle NewStyle = ActionButton->
			GetStyle();
		NewStyle.Normal.TintColor = FSlateColor(FLinearColor(0.9f, 0.7f, 0.0f, 1.0f));
		NewStyle.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.8f, 0.2f, 1.0f));
		ActionButton->SetStyle(NewStyle);
	}
}

void UWJ_ActionItemWidget::ResetStyle()
{
	if (ActionText)
	{
		FLinearColor DefaultColor = FLinearColor::White;
		ActionText->SetRenderScale(FVector2D(1.0f, 1.0f));

		ActionText->SetColorAndOpacity(DefaultColor);
	}

	if (ActionButton)
	{
		FButtonStyle DefaultStyle = ActionButton->GetStyle();
		DefaultStyle.Normal.TintColor = FSlateColor(FLinearColor::White);
		DefaultStyle.Hovered.TintColor = FSlateColor(FLinearColor::White);
		ActionButton->SetStyle(DefaultStyle);
	}
}

void UWJ_ActionItemWidget::ExecuteScript()
{

}


