// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../WJ_ItemStruct.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "WJ_InteractActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InteractActionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* ActionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProgressiveNum;

	UFUNCTION(BlueprintCallable)
	void AddInteractInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlotStruct Information;

	UFUNCTION(BlueprintCallable)
	void Action();

public:

	UFUNCTION()
	void SetProgressiveNum(int32 Num);
};
