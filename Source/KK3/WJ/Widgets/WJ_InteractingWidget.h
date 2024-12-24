// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "WJ_InteractingWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InteractingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Actor Interact", meta = (BindWidget, AllowPrivateAccess = "true"))
	UImage* InteractionImage;

protected:
	
	UPROPERTY(EditAnywhere ,BlueprintReadOnly, Category = "Actor Interact", meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* ActorImageButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Interact", meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* ExitButton;

	UFUNCTION(BlueprintCallable)
	void ActorImageHovered();

	UFUNCTION(BlueprintCallable)
	void ActorImageClicked();
	
	UFUNCTION(BlueprintCallable)
	void ActorImageReleased();

	UFUNCTION(BlueprintCallable)
	void BreakInteract();
};
