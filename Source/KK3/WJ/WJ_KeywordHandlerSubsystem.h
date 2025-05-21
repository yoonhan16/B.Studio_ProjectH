// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WJ_KeywordHandlerSubsystem.generated.h"

/**
 * 
 */

class UWJ_RichTextKeywordHandler;

UCLASS()
class KK3_API UWJ_KeywordHandlerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	UWJ_RichTextKeywordHandler* GetHandler() const { return Handler; }


protected:
	UPROPERTY()
	UWJ_RichTextKeywordHandler* Handler = nullptr;

};
