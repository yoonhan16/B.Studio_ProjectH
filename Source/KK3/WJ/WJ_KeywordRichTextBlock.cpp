// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_KeywordRichTextBlock.h"
#include "WJ_ClickableTextDecorator.h"
#include "WJ_KeywordHandlerSubsystem.h"
#include "WJ_RichTextKeywordHandler.h"

void UWJ_KeywordRichTextBlock::CreateDecorators(TArray<TSharedRef<ITextDecorator>>& OutDecorators)
{

	Super::CreateDecorators(OutDecorators);

    if (!KeywordHandler)
    {
        if (UWorld* World = GetWorld())
        {
            if (!World || !World->IsGameWorld())
            {
                UE_LOG(LogTemp, Log, TEXT("CreateDecorators skipped in Editor Preview"));
                return;
            }


            if (UGameInstance* GI = World->GetGameInstance())
            {
                auto* HandlerSubsystem = GI->GetSubsystem<UWJ_KeywordHandlerSubsystem>();
                if (!HandlerSubsystem)
                {
                    UE_LOG(LogTemp, Error, TEXT("Subsystem was NOT found"));
                    return;
                }

                if(HandlerSubsystem->GetHandler())
                {
                    KeywordHandler = HandlerSubsystem->GetHandler();
                }
                else
                {
                    return;
                }
            }
        }

        if(!KeywordHandler)
        {
            UE_LOG(LogTemp, Log, TEXT("CreateDecorators: KeywordHandler is null, decorators skipped."));
        }

    }

    if (KeywordIds.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateDecorators: KeywordIds array is empty, decorators skipped."));
        return;
    }

    const FString Joined = FString::Join(KeywordIds, TEXT(","));
    UE_LOG(LogTemp, Log, TEXT("CreateDecorators called! KeywordIds: %s"), *Joined);

	if (!KeywordHandler) return;

	for (const FString& KeywordId : KeywordIds)
	{
		OutDecorators.Add(
			MakeShareable(new FWJ_ClickableTextDecorator(this, KeywordId, KeywordHandler))
		);
	}
}
