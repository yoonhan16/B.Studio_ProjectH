// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WJ_TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KK3_API UWJ_TraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWJ_TraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	APlayerCameraManager* PlayerCameraManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AWJ_InteractionActor* InteractionActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWJ_InteractionActor*> NearInteractActors;

	UFUNCTION(BlueprintCallable)
	void Trace();

public:
	UFUNCTION(BlueprintCallable)
	AWJ_InteractionActor* GetInteractionActor();
	
	UFUNCTION(BlueprintCallable)
	void AddNearActor(AWJ_InteractionActor* NewActor);

	UFUNCTION(BlueprintCallable)
	bool GetIsNearActor(AWJ_InteractionActor* NewActor);
};
