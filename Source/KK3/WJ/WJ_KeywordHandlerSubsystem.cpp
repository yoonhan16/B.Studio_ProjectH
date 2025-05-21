// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_KeywordHandlerSubsystem.h"
#include "WJ_RichTextKeywordHandler.h"
#include "Engine/Engine.h"

void UWJ_KeywordHandlerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("KeywordHandlerSubsystem initialized."));

	Handler = NewObject<UWJ_RichTextKeywordHandler>(this);

	if (!Handler)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create KeywordHandler instance!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Handler created successfully"));
		Handler->InitializeDummyData();
	}

}
