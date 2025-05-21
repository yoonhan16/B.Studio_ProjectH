// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ClickableTextDecorator.h"
#include "WJ_RichTextKeywordHandler.h"



TSharedRef<ISlateRun> FWJ_ClickableTextDecorator::Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunInfo, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style)
{
    UE_LOG(LogTemp, Warning, TEXT("Create() for KeywordId=%s"), *KeywordId);

    // 1) RunInfo 복사 및 MetaData 문자열화
    FRunInfo FinalRunInfo(RunInfo.Name);
    for (const auto& Pair : RunInfo.MetaData)
    {
        const FString& Key = Pair.Key;
        const FTextRange& Range = Pair.Value;
        const FString Value = OriginalText.Mid(Range.BeginIndex, Range.Len());
        FinalRunInfo.MetaData.Add(Key, Value);
    }

    // 2) 클릭 ID 할당 (MetaData의 id 속성)
    const FString ClickedId = RunInfo.MetaData.Contains(TEXT("id"))
        ? FinalRunInfo.MetaData[TEXT("id")]
        : TEXT("undefined");

    // 3) 표시할 텍스트 범위
    const FTextRange& ContentRange = RunInfo.ContentRange;
    FText DisplayText = FText::FromString(OriginalText.Mid(ContentRange.BeginIndex, ContentRange.Len()));

    // 4) 하이퍼링크 스타일 구하기
    const FHyperlinkStyle& HyperlinkStyle = FCoreStyle::Get().GetWidgetStyle<FHyperlinkStyle>("Hyperlink");

    // 5) FSlateHyperlinkRun 생성 및 클릭 바인딩
    return FSlateHyperlinkRun::Create(
        FinalRunInfo,
        ModelText,
        HyperlinkStyle,
        FSlateHyperlinkRun::FOnClick::CreateLambda([this, ClickedId](const FSlateHyperlinkRun::FMetadata& Metadata)
            {
                if (KeywordHandler && !ClickedId.IsEmpty())
                {
                    KeywordHandler->HandleKeywordClicked(ClickedId);
                }
            }),
        FSlateHyperlinkRun::FOnGenerateTooltip(),
        FSlateHyperlinkRun::FOnGetTooltipText(),
        ContentRange
    );
}

bool FWJ_ClickableTextDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
    UE_LOG(LogTemp, Warning, TEXT("Supports() name=%s  text=%s"), *RunParseResult.Name, *Text);

    // 1) 태그가 <a> 가 맞는지 체크
    if (RunParseResult.Name != TEXT("a"))
    {
        return false;
    }

    // 2) MetaData에서 "id" 범위를 꺼내기
    const FTextRange* IdRange = RunParseResult.MetaData.Find(TEXT("id"));
    if (!IdRange)
    {
        return false;
    }

    // 3) 실제 원문(Text)에서 해당 범위만큼 Mid로 잘라내서 ID 문자열로 변환
    const FString IdString = Text.Mid(IdRange->BeginIndex, IdRange->Len());


    // 4) KeywordId와 비교
    return IdString == KeywordId;
}

