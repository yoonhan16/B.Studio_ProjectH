// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_GameModeBase.h"
#include "WJ_PlayerController.h"
#include "WJ_PlayerState.h"
#include "WJ_GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/WJ_Widget.h"

AWJ_GameModeBase::AWJ_GameModeBase()
{
	ProgressNum = 0;
}

void AWJ_GameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AWJ_PlayerController* CurrentPC = Cast<AWJ_PlayerController>(NewPlayer);

	if (CurrentPC)
	{
		PlayerControllers.AddUnique(CurrentPC);

		AWJ_GameStateBase* GS = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));	

		GS->AddPlayerControllers(CurrentPC);
		GS->GetPlayersNum();
		GS->GetSequanceReady();

		//CurrentPC->SetPlayerControllerID(PlayerControllers.Find(CurrentPC));

		CurrentPC->SetPlayerIndex(PlayerControllers.Find(CurrentPC));


		AWJ_PlayerState* CurrentPS = CurrentPC->GetPlayerState<AWJ_PlayerState>();

		if (CurrentPS)
		{
			GS->AddPlayerStates(CurrentPS);
			CurrentPS->SetPlayerIndex(PlayerControllers.Find(CurrentPC));
			CurrentPS->SetItemChecker(TestItems);
			//CurrentPS->SetItemChecked(PlayerControllers.Find(CurrentPC) , true);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Player Index is : %d"), PlayerControllers.Find(CurrentPC)));

		//AWJ_PlayerState* WJ_PS = CurrentPC->GetPlayerState<AWJ_PlayerState>();
		//if (WJ_PS)
		//{
		//	GS->SetPlayerIndex(WJ_PS);
		//}
	}
}

int32 AWJ_GameModeBase::GetProgressNum()
{
	return ProgressNum;
}

void AWJ_GameModeBase::SetProgressNum(int32 Num)
{
	ProgressNum = Num;
}

void AWJ_GameModeBase::SequanceChange(AWJ_PlayerController* CurrentPC)
{

}

void AWJ_GameModeBase::GetPlayersReady()
{
	int32 PCNum = 0;
	int32 trueNum = 0;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AWJ_PlayerController* PC = Cast<AWJ_PlayerController>(It->Get());

		if (PC)
		{
			PCNum = PCNum + 1;

			if (PC->GetIsReady())
			{
				trueNum = trueNum + 1;
			}
		}
	}

}

void AWJ_GameModeBase::CountStart(float Count, float Cycle)
{
	CountTime = Count;
	CycleTime = Cycle;

	GetWorldTimerManager().SetTimer(CountTimerHandle, this, &AWJ_GameModeBase::AdvanceTimer, CycleTime);

}

void AWJ_GameModeBase::UpdateTimer()
{
}

void AWJ_GameModeBase::AdvanceTimer()
{
	CountTime = CountTime - CycleTime;
	UpdateTimer();

	if (CountTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountTimerHandle);
		FinishTimer();
	}
}

void AWJ_GameModeBase::FinishTimer()
{
}

void AWJ_GameModeBase::UpdateCountWidget()
{
	if (CountWidget)
	{
		float CountPercent = CountTime / MaxTime;

		CountWidget->SetProgressPercent(CountPercent);
	}
}

void AWJ_GameModeBase::SequanceChangeCheck()
{



}

int32 AWJ_GameModeBase::GetPlayerIndex(APlayerController* PC)
{
	AWJ_PlayerController* WJ_PC = Cast<AWJ_PlayerController>(PC);

	if (PlayerControllers.Contains(WJ_PC))
	{
		return PlayerControllers.Find(WJ_PC);
	}
	else
	{
		return -1;
	}
}
