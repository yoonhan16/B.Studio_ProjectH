// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../WJ_ItemStruct.h"
#include "../WJ_Object.h"
#include "WJ_Widget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);
/**
 * 
 */
UCLASS()
class KK3_API UWJ_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UMultiLineEditableTextBox* DescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* ImageProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UVerticalBox* DescriptionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UListView* PhaseCheckList;

	UWidgetAnimation* FadeIn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> CurrentScripts;

	int32 CurrentScriptIndex = 0;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScriptText;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextButton;

	UPROPERTY(meta = (BindWidget))
	UListView* ActionListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnDialogueEnded OnDialogueEnded;
public:

	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FText NewText);

	UFUNCTION(BlueprintCallable)
	void SetProgressPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdatePhaseCheckList();

	UFUNCTION(BlueprintCallable)
	UWidgetAnimation* FindAnimation(const FName& AnimationName);

	UFUNCTION(BlueprintCallable)
	void HighlightSelectedQuestion(UWJ_Object* SelectedQuestion, UListView* ListView);

	UFUNCTION(BlueprintCallable)
	void DisplayScript(const TArray<FDialogueEntry>& Scripts);

	UFUNCTION(BlueprintCallable)
	void NextScript();

	UFUNCTION(BlueprintCallable)
	void HandleEndOfDialogue();

	virtual void RestoreActionSelectionUi();
};
