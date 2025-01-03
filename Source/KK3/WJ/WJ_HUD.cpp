// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/WJ_WIdget.h"
#include "WJ_GameStateBase.h"

AWJ_HUD::AWJ_HUD()
{
	ActorInterfaceWidget = nullptr;
}

void AWJ_HUD::BeginPlay()
{
	Super::BeginPlay();

}

void AWJ_HUD::SetInteractionWidget()
{
	if (InteractionInterfaceWidget)
	{
		ActorInterfaceWidget = Cast<UWJ_Widget>(InteractionInterfaceWidget);
	}
}

void AWJ_HUD::SetActorInterfaceWidget(UWJ_Widget* CurrentWidget)
{
	ActorInterfaceWidget = CurrentWidget;
}

void AWJ_HUD::SetWidgetText(FText NewText)
{
	if (ActorInterfaceWidget)
	{
		ActorInterfaceWidget->SetDescriptionText(NewText);
	}
}

void AWJ_HUD::SetActionListWidget(TMap<FString, bool> CurrentActions)
{
	if (ActionListWidget)
	{
		UWJ_ActionListWidget* AL = Cast<UWJ_ActionListWidget>(ActionListWidget);

		if (AL)
		{
			AL->SetActions(CurrentActions);
			AL->SetActionList();
		}
	}
}

void AWJ_HUD::SetProgressPercent(float Percent)
{
	if (MouseFocusWidget)
	{
		MouseFocusWidget->SetProgressPercent(Percent);
	}
}

void AWJ_HUD::UpdatePhaseChecker()
{
	if (PhaseCheckerWidget)
	{
		//PhaseCheckerWidget->Phase
	}
}

void AWJ_HUD::CallPhaseChange()
{
}

void AWJ_HUD::RevealInfomation()
{
	if (InfomationWidget)
	{
		InfomationWidget->RemoveFromParent();
	}


	if (InfomationWidgetClass)
	{
		InfomationWidget = Cast<UWJ_Widget>(CreateWidget(GetWorld(), InfomationWidgetClass));

		if (InfomationWidget)
		{
			AWJ_GameStateBase* GSB = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

			InfomationWidget->SetDescriptionText(GSB->GetDialogText());

			InfomationWidget->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RevealInfomation is Called!"));
		}
	}
}

void AWJ_HUD::SetInfomation(FText Info)
{
	if (InfomationWidget)
	{
		InfomationWidget->SetDescriptionText(Info);
	}

}
