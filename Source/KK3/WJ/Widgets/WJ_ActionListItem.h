// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WJ_ActionListItem.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ActionListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UTextBlock* ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UImage* ButtonImage;
};
