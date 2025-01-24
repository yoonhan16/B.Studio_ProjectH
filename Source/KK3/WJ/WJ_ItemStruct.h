// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_ItemStruct.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FSlotStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DescriptionArray;

	FSlotStruct()
	{
		ItemID = "Defalut";
		Description = "Defalut";
	};
};

USTRUCT(Atomic, BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWJ_InteractionActor* ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize;

};

USTRUCT(Atomic, BlueprintType)
struct FOptionalDescriptions
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Descriptions;

};


USTRUCT(Atomic, BlueprintType)
struct FItemCheckerStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStruct ItemStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalDescriptions OptionalDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsChecked = false;
};

USTRUCT(Atomic, BlueprintType)
struct FClueStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClueNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsChecked = false;
};



UCLASS()
class KK3_API AWJ_ItemStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_ItemStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
