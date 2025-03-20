// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_Widget.h"
#include "../WJ_ItemStruct.h"
#include "../WJ_PlayerState.h"
#include "Animation/WidgetAnimation.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Components/MultiLineEditableTextBox.h"

void UWJ_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DescriptionBox)
	{
		DescriptionBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWJ_Widget::SetDescriptionText(FText NewText)
{
	if (DescriptionText)
	{
		DescriptionText->SetText(NewText);
	}
}

void UWJ_Widget::SetProgressPercent(float Percent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SetProgressPercent Called"));


	if (ImageProgressBar)
	{
		ImageProgressBar->SetPercent(Percent);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Percent is %f"), Percent));
	}
}

void UWJ_Widget::UpdatePhaseCheckList()
{
	if (PhaseCheckList)
	{

	}
}


UWidgetAnimation* UWJ_Widget::FindAnimation(const FName& AnimationName)
{
	FProperty* Prop = GetClass()->FindPropertyByName(AnimationName);

	if (Prop)
	{
		FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop);

		if (ObjProp)
		{
			UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
			return (Obj && Obj->IsA<UWidgetAnimation>()) ? Cast<UWidgetAnimation>(Obj) : nullptr;
		}
	}

	return nullptr;
}

void UWJ_Widget::HighlightSelectedQuestion(UWJ_Object* SelectedQuestion, UListView* ListView)
{
	if (!ListView || !SelectedQuestion) return;

	for (UObject* ItemObject : ListView->GetListItems())
	{
		UWJ_Object* QuestionItem = Cast<UWJ_Object>(ItemObject);
		if (!QuestionItem) continue;

		UUserWidget* Widget = ListView->GetEntryWidgetFromItem(QuestionItem);
		if (!Widget) continue;

		UTextBlock* QuestionText = Cast<UTextBlock>(Widget->GetWidgetFromName("QuestionText"));
		if (!QuestionText) return;

		QuestionText->SetColorAndOpacity((QuestionItem == SelectedQuestion) ? FSlateColor(FLinearColor(1.0f, 0.8f, 0.2f, 1.0f)) : FSlateColor(FLinearColor::White)
		);

	}

}
