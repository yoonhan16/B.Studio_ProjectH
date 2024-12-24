// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InvestigatingWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "../WJ_PlayerController.h"
#include "WJ_InteractActionWidget.h"

void UWJ_InvestigatingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Actions.Num() > 0)
	{
		for (UWJ_InteractActionWidget* Action : Actions)
		{
			Action->SetVisibility(ESlateVisibility::Hidden);
			Action->SetProgressiveNum(ProgressiveNum);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%d"), Actions.Num()));

	ExitButton->OnPressed.AddDynamic(this, &UWJ_InvestigatingWidget::BreakInteract);
}

void UWJ_InvestigatingWidget::ShowActionWidget(int ActionNum)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%d"), Actions.Num()));
	Actions[ActionNum]->SetVisibility(ESlateVisibility::Visible);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Interact Action Widget be Visible"));
}

void UWJ_InvestigatingWidget::HideActionWidget(int ActionNum)
{
	Actions[ActionNum]->SetVisibility(ESlateVisibility::Hidden);
}

void UWJ_InvestigatingWidget::GetArrayNum()
{
	int32 ArrayNum = Actions.Num();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%d"), ArrayNum));
	//if (Actions.Num() > 0)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Actions is Valid"));
	//	for (UWJ_InteractActionWidget* Action : Actions)
	//	{
	//		Action->SetProgressiveNum(ProgressiveNum);
	//	}
	//}
}

void UWJ_InvestigatingWidget::SetActionsNum()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("SetActionNum Called, %d"), Actions.Num()));
	if (Actions.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Actions is Valid"));
		for (UWJ_InteractActionWidget* Action : Actions)
		{
			Action->SetProgressiveNum(ProgressiveNum);
		}
	}
}

void UWJ_InvestigatingWidget::BreakInteract()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AWJ_PlayerController* WJPC = Cast<AWJ_PlayerController>(PC);

	if (WJPC)
	{
		WJPC->DisconnectingActor();
	}
}
