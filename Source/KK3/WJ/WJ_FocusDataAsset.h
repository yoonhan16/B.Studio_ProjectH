// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputSubsystems.h"
#include "WJ_FocusDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_FocusDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Observe;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Look;

};
