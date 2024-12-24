// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_Actor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AWJ_Actor::AWJ_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));

	bWidgetVisibility = false;
}

// Called when the game starts or when spawned
void AWJ_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWJ_Actor::GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_Actor, bWidgetVisibility);
}

bool AWJ_Actor::Server_SetWidgetVisibleTrue_Validate()
{
	return true;
}

void AWJ_Actor::Server_SetWidgetVisibleTrue_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Server_SetWidgetVisibleTrue is Called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SetWidgetVisibleTrue_Implementation"));
	Multi_SetWidgetVisibleTrue();
}

bool AWJ_Actor::Multi_SetWidgetVisibleTrue_Validate()
{
	return true;
}

void AWJ_Actor::Multi_SetWidgetVisibleTrue_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Multi_SetWidgetVisibleTrue is Called"));
	UE_LOG(LogTemp, Warning, TEXT("Multi_SetWidgetVisibleTrue_Implementation"));

	bWidgetVisibility = true;

	Widget->SetVisibility(bWidgetVisibility);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Widget is Visible"));
}

bool AWJ_Actor::Server_SetWIdgetVisibleFalse_Validate()
{
	return true;
}

void AWJ_Actor::Server_SetWIdgetVisibleFalse_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Server_SetWidgetVisibleTrue is Called"));
	UE_LOG(LogTemp, Warning, TEXT("Server_SetWidgetVisibleTrue_Implementation"));
	Multi_SetWidgetVisibleFalse();
}

bool AWJ_Actor::Multi_SetWidgetVisibleFalse_Validate()
{
	return true;
}

void AWJ_Actor::Multi_SetWidgetVisibleFalse_Implementation()
{

}

// Called every frame
void AWJ_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_Actor::SetWidgetVisibleTrue()
{
	if (HasAuthority())
	{
		Multi_SetWidgetVisibleTrue();
	}
	else
	{
		Server_SetWidgetVisibleTrue();
	}
}

void AWJ_Actor::SetWidgetVisibleFalse()
{
	if (HasAuthority())
	{
		
	}
}

