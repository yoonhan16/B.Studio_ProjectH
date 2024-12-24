// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "WJ_PlayerController.h"
#include "WJ_PlayerState.h"
#include "Actors/WJ_InteractionActor.h"

AWJ_GameStateBase::AWJ_GameStateBase()
{
	FString DefaultString = FString(TEXT("Default"));
	FText DefaultText = FText::FromString(DefaultString);

	bReplicates = true;

	for (int i = 0; i < 6; ++i)
	{
		
		DialogList.Add(DefaultText);
	}
}

void AWJ_GameStateBase::BeginPlay()
{
	Super::BeginPlay();

	GetInteractionActors();
}

void AWJ_GameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_GameStateBase, PlayerControllers);
	DOREPLIFETIME(AWJ_GameStateBase, PlayerStates);
}

void AWJ_GameStateBase::GetPlayersNum()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Players Num is : %s"), *FString::FromInt(PlayerArray.Num())));
}

bool AWJ_GameStateBase::GetClueCheck(int32 ClueNum)
{
	if (ClueCheckList.Num() > ClueNum)
	{
		return ClueCheckList[ClueNum]->GetIsChecked();
	}

	return false;
}

void AWJ_GameStateBase::SetClueCheck(int32 ClueNum)
{
	if (ClueCheckList.Num() > ClueNum)
	{
		ClueCheckList[ClueNum]->SetIsChecked();
	}
}

int32 AWJ_GameStateBase::GetClueCheckListNum()
{
	return ClueCheckList.Num();
}

void AWJ_GameStateBase::GetInteractionActors()
{
	TArray<AActor*> MyActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_InteractionActor::StaticClass(), MyActors);

	if (MyActors.Num() > 0)
	{
		for (AActor* Actor : MyActors)
		{
			AWJ_InteractionActor* IA = Cast<AWJ_InteractionActor>(Actor);

			ClueCheckList.AddUnique(IA);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Actor Name : %s"), *(IA->GetName())));
		}
	}
}

FText AWJ_GameStateBase::GetDialogText()
{
	if (GetClueCheck(0))
	{
		if (GetClueCheck(1))
		{
			if (GetClueCheck(2))
			{
				return DialogList[5];
			}
			else
			{
				return DialogList[4];
			}
		}
		else if(GetClueCheck(2))
		{
			return DialogList[3];
		}
		
		return DialogList[2];
	}
	else
	{
		return DialogList[0];
	}


}

void AWJ_GameStateBase::AddPlayerControllers(AWJ_PlayerController* NewPC)
{
	PlayerControllers.AddUnique(NewPC);
}

void AWJ_GameStateBase::AddPlayerStates(AWJ_PlayerState* NewPS)
{
	PlayerStates.AddUnique(NewPS);
}

void AWJ_GameStateBase::GetSequanceReady()
{
	int32 Number = 0;

	for (APlayerState* Player : PlayerArray)
	{

		if(Player)
		{
			AWJ_PlayerState* PS = Cast<AWJ_PlayerState>(Player);
			if (PS) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Name is : %s"), *PS->GetName()));

			}
		}
	}
}

void AWJ_GameStateBase::SetPlayerIndex(AWJ_PlayerState* WJ_PS)
{
	WJ_PS->SetPlayerIndex(PlayerArray.Num() - 1);

}

