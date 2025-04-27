// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../WJ_ItemStruct.h"
#include "WJ_InterrogationOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InterrogationOptionWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionText;

	UPROPERTY()
	class UWJ_InterrogationWidget* ParentInterrogationWidget;

	UPROPERTY()
	TArray<FDialogueEntry> DialogueScripts;

	UFUNCTION()
	void OnOptionClicked();
};
