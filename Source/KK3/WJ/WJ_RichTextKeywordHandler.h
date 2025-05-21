// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/RichTextBlock.h"
#include "Framework/Text/ITextDecorator.h"
#include "Framework/Text/SlateHyperlinkRun.h"
#include "Framework/Text/ISlateRun.h"
#include "WJ_ItemStruct.h"
#include "WJ_RichTextKeywordHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeywordClicked, const FString&, Keyword);

USTRUCT(BlueprintType)
struct FKeywordEventEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KeywordId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueEntry> TriggeredDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnlockClueId = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRequiresCondition = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RequiredClueIds;
};

/**
 * Handles keyword clicks inside RichTextBlock (e.g., <a href="keyword">text</a>)
 */
UCLASS(Blueprintable, BlueprintType)
class KK3_API UWJ_RichTextKeywordHandler : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Keyword")
	void BindTo(class URichTextBlock* TargetRichText);

	UPROPERTY(BlueprintAssignable)
	FOnKeywordClicked OnKeywordClickedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Keyword")
	TMap<FString, FKeywordEventEntry> KeywordEventMap;

	UFUNCTION(BlueprintCallable, Category = "Keyword")
	void HandleKeywordClicked(const FString& KeywordId);

	UPROPERTY()
	class AWJ_PlayerState* PlayerState = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Dummy")
	void InitializeDummyData();
protected:

	void HandleHyperlinkClicked(const FTextRunInfo& RunInfo);

	TSharedRef<ITextDecorator> MakeKeywordDecorator(URichTextBlock* Owner, const FString& KeywordId);


};
