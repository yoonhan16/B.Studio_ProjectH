// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_PlayerState.h"
#include "WJ_PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/WJ_ArrayActor.h"
#include "Actors/WJ_InteractionActor.h"

void AWJ_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	auto AA = UGameplayStatics::GetActorOfClass(GetWorld(), AWJ_ArrayActor::StaticClass());

	ArrayActor = Cast<AWJ_ArrayActor>(AA);

	CopyArrayActor();

	SetActorGuide(0, true);

	bReplicates = true;
}

void AWJ_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_PlayerState, PlayerIndex);
	DOREPLIFETIME(AWJ_PlayerState, PlayerRole);
	DOREPLIFETIME(AWJ_PlayerState, ItemChecker);
}

void AWJ_PlayerState::InitializeClueMap()
{
	ClueIndexMap.Empty();

	for (int32 i = 0; i < ClueDatabase.Num(); i++)
	{
		ClueIndexMap.Add(ClueDatabase[i].ClueID, i);
	}
}

void AWJ_PlayerState::UpdateClue(int32 ClueID)
{
	if (!ClueIndexMap.Contains(ClueID))
	{
		return;
	}

	int32 ClueIndex = ClueIndexMap[ClueID];
	FLinkedClue& CurrentClue = ClueDatabase[ClueIndex];

	for (int32 NextClueID : CurrentClue.AfterClueList)
	{
		if (!ClueIndexMap.Contains(NextClueID))
		{
			continue;
		}

		int32 NextClueIndex = ClueIndexMap[NextClueID];
		FLinkedClue& NextClue = ClueDatabase[NextClueIndex];
		NextClue.BeforeCluesCheck++;

		if ((NextClue.BeforeCluesCheck >= NextClue.BeforeClueList.Num()) && NextClue.bIsAutoActive)
		{
			ActivateClue(NextClueID);
		}
	}
}

void AWJ_PlayerState::ActivateClue(int32 ClueID)
{
	if (!ClueIndexMap.Contains(ClueID)) return;

	int32 ClueIndex = ClueIndexMap[ClueID];
	FLinkedClue& Clue = ClueDatabase[ClueIndex];
	
	if (Clue.bIsActive) return;

	Clue.bIsActive = true;

	UpdateClue(ClueID);
}

void AWJ_PlayerState::AddActorProcedure(AWJ_InteractionActor* Actor)
{
	ActorProcedure.AddUnique(Actor);
}

void AWJ_PlayerState::SetActorProcedure()
{
}

void AWJ_PlayerState::CopyArrayActor()
{
	if (ArrayActor)
	{
		ActorProcedure = ArrayActor->GetArrayActors();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("CopyArrayActor Called!"));
	}
}

void AWJ_PlayerState::SetActorGuide(int32 Index, bool Visibillity)
{
	if (ActorProcedure.Num() > Index)
	{
		ActorProcedure[Index]->SetGuideVisible(Visibillity);
	}
}

bool AWJ_PlayerState::CheckLocalPlayer()
{
	return false;
}

void AWJ_PlayerState::GetStateName()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("This Playerstate Name is : %s"), *this->GetName()));
	
	AWJ_PlayerController* WJ_PC = Cast<AWJ_PlayerController>(GetPlayerController());

	if(WJ_PC)
	{
		//PlayerIndex = WJ_PC->GetPlayerIndex();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Index is : %d"), WJ_PC->GetPlayerIndex()));
	}
}

void AWJ_PlayerState::SetPlayerIndex(int32 NewIndex)
{
	if (HasAuthority())
	{
		Multi_SetPlayerIndex(NewIndex);
	}
	else
	{
		Server_SetPlayerIndex(NewIndex);
	}
}

bool AWJ_PlayerState::Server_SetPlayerIndex_Validate(int32 NewIndex)
{
	return true;
}

void AWJ_PlayerState::Server_SetPlayerIndex_Implementation(int32 NewIndex)
{
	Multi_SetPlayerIndex(NewIndex);
}

bool AWJ_PlayerState::Multi_SetPlayerIndex_Validate(int32 NewIndex)
{
	return true;
}

void AWJ_PlayerState::Multi_SetPlayerIndex_Implementation(int32 NewIndex)
{
	PlayerIndex = NewIndex;
}

int32 AWJ_PlayerState::GetPlayerIndex()
{
	return PlayerIndex;
}

void AWJ_PlayerState::SetPlayerRole(const FString& NewRole)
{
	if (HasAuthority())
	{
		Multi_SetPlayerRole(NewRole);
	}
	else
	{
		Server_SetPlayerRole(NewRole);
	}
}

bool AWJ_PlayerState::Server_SetPlayerRole_Validate(const FString& NewRole)
{
	return true;
}

void AWJ_PlayerState::Server_SetPlayerRole_Implementation(const FString& NewRole)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Server Function is Called"));
	Multi_SetPlayerRole(NewRole);
}

bool AWJ_PlayerState::Multi_SetPlayerRole_Validate(const FString& NewRole)
{
	return true;
}

void AWJ_PlayerState::Multi_SetPlayerRole_Implementation(const FString& NewRole)
{
	PlayerRole = NewRole;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Multi Function is Called, NewRole is : %s"), *PlayerRole));

}

FString AWJ_PlayerState::GetPlayerRole()
{
	return PlayerRole;
}

void AWJ_PlayerState::SetPlayerName(const FString& NewName)
{
	if (HasAuthority())
	{
		Multi_SetPlayerName(NewName);
	}
	else
	{
		Server_SetPlayerName(NewName);
	}
}

bool AWJ_PlayerState::Server_SetPlayerName_Validate(const FString& NewName)
{
	return true;
}

void AWJ_PlayerState::Server_SetPlayerName_Implementation(const FString& NewName)
{
	Multi_SetPlayerName(NewName);
}

bool AWJ_PlayerState::Multi_SetPlayerName_Validate(const FString& NewName)
{
	return true;
}

void AWJ_PlayerState::Multi_SetPlayerName_Implementation(const FString& NewName)
{
	PlayerName = NewName;
}

void AWJ_PlayerState::SetItemChecker(const TArray<FItemCheckerStruct>& NewItems)
{
	if (HasAuthority())
	{
		Multi_SetItemChecker(NewItems);
	}
	else
	{
		Server_SetItemChecker(NewItems);
	}
}

bool AWJ_PlayerState::Server_SetItemChecker_Validate(const TArray<FItemCheckerStruct>& NewItems)
{
	return true;
}

void AWJ_PlayerState::Server_SetItemChecker_Implementation(const TArray<FItemCheckerStruct>& NewItems)
{
	Multi_SetItemChecker(NewItems);
}

bool AWJ_PlayerState::Multi_SetItemChecker_Validate(const TArray<FItemCheckerStruct>& NewItems)
{
	return true;
}

void AWJ_PlayerState::Multi_SetItemChecker_Implementation(const TArray<FItemCheckerStruct>& NewItems)
{
	ItemChecker = NewItems;
}

void AWJ_PlayerState::SetItemChecked(int32 ItemIndex, bool ItemChecked)
{
	if (ItemChecker.Num() > ItemIndex)
	{
		ItemChecker[ItemIndex].IsChecked = ItemChecked;
	}
}

void AWJ_PlayerState::AddItemChecker(FItemCheckerStruct NewItem)
{
	if (HasAuthority())
	{
		Multi_AddItemChecker(NewItem);
	}
	else
	{
		Server_AddItemChecker(NewItem);
	}


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Array Item Num is : %d"), ItemChecker.Num()));
}

bool AWJ_PlayerState::Server_AddItemChecker_Validate(FItemCheckerStruct NewItem)
{
	return true;
}

void AWJ_PlayerState::Server_AddItemChecker_Implementation(FItemCheckerStruct NewItem)
{
	Multi_AddItemChecker(NewItem);
}

bool AWJ_PlayerState::Multi_AddItemChecker_Validate(FItemCheckerStruct NewItem)
{
	return true;
}

void AWJ_PlayerState::Multi_AddItemChecker_Implementation(FItemCheckerStruct NewItem)
{
	for (auto Item : ItemChecker)
	{
		if (Item.ItemStruct.Name.EqualTo(NewItem.ItemStruct.Name))
		{
			return;
		}
	}

	ItemChecker.Add(NewItem);

}
