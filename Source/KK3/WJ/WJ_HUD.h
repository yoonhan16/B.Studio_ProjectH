// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/WJ_Widget.h"
#include "Widgets/WJ_ActionListWidget.h"
#include "WJ_HUD.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API AWJ_HUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AWJ_HUD();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	TSubclassOf<UWJ_Widget> InfomationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	UWJ_Widget* InformationWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	UWJ_Widget* ActorInterfaceWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	UWJ_Widget* MouseFocusWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	TSubclassOf<UWJ_Widget> InteractionInterfaceWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infomation")
	TSubclassOf<UWJ_ActionListWidget> ActionListWidget;

public:

	UFUNCTION(BlueprintCallable)
	void SetInteractionWidget();

	UFUNCTION(BlueprintCallable)
	void SetActorInterfaceWidget(UWJ_Widget* CurrentWidget);

	UFUNCTION(BlueprintCallable)
	void SetWidgetText(FText NewText);

	UFUNCTION(BlueprintCallable)
	void SetActionListWidget(TMap<FString, bool> CurrentActions);

	UFUNCTION(BlueprintCallable)
	void SetProgressPercent(float Percent);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWJ_Widget* PhaseCheckerWidget;

public:

	UFUNCTION(BlueprintCallable)
	void UpdatePhaseChecker();

	UFUNCTION(BlueprintCallable)
	void CallPhaseChange();

	UFUNCTION(BlueprintCallable)
	void RevealInfomation();

	UFUNCTION(BlueprintCallable)
	void SetInfomation(FText Info);
};
