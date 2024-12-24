// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJ_TestActor.generated.h"

UCLASS()
class KK3_API AWJ_TestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_TestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class AWJ_InteractionActor*> TestActorLists;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActorNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActorRole;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:

	UFUNCTION(BlueprintCallable)
	void SetActorChecked(int32 Index);

	UFUNCTION(BlueprintCallable)
	void DialogTest();
};
