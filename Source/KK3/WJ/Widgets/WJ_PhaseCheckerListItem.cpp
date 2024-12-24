// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_PhaseCheckerListItem.h"
#include "../WJ_Object.h"

void UWJ_PhaseCheckerListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UWJ_Object* Object = Cast<UWJ_Object>(ListItemObject);
}
