// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ClueComponent.h"

// Sets default values for this component's properties
UWJ_ClueComponent::UWJ_ClueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWJ_ClueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWJ_ClueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWJ_ClueComponent::CombinateClue()
{
}

void UWJ_ClueComponent::GetNewClue()
{
}

TArray<FSlotStruct> UWJ_ClueComponent::GetClueStruct()
{
	return this->ClueStruct;
}
