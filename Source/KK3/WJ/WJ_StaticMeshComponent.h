// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WJ_StaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class KK3_API UWJ_StaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:

	UWJ_StaticMeshComponent();

protected:
	virtual void BeginPlay() override;

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY()
	UMaterialInterface* MaterialDynamic;

	UPROPERTY(Replicated)
	int32 ColorNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProgressiveNum;

	UFUNCTION()
	void InteractAction();

	UFUNCTION(BlueprintCallable)
	void SetColorNum();

	UFUNCTION(BlueprintCallable)
	void ChangeColor();

protected:

};
