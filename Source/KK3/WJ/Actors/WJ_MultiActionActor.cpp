// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_MultiActionActor.h"
#include "../WJ_Character.h"

// Sets default values
AWJ_MultiActionActor::AWJ_MultiActionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConditionalNum = 2;
}

// Called when the game starts or when spawned
void AWJ_MultiActionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWJ_MultiActionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWJ_MultiActionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWJ_Character* OverlapedCharacter = Cast<AWJ_Character>(OtherActor);

	if (OverlapedCharacter && (PlayerChecker.Num() < ConditionalNum))
	{
		PlayerChecker.AddUnique(OverlapedCharacter);


	}

}

void AWJ_MultiActionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWJ_Character* OverlapedCharacter = Cast<AWJ_Character>(OtherActor);

	PlayerChecker.Remove(OverlapedCharacter);
}

void AWJ_MultiActionActor::MultiActionTimer()
{
}

void AWJ_MultiActionActor::MultiAction()
{
}

