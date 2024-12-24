// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Listview.h"
#include "WJ_ActionListItem.h"
#include "WJ_ActionListWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ActionListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UListView> ActionList;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UWJ_ActionListItem> ActionListItem;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, bool> Actions;

public:

	UFUNCTION(BlueprintCallable)
	void SetActionList();

	UFUNCTION(BlueprintCallable)
	void SetActions(TMap<FString, bool> NewActions);
};
