// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WJ_ItemStruct.h"
#include "WJ_ClueObject.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_ClueObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	FSlotStruct ClueStruct;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<UWJ_ClueObject*> BelongArray; 

	UFUNCTION(BlueprintCallable)
	void SetBelongArray(TArray<UWJ_ClueObject*> Array);

	UFUNCTION(BlueprintCallable)
	void UpdateClue(); 

	UFUNCTION(BlueprintCallable)
	void UpdateSelf(); 
	
	//UPROPERTY(EditAnywhere, BlueprintReadwrite)
	//TArray<ClueBox> ClueBoxs;
};
