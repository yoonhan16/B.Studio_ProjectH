// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "WJ_Actor.generated.h"

UCLASS()
class KK3_API AWJ_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWJ_Actor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Widget;

	UPROPERTY(Replicated)
	bool bWidgetVisibility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetWidgetVisibleTrue();
	bool Server_SetWidgetVisibleTrue_Validate();
	void Server_SetWidgetVisibleTrue_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetWidgetVisibleTrue();
	bool Multi_SetWidgetVisibleTrue_Validate();
	void Multi_SetWidgetVisibleTrue_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetWIdgetVisibleFalse();
	bool Server_SetWIdgetVisibleFalse_Validate();
	void Server_SetWIdgetVisibleFalse_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_SetWidgetVisibleFalse();
	bool Multi_SetWidgetVisibleFalse_Validate();
	void Multi_SetWidgetVisibleFalse_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWidgetVisibleTrue();

	void SetWidgetVisibleFalse();
};
