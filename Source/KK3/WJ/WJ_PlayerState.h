// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WJ_PlayerState.generated.h"

/**
 * 
 */
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
public:
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

};
