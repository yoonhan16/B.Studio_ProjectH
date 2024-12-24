// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WJ_InvestigatingWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InvestigatingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Interact", meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions", meta = (BindWidget, AllowPrivateAccess = "true"))
	TArray<class UWJ_InteractActionWidget*> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProgressiveNum;

	UFUNCTION(BlueprintCallable)
	void ShowActionWidget(int ActionNum);

	UFUNCTION(BlueprintCallable)
	void HideActionWidget(int ActionNum);

	UFUNCTION(BlueprintCallable)
	void GetArrayNum();

	UFUNCTION(BlueprintCallable)
	void SetActionsNum();

	UFUNCTION(BlueprintCallable)
	void BreakInteract();
};
