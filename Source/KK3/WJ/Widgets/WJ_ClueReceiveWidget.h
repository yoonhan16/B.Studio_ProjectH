// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_ClueReceiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ClueReceiveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void AddClueToUI(const FSubmittedClue& NewClue);
};
