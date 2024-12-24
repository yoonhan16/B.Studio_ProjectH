// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "WJ_ActorComponent.h"
#include "../WJ_StaticMeshComponent.h"
#include "../Widgets/WJ_InteractingWidget.h"
#include "../Widgets/WJ_MultiInteractingWidget.h"
#include "WJ_MultiInteractionActor.generated.h"

UCLASS()
class KK3_API AWJ_MultiInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_MultiInteractionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWJ_ActorComponent* Clue01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<UWJ_StaticMeshComponent*> Clues;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* OverlapChecker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWJ_MultiInteractingWidget> MultiWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWJ_Character* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWJ_Character*> ConnectCharacters; 

	AWJ_Character* OverlapCharacter = nullptr;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UWJ_MultiInteractingWidget> GetInteractingWidget();

	UFUNCTION()
	bool GetContainComponent(UWJ_StaticMeshComponent* Component);

	UFUNCTION()
	void SetControlOwner(AWJ_Character* NewOwner);

	UFUNCTION(BlueprintCallable)
	void SetCharacterArray(AWJ_Character* NewCharacter);

	UFUNCTION(BlueprintCallable)
	void ComponentInteract(UWJ_StaticMeshComponent* TargetComponent);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RepComponentInteract(UWJ_StaticMeshComponent* TargetComponent);
	bool Server_RepComponentInteract_Validate(UWJ_StaticMeshComponent* TargetComponent);
	void Server_RepComponentInteract_Implementation(UWJ_StaticMeshComponent* TargetComponent);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_RepComponentInteract(UWJ_StaticMeshComponent* TargetComponent);
	bool Multi_RepComponentInteract_Validate(UWJ_StaticMeshComponent* TargetComponent);
	void Multi_RepComponentInteract_Implementation(UWJ_StaticMeshComponent* TargetComponent);
};
