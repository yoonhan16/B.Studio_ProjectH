// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_ItemEntryObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KK3_API UWJ_ItemEntryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FText ItemDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWJ_InteractionActor* ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsChecked;
};
