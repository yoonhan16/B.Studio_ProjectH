// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_ItemStruct.generated.h"

struct FActionRequirements;

UENUM(BlueprintType)
enum class EGamePlayMode : uint8
{
	Single UMETA(DisplayName = "SinglePlayer"),
	Multi UMETA(DisplayName = "MultiPlayer")
};


UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	None UMETA(DisplayName = "None"),
	Profiler UMETA(DisplayName = "Profiler"),
	Investigator UMETA(DisplayName = "Investigator")
};

UENUM(BlueprintType)
enum class EDialogueType : uint8
{
	Normal,
	End
};

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Dialogue,
	Investigation,
	SpecialEvent
};

UENUM(BlueprintType)
enum class EInterrogationMood : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Aggressive UMETA(DisplayName = "Aggressive"),
	Friendly UMETA(DisplayName = "Friendly"),
	Suspicious UMETA(DisplayName = "Suspicious")
	
};

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

// Not only using clue , but also using on branch and scripts
USTRUCT(Atomic, BlueprintType)
struct FLinkedClue
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClueName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClueDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAutoActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsKey = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BeforeCluesCheck = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> BeforeClueList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AfterClueList;
};

// To check what clue is available that each Interaction Actors
USTRUCT(Atomic, BlueprintType)
struct FActionRequirements
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> CheckList;
};

USTRUCT(Atomic, BlueprintType)
struct FDialogueEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueType DialogueType = EDialogueType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextIndex = -1;
};

USTRUCT(BlueprintType)
struct FActionEntry
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionType ActionType = EActionType::Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> Descriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRequiresCondition = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RequiredClues;
};

// Showing what player is able to action with that interaction actor
USTRUCT(Atomic, BlueprintType)
struct FActionScriptStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FActionEntry> ActionScripts;
};

USTRUCT(Atomic, BlueprintType)
struct FClueData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

};

USTRUCT(BlueprintType)
struct FClueMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClueTitle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SenderPlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime SentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReviewed = false;

};

USTRUCT(BlueprintType)
struct FSubmittedClue
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OriginalClueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SenderPlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConfirmed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime SubmittedAt;
};

USTRUCT(BlueprintType)
struct FInterrogationScriptEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialogueEntry Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> Descriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RequiredClues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInterrogationMood Mood = EInterrogationMood::Neutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRequiresCondition = false;

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
