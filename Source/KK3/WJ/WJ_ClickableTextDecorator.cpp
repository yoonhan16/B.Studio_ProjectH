// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_ClickableTextDecorator.h"
#include "WJ_RichTextKeywordHandler.h"



TSharedRef<ISlateRun> FWJ_ClickableTextDecorator::Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunInfo, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style)
{
    UE_LOG(LogTemp, Warning, TEXT("Create() for KeywordId=%s"), *KeywordId);

    // 1) RunInfo ���� �� MetaData ���ڿ�ȭ
    FRunInfo FinalRunInfo(RunInfo.Name);
    for (const auto& Pair : RunInfo.MetaData)
    {
        const FString& Key = Pair.Key;
        const FTextRange& Range = Pair.Value;
        const FString Value = OriginalText.Mid(Range.BeginIndex, Range.Len());
        FinalRunInfo.MetaData.Add(Key, Value);
    }

    // 2) Ŭ�� ID �Ҵ� (MetaData�� id �Ӽ�)
    const FString ClickedId = RunInfo.MetaData.Contains(TEXT("id"))
        ? FinalRunInfo.MetaData[TEXT("id")]
        : TEXT("undefined");

    // 3) ǥ���� �ؽ�Ʈ ����
    const FTextRange& ContentRange = RunInfo.ContentRange;
    FText DisplayText = FText::FromString(OriginalText.Mid(ContentRange.BeginIndex, ContentRange.Len()));

    // 4) �����۸�ũ ��Ÿ�� ���ϱ�
    const FHyperlinkStyle& HyperlinkStyle = FCoreStyle::Get().GetWidgetStyle<FHyperlinkStyle>("Hyperlink");

    // 5) FSlateHyperlinkRun ���� �� Ŭ�� ���ε�
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

    // 1) �±װ� <a> �� �´��� üũ
    if (RunParseResult.Name != TEXT("a"))
    {
        return false;
    }

    // 2) MetaData���� "id" ������ ������
    const FTextRange* IdRange = RunParseResult.MetaData.Find(TEXT("id"));
    if (!IdRange)
    {
        return false;
    }

    // 3) ���� ����(Text)���� �ش� ������ŭ Mid�� �߶󳻼� ID ���ڿ��� ��ȯ
    const FString IdString = Text.Mid(IdRange->BeginIndex, IdRange->Len());


    // 4) KeywordId�� ��
    return IdString == KeywordId;
}

