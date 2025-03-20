// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_ItemStruct.h"
#include "WJ_Object.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_Object : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> Scripts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWJ_Widget* ParentWidget;
};
