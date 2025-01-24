// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Widgets/WJ_InteractingWidget.h"
#include "../Widgets/WJ_InvestigatingWidget.h"
#include "../WJ_ItemStruct.h"
#include "WJ_InteractionActor.generated.h"

UCLASS()
class KK3_API AWJ_InteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_InteractionActor();

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USpringArmComponent*> CameraPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPrimitiveComponent*> TargetComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWJ_Widget* IsFocusWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStruct ItemStruct;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWJ_Widget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* GuideWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	TSubclassOf<UWJ_InvestigatingWidget> InvestigatingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	UWJ_InvestigatingWidget* InvestigatingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	TSubclassOf<UWJ_InteractingWidget> InteractingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	UWJ_InteractingWidget* InteractingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProgressiveNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, bool> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFocused;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	bool bIsChecked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	bool bIsTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FClueStruct> ClueStructs;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated)
	TArray<FOptionalDescriptions> OptionalDescriptions;
public:

	UFUNCTION(BlueprintCallable)
	void Interacting();

	UFUNCTION(BlueprintCallable)
	void Investigating();

	UFUNCTION()
	void UpdateInvestigatingWidget(int ComponentNumber, bool bVisible);

	UFUNCTION()
	void GetComponentIndex();

	UFUNCTION(BlueprintCallable)
	void IsFocus();

	UFUNCTION(BlueprintCallable)
	void IsNotFocus();

	UFUNCTION(BlueprintCallable)
	void Connect();

	UFUNCTION(BlueprintCallable)
	void Disconnect();

	UFUNCTION(BlueprintCallable)
	void SetGuideVisible(bool Visibillity);

	UFUNCTION(BlueprintCallable)
	bool GetIsCanInteract();

	UFUNCTION(BlueprintCallable)
	void SetInteractPossible();

	UFUNCTION(BlueprintCallable)
	void SetInteractImPossible();

	UFUNCTION(BlueprintCallable)
	void SetIsCanInteract(bool NewValue);

	UFUNCTION(BlueprintCallable)
	void IsCanInteract();

	UFUNCTION(Server, Reliable, WithValidation) // = Replicated ÇÏ°Ú´Ù.
	void Server_IsCanInteract();
	bool Server_IsCanInteract_Validate();
	void Server_IsCanInteract_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multicast_IsCanInteract();
	bool Multicast_IsCanInteract_Validate();
	void Multicast_IsCanInteract_Implementation();

protected:

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	class AWJ_Character* OverlapedCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	bool IsFocused = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	UFUNCTION(BlueprintCallable)
	TMap<FString, bool> GetActions();


	// Struct index used to add listview item , bool used to change script texts detail.
	UFUNCTION(BlueprintCallable)
	TArray<FClueStruct> GetClueStructs();

	UFUNCTION(BlueprintCallable)
	void SetIsFocused(bool bFocused);

	UFUNCTION(BlueprintCallable)
	void SetWidgetVisible();

	UFUNCTION(BlueprintCallable)
	void SetRenderCustomDepth();

	UFUNCTION(BlueprintCallable)
	void SetWidgetPercentage(float Percent);

protected:

	int32 Count;

	FTimerHandle CountTimerHandle;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateTimer();

	UFUNCTION(BlueprintCallable)
	void AdvanceTimer();

	UFUNCTION(BlueprintCallable)
	void CountFinished();

	UFUNCTION(BlueprintCallable)
	bool GetIsChecked();

	UFUNCTION(BlueprintCallable)
	void SetIsChecked();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetIsChecked();
	bool Server_SetIsChecked_Validate();
	void Server_SetIsChecked_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multicast_SetIsChecked();
	bool Multicast_SetIsChecked_Validate();
	void Multicast_SetIsChecked_Implementation();

	UFUNCTION(BlueprintCallable)
	void SetIsTest(bool IsTest);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetIsTest(bool IsTest);
	bool Server_SetIsTest_Validate(bool IsTest);
	void Server_SetIsTest_Implementation(bool IsTest);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multicast_SetIsTest(bool IsTest);
	bool Multicast_SetIsTest_Validate(bool IsTest);
	void Multicast_SetIsTest_Implementation(bool IsTest);
};
