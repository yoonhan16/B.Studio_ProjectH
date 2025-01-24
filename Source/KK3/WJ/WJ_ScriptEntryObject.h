// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_ItemStruct.h"
#include "WJ_ScriptEntryObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KK3_API UWJ_ScriptEntryObject : public UObject
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Scripts;

public:

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetScripts();

	UFUNCTION(BlueprintCallable)
	void SetScripts(TArray<FString> NewScripts);
};
