// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_RichTextClickableDecorator.h"
#include "WJ_RichTextKeywordHandler.h"
#include "Framework/Text/ITextDecorator.h"
#include "Framework/Text/SlateHyperlinkRun.h"
#include "Framework/Text/ISlateRun.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Engine/Engine.h"

class FClickableTextDecorator : public ITextDecorator
{
public:
	FClickableTextDecorator(URichTextBlock* InOwner) : Owner(InOwner) {}

	FClickableTextDecorator(UWJ_RichTextKeywordHandler* InHandler) : KeywordHandler(InHandler)
	{

	}

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
	{
		return RunParseResult.Name == TEXT("clickable");
	}

	virtual TSharedRef<ISlateRun> Create(const TSharedRef<class FTextLayout>& TextLayout
		,const FTextRunParseResults& RunInfo, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style) override
	{
		FRunInfo FinalRunInfo(RunInfo.Name);

		for (const auto& Pair : RunInfo.MetaData)
		{
			const FString Key = Pair.Key;
			const FTextRange& Range = Pair.Value;
			const FString Value = OriginalText.Mid(Range.BeginIndex, Range.Len());

			FinalRunInfo.MetaData.Add(Key, Value);
		}

		const FTextRange Range = RunInfo.ContentRange;

		FText DisplayText = FText::FromString(OriginalText.Mid(RunInfo.ContentRange.BeginIndex, RunInfo.ContentRange.Len()));

		if (const FTextRange* FoundRange = RunInfo.MetaData.Find(TEXT("id")))
		{
			ClickedId = OriginalText.Mid(FoundRange->BeginIndex, FoundRange->Len());
		}
		else
		{
			ClickedId = TEXT("undefined");
		}

		const FHyperlinkStyle* HyperlinkStyle = &FCoreStyle::Get().GetWidgetStyle<FHyperlinkStyle>("Hyperlink");

		

		return FSlateHyperlinkRun::Create(FinalRunInfo, ModelText, *HyperlinkStyle, FSlateHyperlinkRun::FOnClick::CreateLambda([this](const FSlateHyperlinkRun::FMetadata& Metadata) {
			if (KeywordHandler && !ClickedId.IsEmpty())
			{
				KeywordHandler->HandleKeywordClicked(ClickedId);
			}
			}),
			FSlateHyperlinkRun::FOnGenerateTooltip(),
			FSlateHyperlinkRun::FOnGetTooltipText(), Range);
	}



	void OnClick(const FSlateHyperlinkRun& Run)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Clicked ID : %s"), *ClickedId));
		}
	}
private:
	URichTextBlock* Owner;

	FString ClickedId;

	UWJ_RichTextKeywordHandler* KeywordHandler = nullptr;
};

TSharedPtr<ITextDecorator> UWJ_RichTextClickableDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FClickableTextDecorator(InOwner));
}
