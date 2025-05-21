// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Framework/Text/ITextDecorator.h"
#include "Framework/Text/SlateHyperlinkRun.h"
#include "Framework/Text/ISlateRun.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Components/RichTextBlock.h"
#include "Engine/Engine.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UWJ_RichTextKeywordHandler;

class KK3_API FWJ_ClickableTextDecorator : public ITextDecorator
{

public:
	FWJ_ClickableTextDecorator() : Owner(nullptr) {};
	FWJ_ClickableTextDecorator(URichTextBlock* InOwner) : Owner(InOwner), KeywordId(TEXT("")) {}
	FWJ_ClickableTextDecorator(URichTextBlock* InOwner, const FString& InKeywordId) : Owner(InOwner), KeywordId(InKeywordId) {}
	FWJ_ClickableTextDecorator(URichTextBlock* InOwner, const FString& InKeywordId, UWJ_RichTextKeywordHandler* InKeywordHandler) : Owner(InOwner), KeywordId(InKeywordId), KeywordHandler(InKeywordHandler) {}

	virtual ~FWJ_ClickableTextDecorator() {}

protected:
	URichTextBlock* Owner;

	FString KeywordId;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	UWJ_RichTextKeywordHandler* KeywordHandler = nullptr;

public:

	virtual TSharedRef<ISlateRun> Create(const TSharedRef<class FTextLayout>& TextLayout
		, const FTextRunParseResults& RunInfo, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style) override;

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override;

};
