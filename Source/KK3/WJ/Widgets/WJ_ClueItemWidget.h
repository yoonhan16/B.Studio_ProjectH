// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../WJ_ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WJ_ClueItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ClueItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Setup(const FLinkedClue& InClue);

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ClueNameText;

	UPROPERTY(meta = (BindWidget))
	class UImage* ClueIcon;

public:
	UPROPERTY()
	FLinkedClue ClueData;
};
