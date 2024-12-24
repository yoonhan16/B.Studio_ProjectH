// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RootComponent.h"

// Sets default values for this component's properties
UWJ_RootComponent::UWJ_RootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWJ_RootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWJ_RootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UWJ_RootComponent::ClueVaild(int ClueNum)
{
	if (CluesName.Num() > ClueNum)
	{
		return CluesCollect[ClueNum];
	}
	else
	{
		return false;
	}
}

void UWJ_RootComponent::AddClues(AWJ_InteractionActor* CurrentClue)
{
	if (CluesName.Contains(CurrentClue))
	{
		CluesName.AddUnique(CurrentClue);
		CluesCollect.Add(false);
	}
}

