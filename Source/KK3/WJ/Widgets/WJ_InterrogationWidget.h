// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WJ_Widget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "WJ_ActionsWidget.h"
#include "../WJ_Object.h"
#include "WJ_InterrogationWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InterrogationWidget : public UWJ_Widget
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(meta = (BindWidget))
	UListView* QuestionListView;

	UPROPERTY(meta = (BindWidget))
	UButton* NextButton;

	UPROPERTY(meta = (BindWidget))
	UButton* EndButton;

	UPROPERTY(BlueprintReadWrite)
	TArray<FDialogueEntry> CurrentDialogue;

	int32 CurrentDialogueIndex = 0;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnded OnDialogueEnded;

	FTimerHandle NextButtonEnableTimer;

	FTimerHandle AutoProceedTimer;
public:

	UFUNCTION(BlueprintCallable)
	void UpdateAvailableQuestions(FActionScriptStruct NewQuestionData);

	UFUNCTION(BlueprintCallable)
	void OnQuestionSelected(UWJ_Object* SelectedQuestion);

	UFUNCTION(BlueprintCallable)
	void NextDialogue();

	UFUNCTION(BlueprintCallable)
	void EndInterrogation();

	UFUNCTION(BlueprintCallable)
	void OnDialogueUpdated();

	UFUNCTION(blueprintCallable)
	void EnableNextButton();
};
