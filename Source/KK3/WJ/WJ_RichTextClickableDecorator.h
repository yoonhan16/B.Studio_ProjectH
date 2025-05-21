// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "WJ_RichTextClickableDecorator.generated.h"


class FClickableTextDecorator;

/**
 * 
 */
UCLASS()
class KK3_API UWJ_RichTextClickableDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
	
protected:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

protected:
	TSharedPtr<FClickableTextDecorator> DecoratorInstance;
};
