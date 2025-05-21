// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_ItemStruct.h"
#include "WJ_KeywordStruct.generated.h"

/*
*
*/
UENUM(BlueprintType)
enum class EKeywordLinkType : uint8
{
	ClueList UMETA(DisplayName = "ClueList"),
	DialogueLog UMETA(DisplayName = "DialogueLog")
};

USTRUCT(BlueprintType)
struct FKeywordEntry : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeywordId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnlockClueId = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> TriggerdDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRequiresCondition = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RequiredClueIds;
};

UCLASS()
class KK3_API AWJ_KeywordStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_KeywordStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
