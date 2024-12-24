// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InteractingWidget.h"
#include "../WJ_PlayerController.h"
#include "Kismet/GamePlayStatics.h"

void UWJ_InteractingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActorImageButton->OnHovered.AddDynamic(this, &UWJ_InteractingWidget::ActorImageHovered);
	ActorImageButton->OnPressed.AddDynamic(this, &UWJ_InteractingWidget::ActorImageClicked);
	ActorImageButton->OnReleased.AddDynamic(this, &UWJ_InteractingWidget::ActorImageReleased);

	ExitButton->OnPressed.AddDynamic(this, &UWJ_InteractingWidget::BreakInteract);
}

void UWJ_InteractingWidget::ActorImageHovered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Mouse Hover!"));
}

void UWJ_InteractingWidget::ActorImageClicked()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetInputMode(FInputModeGameOnly());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Mouse Click!"));
}

void UWJ_InteractingWidget::ActorImageReleased()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetInputMode(FInputModeGameAndUI());
}

void UWJ_InteractingWidget::BreakInteract()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AWJ_PlayerController* WJPC = Cast<AWJ_PlayerController>(PC);

	if (WJPC)
	{
		WJPC->DisconnectingActor();
	}
}
