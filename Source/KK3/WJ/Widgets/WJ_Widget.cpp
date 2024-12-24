// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_Widget.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Components/MultiLineEditableTextBox.h"

void UWJ_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DescriptionBox)
	{
		DescriptionBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWJ_Widget::SetDescriptionText(FText NewText)
{
	if (DescriptionText)
	{
		DescriptionText->SetText(NewText);
	}
}

void UWJ_Widget::SetProgressPercent(float Percent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SetProgressPercent Called"));


	if (ImageProgressBar)
	{
		ImageProgressBar->SetPercent(Percent);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Percent is %f"), Percent));
	}
}

void UWJ_Widget::UpdatePhaseCheckList()
{
	if (PhaseCheckList)
	{

	}
}
