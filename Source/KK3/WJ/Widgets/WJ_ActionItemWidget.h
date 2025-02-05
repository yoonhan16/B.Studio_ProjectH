// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "WJ_ActionItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ActionItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Scripts;

	UPROPERTY(meta = (BindWidget))
	UButton* ActionButton;

public:
	UPROPERTY()
	UWJ_ActionsWidget* ParentActionsWidget;

	UFUNCTION(BlueprintCallable)
	void OnActionSelected();

	UFUNCTION(BlueprintCallable)
	void OnHoveredEffect();

	UFUNCTION(BlueprintCallable)
	void OnUnhoveredEffect();

	UFUNCTION(BlueprintCallable)
	void HighlightStyle();

	UFUNCTION(BlueprintCallable)
	void ResetStyle();

	UFUNCTION(BlueprintCallable)
	void ExecuteScript();
};
