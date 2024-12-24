// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Actors/WJ_Actor.h"
#include "Actors/WJ_InteractionActor.h"
#include "Actors/WJ_MultiInteractionActor.h"
#include "Widgets/WJ_Widget.h"
#include "WJ_TraceComponent.h"
#include "WJ_EmptyComponent.h"
#include "WJ_ClueComponent.h"
#include "WJ_ItemStruct.h"
#include "WJ_Character.generated.h"

class UWJ_ClueObject;

UCLASS()
class KK3_API AWJ_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWJ_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* CurrentCameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UArrowComponent* CurrentArrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWJ_TraceComponent* TraceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* Arrow_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera_Interact;

	UFUNCTION()
	void CanInteract();

	UFUNCTION()
	void CannotInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCanInvestigate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCanMultiInteract;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWJ_InteractionActor* InteractionActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWJ_InteractionActor* SeeActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWJ_InteractionActor* IA;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWJ_MultiInteractionActor* MultiInteractionActor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWJ_Widget* MousepointWidget = nullptr;

	UFUNCTION(BlueprintCallable)
	void Interacting();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interacting(AWJ_InteractionActor* WJIA);
	bool Server_Interacting_Validate(AWJ_InteractionActor* WJIA);
	void Server_Interacting_Implementation(AWJ_InteractionActor* WJIA);

	UFUNCTION(BlueprintCallable)
	void EndInteracting();

	UFUNCTION(BlueprintCallable)
	void Investigating();

	UFUNCTION(BlueprintCallable)
	void EndInvestigating();

	UFUNCTION(BlueprintCallable)
	void NoticeMultiActor();

	UFUNCTION(BlueprintCallable)
	void MultiInteracting();

	UFUNCTION(BlueprintCallable)
	void InteractToComponent();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_InteractToComponent(UWJ_StaticMeshComponent* Component);
	bool Server_InteractToComponent_Validate(UWJ_StaticMeshComponent* Component);
	void Server_InteractToComponent_Implementation(UWJ_StaticMeshComponent* Component);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFocus;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MovingCameraTimelineFloatCurve;

	UPROPERTY(EditAnywhere)
	bool bIsCrouch;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsTestOverlaped;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWJ_InteractionActor*> CanInteractActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWJ_InteractionActor* FocusActor;

	FOnTimelineFloat UpdateFunctionFloat;

	FOnTimelineEvent CurveFinishedCallback;

	UFUNCTION(BlueprintCallable)
	void SetFocusActor();

	UFUNCTION()
	void UpdateTimelineComp(float Output);

	UFUNCTION()
	void UpdateComponentReference(UPrimitiveComponent* Component);

	UFUNCTION()
	void TimelineFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* MovingCameraTimeline;

	FTimeline CurveFTimeline;

	FVector CameraStartLoc;
	FVector CameraEndLoc;

	FRotator CameraStartRot;
	FRotator CameraEndRot;

	TArray<UPrimitiveComponent*> TargetComponents;

	UPrimitiveComponent* CurrentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEndInteract;

private:

public:

	UFUNCTION(BlueprintCallable)
	void AddInteractActor(AWJ_InteractionActor* NewActor);

	UFUNCTION(BlueprintCallable)
	void RemoveInteractActor(AWJ_InteractionActor* NewActor);

	FVector OriginLoc;
	FRotator OriginRot;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<UWJ_ClueObject*> Clues;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TSubclassOf<AActor> TestActor;

	UFUNCTION(BlueprintCallable)
	void SpawnItem();

	UFUNCTION(BlueprintCallable)
	void RepTestTrue();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RepTestTrue(AWJ_Actor* Actor);
	bool Server_RepTestTrue_Validate(AWJ_Actor* Actor);
	void Server_RepTestTrue_Implementation(AWJ_Actor* Actor);

	//UFUNCTION(BlueprintCallable)
	//void RepTestFalse();

	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_RepTestFalse(AWJ_Actor* Actor);
	//bool Server_RepTestFalse_Validate(AWJ_Actor* Actor);
	//void Server_RepTestFalse_Implementation(AWJ_Actor* Actor);

	UFUNCTION()
	void GetMultiActorControl();

	UFUNCTION()
	void CheckArrayActor(int32 ProgressNum);

	UFUNCTION(BlueprintCallable)
	void SetIsCrouch(AActor* IActor);

	UFUNCTION(BlueprintCallable)
	bool GetIsCrouch();

	UFUNCTION(BlueprintCallable)
	void FocusHold();

	UFUNCTION(BlueprintCallable)
	void SetupInteractionTrace();

	UFUNCTION(BlueprintCallable)
	void DialogTest();
};
