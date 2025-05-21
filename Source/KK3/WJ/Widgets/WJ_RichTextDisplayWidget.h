// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Engine/DataTable.h"
#include "WJ_RichTextDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_RichTextDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//UWJ_RichTextDisplayWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetDialogueText(const FText& InText);

protected:

	UPROPERTY(meta = (BindWidget))
	URichTextBlock* DialogueRichText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	UDataTable* TextStyleSet;

};
