// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_ArrayActor.generated.h"

UCLASS()
class KK3_API AWJ_ArrayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_ArrayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<class AWJ_InteractionActor*> Actors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<AWJ_InteractionActor*> GetArrayActors();
};
