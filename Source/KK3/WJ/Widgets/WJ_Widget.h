// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_Widget.generated.h"

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
public:

	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FText NewText);

	UFUNCTION(BlueprintCallable)
	void SetProgressPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdatePhaseCheckList();

	UFUNCTION(BlueprintCallable)
	void UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct);
};
