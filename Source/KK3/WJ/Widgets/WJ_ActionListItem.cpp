// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ActionListItem.h"
#include "../WJ_Object.h"

void UWJ_ActionListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UWJ_Object* Object = Cast<UWJ_Object>(ListItemObject);

	if (Object)
	{

	}
}
