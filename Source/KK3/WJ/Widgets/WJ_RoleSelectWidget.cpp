// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RoleSelectWidget.h"
#include "Components/Button.h"
#include "../WJ_PlayerState.h"

void UWJ_RoleSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ProfilerButton)
	{
		ProfilerButton->OnClicked.AddDynamic(this, &UWJ_RoleSelectWidget::OnSelectProfiler);
	}

	if (InvestigatorButton)
	{
		InvestigatorButton->OnClicked.AddDynamic(this, &UWJ_RoleSelectWidget::OnSelectInvestigator);
	}

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UWJ_RoleSelectWidget::OnConfirmSelection);
	}
}

void UWJ_RoleSelectWidget::OnSelectProfiler()
{
	SelectedRole = EPlayerRole::Profiler;
	if (SelectedRoleText)
	{
		SelectedRoleText->SetText(FText::FromString(TEXT("Selected Role : Profiler")));
	}
}

void UWJ_RoleSelectWidget::OnSelectInvestigator()
{
	SelectedRole = EPlayerRole::Investigator;
	if (SelectedRoleText)
	{
		SelectedRoleText->SetText(FText::FromString(TEXT("Selected Role : Investigator")));
	}
}

void UWJ_RoleSelectWidget::OnConfirmSelection()
{
	if (SelectedRole == EPlayerRole::None) return;

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		AWJ_PlayerState* PS = PC->GetPlayerState<AWJ_PlayerState>();
		if (PS)
		{

			PS->SetPlayerRole(SelectedRole);
		}
	}

	RemoveFromParent();
}
