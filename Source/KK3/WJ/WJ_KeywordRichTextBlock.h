// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"
#include "WJ_KeywordRichTextBlock.generated.h"

/**
 * 
 */
class UWJ_RichTextKeywordHandler;

UCLASS()
class KK3_API UWJ_KeywordRichTextBlock : public URichTextBlock
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWJ_RichTextKeywordHandler* KeywordHandler = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> KeywordIds;

protected:
	virtual void CreateDecorators(TArray<TSharedRef<ITextDecorator>>& OutDecorators) override;
};
