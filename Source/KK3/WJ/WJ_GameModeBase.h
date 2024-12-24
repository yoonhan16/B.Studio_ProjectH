// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WJ_PlayerController.h"
#include "WJ_ItemStruct.h"
#include "GameFramework/GameModeBase.h"
#include "WJ_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API AWJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWJ_GameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;


protected:

	UPROPERTY()
	int32 ProgressNum;
	
public:

	UFUNCTION()
	int32 GetProgressNum();

	UFUNCTION()
	void SetProgressNum(int32 Num);

	UFUNCTION(BlueprintCallable)
	void SequanceChange(AWJ_PlayerController* CurrentPC);

	UFUNCTION(BlueprintCallable)
	void GetPlayersReady();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWJ_PlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	class UWJ_Widget* CountWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float MaxTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float CountTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float CycleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle CountTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<FItemCheckerStruct> TestItems;
public:

	UFUNCTION(BlueprintCallable)
	void CountStart(float Count, float Cycle);

	UFUNCTION(BlueprintCallable)
	void UpdateTimer();

	UFUNCTION(BlueprintCallable)
	void AdvanceTimer();

	UFUNCTION(BlueprintCallable)
	void FinishTimer();

	UFUNCTION(BlueprintCallable)
	void UpdateCountWidget();

	UFUNCTION(BlueprintCallable)
	void SequanceChangeCheck();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerIndex(APlayerController* PC);
};
