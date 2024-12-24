// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WJ_GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API AWJ_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:

	AWJ_GameStateBase();

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable)
	void GetPlayersNum();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class AWJ_InteractionActor*> ClueCheckList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<AWJ_PlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<AWJ_PlayerState*> PlayerStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> DialogList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> PlayerRoleList;
public:

	UFUNCTION(BlueprintCallable)
	bool GetClueCheck(int32 ClueNum);

	UFUNCTION(BlueprintCallable)
	void SetClueCheck(int32 ClueNum);

	UFUNCTION(BlueprintCallable)
	int32 GetClueCheckListNum();

	UFUNCTION(BlueprintCallable)
	void GetInteractionActors();

	UFUNCTION(BlueprintCallable)
	FText GetDialogText();

	UFUNCTION(BlueprintCallable)
	void AddPlayerControllers(AWJ_PlayerController* NewPC);

	UFUNCTION(BlueprintCallable)
	void AddPlayerStates(AWJ_PlayerState* NewPS);

	UFUNCTION(BlueprintCallable)
	void GetSequanceReady();

	UFUNCTION(BlueprintCallable)
	void SetPlayerIndex(class AWJ_PlayerState* WJ_PS);
};
