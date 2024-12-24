// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/WJ_InteractionActor.h"
#include "WJ_RootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KK3_API UWJ_RootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWJ_RootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWJ_InteractionActor* CurrentActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWJ_InteractionActor*> CluesName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> CluesCollect;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	bool ClueVaild(int ClueNum);

	UFUNCTION(BlueprintCallable)
	void AddClues(AWJ_InteractionActor* CurrentClue);

};
