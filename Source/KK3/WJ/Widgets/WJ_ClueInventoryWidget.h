// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WJ_Widget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_ClueInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ClueInventoryWidget : public UWJ_Widget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWJ_PlayerController* OwnerPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWJ_PlayerState* OwnerPlayerState;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* SearchBox;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* FilterComboBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UListView* ClueListView;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* DetailsPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DetailName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailDescription;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* DetailScrollBox;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* RelatedLogsScroll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWJ_ClueItemWidget> ClueItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentSearchText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentFilter;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(AWJ_PlayerController* InitialPlayerController, AWJ_PlayerState* InitialPlayerState);

	UFUNCTION(BlueprintCallable)
	void OnSearchTextChanged(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void OnFilterChanged(FString SelectedItem, ESelectInfo::Type SelectInfo);

	UFUNCTION(BlueprintCallable)
	void OnClueItemClicked(UObject* Item);

	UFUNCTION(BlueprintCallable)
	void ShowDetailPanal(const FLinkedClue& Clue);

	UFUNCTION(BlueprintCallable)
	void RefreshClueList();

};
