// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InteractActionWidget.h"
#include "../WJ_Character.h"
#include "../WJ_GameModeBase.h"
#include "../WJ_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void UWJ_InteractActionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActionButton->OnPressed.AddDynamic(this, &UWJ_InteractActionWidget::Action);
}

void UWJ_InteractActionWidget::AddInteractInfo()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AWJ_Character* WJCharacter = Cast<AWJ_Character>(Character);

}

void UWJ_InteractActionWidget::Action()
{
	if (Information.Description != "" && Information.ItemID != "")
	{
		FString Name = Information.ItemID;
		FString Description = Information.Description;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("This Info Name is : %s , Description is : %s"), *Name, *Description));

		AddInteractInfo();
	}

	AWJ_GameModeBase* GameMode = Cast<AWJ_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Current Num is : %d"), ProgressiveNum));

		if (GameMode->GetProgressNum() < ProgressiveNum - 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("GameMode ProgressNum is : %d"), GameMode->GetProgressNum()));
		}
		else
		{
			if (GameMode->GetProgressNum() == ProgressiveNum - 1)
			{
				GameMode->SetProgressNum(ProgressiveNum);

				AWJ_PlayerController* WJPC = Cast<AWJ_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				WJPC->CheckArray(ProgressiveNum);
			}
			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Go To Next Level!"));
		}


	}

}

void UWJ_InteractActionWidget::SetProgressiveNum(int32 Num)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Set Progressive Num!"));
	ProgressiveNum = Num;
}
