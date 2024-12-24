// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_EntryObject.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_EntryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FText ItemDescription;
	
};
