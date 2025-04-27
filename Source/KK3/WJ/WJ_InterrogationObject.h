// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_ItemStruct.h"
#include "WJ_InterrogationObject.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_InterrogationObject : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInterrogationScriptEntry InterrogationData;
};
