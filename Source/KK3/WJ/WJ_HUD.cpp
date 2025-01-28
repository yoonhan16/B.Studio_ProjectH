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
	if (Interaction_ActionScriptWidget)
	{
		ActorInterfaceWidget = Cast<UWJ_Widget>(Interaction_ActionScriptWidget);
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

void AWJ_HUD::ShowGettingInfomation()
{
	if(GettingInfomationWidget)
	{
		UWJ_Widget* GIWidget = CreateWidget<UWJ_Widget>(GetWorld(), GettingInfomationWidget);
		GIWidget->AddToViewport();
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
	if (InformationWidget)
	{
		InformationWidget->RemoveFromParent();
	}


	if (InfomationWidgetClass)
	{
		InformationWidget = Cast<UWJ_Widget>(CreateWidget(GetWorld(), InfomationWidgetClass));

		if (InformationWidget)
		{
			AWJ_GameStateBase* GSB = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

			InformationWidget->SetDescriptionText(GSB->GetDialogText());

			InformationWidget->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RevealInfomation is Called!"));
		}
	}
}

void AWJ_HUD::SetInfomation(FText Info)
{
	if (InformationWidget)
	{
		InformationWidget->SetDescriptionText(Info);
	}

}
