// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_MultiInteractionActor.h"
#include "WJ_ActorComponent.h"
#include "../WJ_Character.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AWJ_MultiInteractionActor::AWJ_MultiInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(StaticMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	OverlapChecker = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapChecker"));
	OverlapChecker->SetupAttachment(StaticMesh);

	OwnerCharacter = nullptr;

	Clue01 = CreateDefaultSubobject<UWJ_ActorComponent>(TEXT("Clue01"));
}

// Called when the game starts or when spawned
void AWJ_MultiInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapChecker->OnComponentBeginOverlap.AddDynamic(this, &AWJ_MultiInteractionActor::OnOverlapBegin);
	OverlapChecker->OnComponentEndOverlap.AddDynamic(this, &AWJ_MultiInteractionActor::OnOverlapEnd);
}

// Called every frame
void AWJ_MultiInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_MultiInteractionActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_MultiInteractionActor, Clues);
}

void AWJ_MultiInteractionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapCharacter = Cast<AWJ_Character>(OtherActor);

	if (OverlapCharacter)
	{
		OverlapCharacter->MultiInteractionActor = this;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("MultiActor is Overlaped"));
	}
}

void AWJ_MultiInteractionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlapCharacter = Cast<AWJ_Character>(OtherActor);

	if (OverlapCharacter)
	{
		OverlapCharacter->MultiInteractionActor = nullptr;
	}
}

TSubclassOf<UWJ_MultiInteractingWidget> AWJ_MultiInteractionActor::GetInteractingWidget()
{
	return MultiWidget;
}

bool AWJ_MultiInteractionActor::GetContainComponent(UWJ_StaticMeshComponent* Component)
{
	return Clues.Contains(Component);
}

void AWJ_MultiInteractionActor::SetControlOwner(AWJ_Character* NewOwner)
{
	OwnerCharacter = NewOwner;

	NewOwner->GetMultiActorControl();
}

void AWJ_MultiInteractionActor::SetCharacterArray(AWJ_Character* NewCharacter)
{
	ConnectCharacters.AddUnique(NewCharacter);

	if (OwnerCharacter == nullptr)
	{
		SetControlOwner(NewCharacter);
	}
}

void AWJ_MultiInteractionActor::ComponentInteract(UWJ_StaticMeshComponent* TargetComponent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ComponentInteract is Called"));

	if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Call HasAuthority!"));
		Multi_RepComponentInteract(TargetComponent);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Call Not HasAuthority!"));
		Server_RepComponentInteract(TargetComponent);
	}

}

bool AWJ_MultiInteractionActor::Server_RepComponentInteract_Validate(UWJ_StaticMeshComponent* TargetComponent)
{
	return true;
}

void AWJ_MultiInteractionActor::Server_RepComponentInteract_Implementation(UWJ_StaticMeshComponent* TargetComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Server Function Called"));
	Multi_RepComponentInteract(TargetComponent);
}

bool AWJ_MultiInteractionActor::Multi_RepComponentInteract_Validate(UWJ_StaticMeshComponent* TargetComponent)
{
	return true;
}

void AWJ_MultiInteractionActor::Multi_RepComponentInteract_Implementation(UWJ_StaticMeshComponent* TargetComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Multi Function Called"));
	if (Clues.Contains(TargetComponent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Multi Function true"));
		TargetComponent->InteractAction();
	}
}


