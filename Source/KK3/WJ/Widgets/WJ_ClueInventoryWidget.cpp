// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ClueInventoryWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "WJ_ClueItemWidget.h"
#include "../WJ_PlayerController.h"
#include "../WJ_PlayerState.h"
#include "Engine/Engine.h"

void UWJ_ClueInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentSearchText = "";
	CurrentFilter = "All";

	RefreshClueList();

	SearchBox->OnTextChanged.AddDynamic(this, &UWJ_ClueInventoryWidget::OnSearchTextChanged);
	FilterComboBox->OnSelectionChanged.AddDynamic(this, &UWJ_ClueInventoryWidget::OnFilterChanged);
	CloseButton->OnClicked.AddDynamic(this, &UUserWidget::RemoveFromParent);
	ClueListView->OnItemClicked().AddUObject(this, &UWJ_ClueInventoryWidget::OnClueItemClicked);
}

void UWJ_ClueInventoryWidget::InitializeWidget(AWJ_PlayerController* InitialPlayerController, AWJ_PlayerState* InitialPlayerState)
{
	OwnerPlayerController = InitialPlayerController;
	OwnerPlayerState = InitialPlayerState;
}

void UWJ_ClueInventoryWidget::OnSearchTextChanged(const FText& Text)
{
	CurrentSearchText = Text.ToString();
	RefreshClueList();
}

void UWJ_ClueInventoryWidget::OnFilterChanged(FString SelectedItem, ESelectInfo::Type SelectInfo)
{
	CurrentFilter = SelectedItem;
	RefreshClueList();
}

void UWJ_ClueInventoryWidget::OnClueItemClicked(UObject* Item)
{
	if (UWJ_ClueItemWidget* ClueItemWidget = Cast<UWJ_ClueItemWidget>(Item))
	{
		ShowDetailPanal(ClueItemWidget->ClueData);
	}
}

void UWJ_ClueInventoryWidget::ShowDetailPanal(const FLinkedClue& Clue)
{
	DetailName->SetText(FText::FromString(Clue.ClueName));
	DetailDescription->SetText(FText::FromString(Clue.ClueDescription));
	DetailScrollBox->SetVisibility(ESlateVisibility::Visible);

	//RelatedLogsScroll->ClearChildren();
	
}

void UWJ_ClueInventoryWidget::RefreshClueList()
{
	if (!ClueItemWidgetClass) return;
	
	ClueListView->ClearListItems();
	
	if (OwnerPlayerState->GetClueDatabase().Num() == 0) return;

	for (const FLinkedClue& Clue : OwnerPlayerState->GetClueDatabase())
	{
		if (Clue.bIsActive && (CurrentFilter == "All" || CurrentFilter == "Active") && (CurrentSearchText.IsEmpty() || Clue.ClueName.Contains(CurrentSearchText)))
		{
			UWJ_ClueItemWidget* Item = CreateWidget<UWJ_ClueItemWidget>(this, ClueItemWidgetClass);
			Item->Setup(Clue);
			ClueListView->AddItem(Item);
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Item Add"));
	}
}
