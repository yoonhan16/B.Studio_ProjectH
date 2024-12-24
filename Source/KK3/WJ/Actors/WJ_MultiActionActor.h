// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_MultiActionActor.generated.h"

UCLASS()
class KK3_API AWJ_MultiActionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_MultiActionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi_Default")
	int32 ConditionalNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AWJ_Character*> PlayerChecker;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	FTimerHandle MultiActionTimeHandle;

	UFUNCTION(BlueprintCallable)
	void MultiActionTimer();

	UFUNCTION(BlueprintCallable)
	void MultiAction();
};
