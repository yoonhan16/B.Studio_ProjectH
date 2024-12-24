// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WJ_ItemStruct.h"
#include "WJ_ClueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KK3_API UWJ_ClueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWJ_ClueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Blueprintreadwrite)
	TArray<FSlotStruct> ClueStruct;

	UPROPERTY(EditAnywhere, Blueprintreadwrite)
	TArray<FSlotStruct> AllClues;

	UFUNCTION(BlueprintCallable)
	void CombinateClue();

	UFUNCTION(BlueprintCallable)
	void GetNewClue();

	UFUNCTION(BlueprintCallable)
	TArray<FSlotStruct> GetClueStruct();
};
