// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionListWidget.h"
#include "../WJ_Object.h"

void UWJ_ActionListWidget::SetActionList()
{
	if (ActionList && ActionListItem && (Actions.Num() > 0))
	{
		for (auto& Action : Actions)
		{
			UWJ_Object* Object = NewObject<UWJ_Object>(UWJ_Object::StaticClass());
			Object->ActionName = Action.Key;

			ActionList->AddItem(Object);
		}
	}
}

void UWJ_ActionListWidget::SetActions(TMap<FString, bool> NewActions)
{
	Actions = NewActions;
}
