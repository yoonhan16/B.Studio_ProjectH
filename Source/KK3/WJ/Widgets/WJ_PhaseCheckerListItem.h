// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WJ_PhaseCheckerListItem.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_PhaseCheckerListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
