// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WJ_ItemStruct.h"
#include "WJ_PlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	None UMETA(DisplayName = "None"),
	Detactor UMETA(DisplayName = "Detactor"),
	Negotiator UMETA(DisplayName = "Negotiator")
};

UCLASS()
class KK3_API AWJ_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<class AWJ_InteractionActor*> ActorProcedure;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	class AWJ_ArrayActor* ArrayActor;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated)
	int32 PlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated)
	FString PlayerRole;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated)
	TArray<FItemCheckerStruct> ItemChecker;

	// Include all clue this array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<FLinkedClue> AllClueList;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateClue(int32 ClueIndex);

	UFUNCTION(BlueprintCallable)
	void ActivateClue(int32 ClueIndex);

	UFUNCTION(BlueprintCallable)
	void AddActorProcedure(AWJ_InteractionActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetActorProcedure();

	UFUNCTION(BlueprintCallable)
	void CopyArrayActor();

	UFUNCTION(BlueprintCallable)
	void SetActorGuide(int32 Index, bool Visibillity);

	UFUNCTION(BlueprintCallable)
	bool CheckLocalPlayer();

	UFUNCTION(BlueprintCallable)
	void GetStateName();

	// Set Index to identify Players together
	UFUNCTION(BlueprintCallable)
	void SetPlayerIndex(int32 NewIndex);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetPlayerIndex(int32 NewIndex);
	bool Server_SetPlayerIndex_Validate(int32 NewIndex);
	void Server_SetPlayerIndex_Implementation(int32 NewIndex);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetPlayerIndex(int32 NewIndex);
	bool Multi_SetPlayerIndex_Validate(int32 NewIndex);
	void Multi_SetPlayerIndex_Implementation(int32 NewIndex);

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerIndex();

	// PlayerRole used to check other players role for proper operation
	UFUNCTION(BlueprintCallable)
	void SetPlayerRole(const FString& NewRole);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetPlayerRole(const FString& NewRole);
	bool Server_SetPlayerRole_Validate(const FString& NewRole);
	void Server_SetPlayerRole_Implementation(const FString& NewRole);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetPlayerRole(const FString& NewRole);
	bool Multi_SetPlayerRole_Validate(const FString& NewRole);
	void Multi_SetPlayerRole_Implementation(const FString& NewRole);

	UFUNCTION(BlueprintCallable)
	FString GetPlayerRole();

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString& NewName);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetPlayerName(const FString& NewName);
	bool Server_SetPlayerName_Validate(const FString& NewName);
	void Server_SetPlayerName_Implementation(const FString& NewName);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetPlayerName(const FString& NewName);
	bool Multi_SetPlayerName_Validate(const FString& NewName);
	void Multi_SetPlayerName_Implementation(const FString& NewName);

	UFUNCTION(BlueprintCallable)
	void SetItemChecker(const TArray<FItemCheckerStruct>& NewItems);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetItemChecker(const TArray<FItemCheckerStruct>& NewItems);
	bool Server_SetItemChecker_Validate(const TArray<FItemCheckerStruct>& NewItems);
	void Server_SetItemChecker_Implementation(const TArray<FItemCheckerStruct>& NewItems);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetItemChecker(const TArray<FItemCheckerStruct>& NewItems);
	bool Multi_SetItemChecker_Validate(const TArray<FItemCheckerStruct>& NewItems);
	void Multi_SetItemChecker_Implementation(const TArray<FItemCheckerStruct>& NewItems);

	UFUNCTION(BlueprintCallable)
	void SetItemChecked(int32 ItemIndex, bool ItemChecked);

	UFUNCTION(BlueprintCallable)
	void AddItemChecker(FItemCheckerStruct NewItem);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddItemChecker(FItemCheckerStruct NewItem);
	bool Server_AddItemChecker_Validate(FItemCheckerStruct NewItem);
	void Server_AddItemChecker_Implementation(FItemCheckerStruct NewItem);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_AddItemChecker(FItemCheckerStruct NewItem);
	bool Multi_AddItemChecker_Validate(FItemCheckerStruct NewItem);
	void Multi_AddItemChecker_Implementation(FItemCheckerStruct NewItem);
};
