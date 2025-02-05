// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "WJ_ActionsWidget.h"
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

		if(ActionText)
		{
			ActionText->SetText(FText::FromString(ActionData->ActionName));
		}

		if (!ParentActionsWidget)
		{
			ParentActionsWidget = Cast<UWJ_ActionsWidget>(GetOuter());
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
	if (ParentActionsWidget)
	{
		ParentActionsWidget->UpdateSelectedAction(this);
		ParentActionsWidget->HideListView();
	}

	ExecuteScript();
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
		ActionText->SetRenderScale(FVector2D(1.1f, 1.1f));
		ActionText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.8f, 0.2f, 1.0f)));
	}

	if (ActionButton)
	{
		ActionButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(0.9f, 0.7f, 0.0f, 1.0f));
	}
}

void UWJ_ActionItemWidget::ResetStyle()
{
	if (ActionText)
	{
		ActionText->SetRenderScale(FVector2D(1.0f, 1.0f));
		ActionText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}

	if (ActionButton)
	{
		ActionButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor::White);
	}
}

void UWJ_ActionItemWidget::ExecuteScript()
{
	for (const FString& Line : Scripts)
	{
		//ParentActionsWidget
	}
}
