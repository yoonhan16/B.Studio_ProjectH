// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Widgets/WJ_ActionsWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "WJ_FocusDataAsset.h"
#include "WJ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API AWJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AWJ_PlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void Look(const FInputActionValue& Value);
	void StopLook(const FInputActionValue& Value);
	void Observe(const FInputActionValue& Value);
	// To active after LinkSubsystem worked
	void FocusHold(const FInputActionInstance& Instance);
	void RequestPhaseChange(const FInputActionInstance& Instance);

	bool IsInteract;
	bool bIsComplete;
	bool bIsTest;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Index", Replicated)
	int32 PlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Name", Replicated)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* GDCMotionMatching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InteractMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* CameraActionMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* HoldAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraRotateAction;

	// not using function what replace down function with new structs
	UFUNCTION(BlueprintCallable)
	void SetActionWidget(AWJ_InteractionActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWJ_ActionsWidget> ActionsWidgetClass;

	UPROPERTY()
	UWJ_ActionsWidget* ActionsWidget;

	UFUNCTION(BlueprintCallable)
	UWJ_ActionsWidget* GetActionsWidget();

	UFUNCTION(BlueprintCallable)
	void InteractingActor();

	UFUNCTION(BlueprintCallable)
	void EndInteractingActor();

	UFUNCTION()
	void DisconnectingActor();

	UFUNCTION()
	void MultiInteractingActor();

	UFUNCTION(BlueprintCallable)
	void CheckCharacter();

	UFUNCTION()
	void CheckArray(int32 ProgressNum);

	void Focusing(const FInputActionValue& Value);
	void StopFocus(const FInputActionValue& Value);
	void MovingActor(const FInputActionValue& Value);
	void MovingMesh(const FInputActionValue& Value);

	void CameraMove(const FInputActionValue& Value);
	void CameraRotate(const FInputActionValue& Value);

	UCameraComponent* CurrentCamera;

	class AWJ_InteractionActor* InteractionActor; 
	class AWJ_MultiInteractionActor* MultiActor;
	class UWJ_InteractingWidget* InteractingWidget;

	class USpringArmComponent* IA_SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	USpringArmComponent* SpringArm_Character;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	UCameraComponent* Camera_Character;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> ProfilerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InvestigatorWidgetClass;

	UUserWidget* CurrentRoleWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UArrowComponent* Arrow_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera_Interact;

	bool bIsFocus;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	bool bIsReady;

	FVector CameraStartLoc;
	FVector CameraEndLoc;

	FRotator CameraStartRot;
	FRotator CameraEndRot;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	class UWJ_Widget* InEar_Widget;

	bool bIsGettingInfomation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSubmittedClue> ReceivedClues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWJ_ClueReceiveWidget* ClueReceiveWidget;
public:

	UFUNCTION(BlueprintCallable)
	bool GetIsReady();

	UFUNCTION(BlueprintCallable)
	void SetIsGettingInfomation(bool NewGetting);

	// To check all player is ready for phase change
	UFUNCTION(BlueprintCallable)
	void SequanceChangeReady();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SequanceChangeReady();
	bool Server_SequanceChangeReady_Validate();
	void Server_SequanceChangeReady_Implementation();

	UFUNCTION(BlueprintCallable)
	void LinkSubsystem();

	UFUNCTION(BlueprintCallable)
	void UnlinkSubsystem();

	// Change Camera and AddMapping for Camera After Interacting Complete
	UFUNCTION(BlueprintCallable)
	void Interact_Camera();

	UFUNCTION(BlueprintCallable)
	void GetPlayersNum();

	UFUNCTION(BlueprintCallable)
	void DialogTest();

	// Set Index to discrimination Players together
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
	void GetPlayerIndexGm();

	void SetPlayerControllerID(int32 NewID);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_CallInEar(AWJ_PlayerController* MyController);
	bool Server_CallInEar_Validate(AWJ_PlayerController* MyController);
	void Server_CallInEar_Implementation(AWJ_PlayerController* MyController);
	
	UFUNCTION(Client, Reliable, WithValidation)
	void Client_CallInEar();
	bool Client_CallInEar_Validate();
	void Client_CallInEar_Implementation();

	UFUNCTION(BlueprintCallable)
	void AddItemStruct(FItemStruct NewItemStruct);

	UFUNCTION(BlueprintCallable)
	void SubmitClueToProfiler(const FClueMessage& ClueMessage);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SubmitClueToProfiler(const FSubmittedClue& SubmittedClue);
	bool Server_SubmitClueToProfiler_Validate(const FSubmittedClue& SubmittedClue);
	void Server_SubmitClueToProfiler_Implementation(const FSubmittedClue& SubmittedClue);

	UFUNCTION(Client, Reliable, WithValidation)
	void Client_ReceiveClue(const FSubmittedClue& ReceivedClue);
	bool Client_ReceiveClue_Validate(const FSubmittedClue& ReceivedClue);
	void Client_ReceiveClue_Implementation(const FSubmittedClue& ReceivedClue);


	UFUNCTION(BlueprintCallable)
	FClueMessage CreateClueMessageFromClue(const FClueData& Clue, const FString& CustomDescription);

	UFUNCTION(BlueprintCallable)
	EPlayerRole GetPlayerRole() const;

	UFUNCTION(BlueprintCallable)
	void SwapPlayerRole();
};

