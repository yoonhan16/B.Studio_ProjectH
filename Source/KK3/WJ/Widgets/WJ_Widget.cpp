// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_Widget.h"
#include "../WJ_ItemStruct.h"
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

void UWJ_Widget::UpdateAvailableActions(FActionScriptStruct NewActionScriptStruct)
{
	

	if (NewActionScriptStruct.ActionValidator.Num() > 1)
	{
		int32 Count = 0;

		for (FActionRequirements ActionScript : NewActionScriptStruct.ActionValidator)
		{
			bool Available = true;

			for (int32 Action : ActionScript.CheckList)
			{

				// Get PlayerState and check clue is active 
				// if not active clue , break this
				//if()
			}


			if (NewActionScriptStruct.ActionScript.IsValidIndex(Count) && Available)
			{
				NewActionScriptStruct.ActionScript[Count];

				// add item in listview
			}

			Count++;
		}
	}
}
