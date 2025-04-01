// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../WJ_ItemStruct.h"
#include "WJ_RoleSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_RoleSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UButton* ProfilerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* InvestigatorButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedRoleText;

	EPlayerRole SelectedRole = EPlayerRole::None;

public:
	UFUNCTION()
	void OnSelectProfiler();

	UFUNCTION()
	void OnSelectInvestigator();

	UFUNCTION()
	void OnConfirmSelection();
};
