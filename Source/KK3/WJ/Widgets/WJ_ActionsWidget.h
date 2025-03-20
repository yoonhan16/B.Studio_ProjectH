// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "WJ_Widget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_ActionsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWJ_PlayerController* OwnerPlayerController;

	UPROPERTY(meta = (BindWidget))
	UListView* ActionListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> ActionItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScriptText;

	UPROPERTY(meta = (BindWidget))
	UButton* NextButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> CurrentScripts;

	int32 CurrentScriptIndex = 0;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnded OnDialogueEnded;
public:
	UFUNCTION()
	void InitializeWidget(AWJ_PlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable)
	void UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct);

	UFUNCTION(BlueprintCallable)
	void UpdateSelectedAction(UWJ_ActionItemWidget* SelectedItem);

	UFUNCTION(BlueprintCallable)
	void OnActionHovered(UWJ_ActionItemWidget* HoveredItem);

	UFUNCTION(BlueprintCallable)
	void OnActionUnhovered(UWJ_ActionItemWidget* UnhoveredItem);

	UFUNCTION(BlueprintCallable)
	void OnNextButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnCloseButtonClicked();

	UFUNCTION(BlueprintCallable)
	void EnableNextButton(bool bEnable);

	UFUNCTION(BlueprintCallable)
	void HideListView();

	UFUNCTION(BlueprintCallable)
	void ShowListView();

	UFUNCTION(BlueprintCallable)
	void DisplayScript(TArray<FDialogueEntry> NewScripts);

	UFUNCTION(BlueprintCallable)
	void NextScript();
	
	UFUNCTION(BlueprintCallable)
	void HandleEndOfDialogue();

	UFUNCTION(BlueprintCallable)
	void RestoreActionSelectionUi();

	UFUNCTION(BlueprintCallable)
	void ResetActionList();
};
