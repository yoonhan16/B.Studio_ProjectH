// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "WJ_Widget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_ActionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ActionsWidget : public UWJ_Widget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UListView* ActionListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> ActionItemWidgetClass;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct);

	UFUNCTION(BlueprintCallable)
	void UpdateSelectedAction(UWJ_ActionItemWidget* SelectedItem);

	UFUNCTION(BlueprintCallable)
	void OnActionHovered(UWJ_ActionItemWidget* HoveredItem);

	UFUNCTION(BlueprintCallable)
	void OnActionUnhovered(UWJ_ActionItemWidget* UnhoveredItem);

	UFUNCTION(BlueprintCallable)
	void HideListView();

	UFUNCTION(BlueprintCallable)
	void ShowListView();
};
