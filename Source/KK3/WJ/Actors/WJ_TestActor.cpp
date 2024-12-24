// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_TestActor.h"
#include "WJ_InteractionActor.h"
#include "../WJ_Character.h"
#include "../WJ_PlayerController.h"
#include "../WJ_HUD.h"
#include "../WJ_PlayerState.h"
#include "../WJ_GameStateBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWJ_TestActor::AWJ_TestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorNumber = -1;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("Trigger"));
	Sphere->SetupAttachment(StaticMesh);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(StaticMesh);
	Widget->SetVisibility(false);
}

// Called when the game starts or when spawned
void AWJ_TestActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWJ_TestActor::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWJ_TestActor::OnOverlapEnd);
}

// Called every frame
void AWJ_TestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_TestActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(ActorNumber > -1)
	{
		AWJ_GameStateBase* GSB = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

		if (GSB)
		{
			if (GSB->GetClueCheckListNum() > ActorNumber && ActorNumber >= 0)
			{
				GSB->SetClueCheck(ActorNumber);
			}
		}
	}
	else if (ActorNumber == -2)
	{
		AWJ_Character* OverlapedCharacter = Cast<AWJ_Character>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OverlapedCharacter Name : %s"), *(OverlapedCharacter->GetName())));
		if(OverlapedCharacter)
		{
			AWJ_PlayerState* OverlapedState = Cast<AWJ_PlayerState>(OverlapedCharacter->GetPlayerState());
			AWJ_PlayerController* OverlapedController = Cast<AWJ_PlayerController>(OverlapedCharacter->GetController());

			if (OverlapedState)
			{
				OverlapedState->SetPlayerRole(ActorRole);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OverlapedState Num : %d"), (OverlapedState->GetPlayerIndex())));
			}

			if (OverlapedController)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OverlapedController Num : %d"), (OverlapedController->GetPlayerIndex())));
			}
		}
		
	}
	else
	{
		AWJ_Character* OverlapedCharacter = Cast<AWJ_Character>(OtherActor);
		if (OverlapedCharacter)
		{
			OverlapedCharacter->bIsTestOverlaped = true;

			Widget->SetVisibility(true);

			//OverlapedCharacter->DialogTest();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OverlapedCharactere Name : %s"), *(OverlapedCharacter->GetName())));
		}

	}
}

void AWJ_TestActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ActorNumber == -1)
	{
		AWJ_Character* OverlapedCharacter = Cast<AWJ_Character>(OtherActor);
		if (OverlapedCharacter)
		{
			OverlapedCharacter->bIsTestOverlaped = true;

			Widget->SetVisibility(false);
			//OverlapedCharacter->DialogTest();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OverlapedCharactere Name : %s"), *(OverlapedCharacter->GetName())));
		}
	}
}

void AWJ_TestActor::SetActorChecked(int32 Index)
{
	if (TestActorLists.Num() > Index)
	{
		TestActorLists[Index]->SetIsChecked();
	}
}

void AWJ_TestActor::DialogTest()
{
	AWJ_HUD* MyHUD = Cast<AWJ_HUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (MyHUD)
	{
		MyHUD->RevealInfomation();

		
	}
}


