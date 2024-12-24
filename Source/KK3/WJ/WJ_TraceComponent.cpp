// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_TraceComponent.h"
#include "WJ_Character.h"
#include "WJ_PlayerController.h"
#include "Actors/WJ_InteractionActor.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UWJ_TraceComponent::UWJ_TraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickInterval(0.02f);
	// ...

	PlayerCameraManager = nullptr;
}


// Called when the game starts
void UWJ_TraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
}

void UWJ_TraceComponent::Trace()
{
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CameraRotation);
	FVector EndLocation = CameraLocation + (ForwardVector * 1000);
	FHitResult HitOut;
	FCollisionQueryParams TraceParams;

	GetWorld()->LineTraceSingleByChannel(HitOut, CameraLocation, EndLocation, ECC_Visibility, TraceParams);

	if (HitOut.GetActor())
	{
		AWJ_InteractionActor* HitActor = Cast<AWJ_InteractionActor>(HitOut.GetActor());

		AWJ_PlayerController* PC = Cast<AWJ_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
		if(PC)
		{

			if (PC->InteractionActor != nullptr)
			{
				PC->InteractionActor->SetIsFocused(false);
				PC->InteractionActor->SetWidgetVisible();
				PC->InteractionActor->SetRenderCustomDepth();
			}

			if (HitActor)
			{
				if (GetIsNearActor(HitActor))
				{
					InteractionActor = HitActor;
				}

				PC->InteractionActor = HitActor;
				PC->InteractionActor->SetIsFocused(true);
				PC->InteractionActor->SetWidgetVisible();
				PC->InteractionActor->SetRenderCustomDepth();
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Trace Called"));

}

AWJ_InteractionActor* UWJ_TraceComponent::GetInteractionActor()
{
	if (InteractionActor)
	{
		return InteractionActor;
	}

	return nullptr;
}

void UWJ_TraceComponent::AddNearActor(AWJ_InteractionActor* NewActor)
{
	NearInteractActors.AddUnique(NewActor);
}

bool UWJ_TraceComponent::GetIsNearActor(AWJ_InteractionActor* NewActor)
{
	return NearInteractActors.Contains(NewActor);
}


// Called every frame
void UWJ_TraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Trace();
	// ...
}

