// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_InteractionActor.h"
#include "../WJ_Character.h"
#include "../Widgets/WJ_InteractingWidget.h"
#include "../Widgets/WJ_Widget.h"
#include "../WJ_PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWJ_InteractionActor::AWJ_InteractionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("Trigger"));
	Sphere->SetupAttachment(StaticMesh);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(StaticMesh);
	Widget->SetVisibility(false);

	GuideWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("GuideWidget"));
	GuideWidget->SetupAttachment(StaticMesh);
	GuideWidget->SetVisibility(false);

	SpringArm_Camera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm_Camera"));
	SpringArm_Camera->SetupAttachment(StaticMesh);

	CurrentWidget = nullptr;
	bCanInteract = true;
	bReplicates = true;
	bIsFocused = false;
	bIsChecked = false;
	bIsTest = false;

	CameraPoints.AddUnique(SpringArm_Camera);

	Count = 0;

	SetActorTickInterval(0.1f);
}

// Called when the game starts or when spawned
void AWJ_InteractionActor::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);

	if (Widget)
	{
		CurrentWidget = Cast<UWJ_Widget>(Widget->GetWidget());
		//if (CurrentWidget)
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CurrentWidget is Valid"));
		//}
	}

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWJ_InteractionActor::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWJ_InteractionActor::OnOverlapEnd);
	
	if (IsFocusWidget)
	{
		IsFocusWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//GetWorldTimerManager().SetTimer(CountTimerHandle, this, &AWJ_InteractionActor::AdvanceTimer, 0.1f, true);
}

// Called every frame
void AWJ_InteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFocused)
	{

	}
}

void AWJ_InteractionActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_InteractionActor, bCanInteract);
	DOREPLIFETIME(AWJ_InteractionActor, bIsChecked);
	DOREPLIFETIME(AWJ_InteractionActor, bIsTest);
}

void AWJ_InteractionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap Begin"));
		}

		OverlapedCharacter = Cast<AWJ_Character>(OtherActor);

		if(OverlapedCharacter)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("WJ_Character is Overlap"));

			OverlapedCharacter->AddInteractActor(this);
		}

		//Widget->SetVisibility(bIsFocused);

		if (IsFocusWidget)
		{
			IsFocusWidget->SetVisibility(ESlateVisibility::Visible);
		}

}

void AWJ_InteractionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap End"));
		}

		OverlapedCharacter = Cast<AWJ_Character>(OtherActor);

		if (OverlapedCharacter)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("WJ_Character was Overlap"));
			OverlapedCharacter->RemoveInteractActor(this);
		}

		SetIsFocused(false);

		Widget->SetVisibility(bIsFocused);

		if (IsFocusWidget)
		{
			IsFocusWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		SetRenderCustomDepth();

}

TMap<FString, bool> AWJ_InteractionActor::GetActions()
{
	return Actions;
}

TArray<FClueStruct> AWJ_InteractionActor::GetClueStructs()
{
	return ClueStructs;
}

void AWJ_InteractionActor::SetIsFocused(bool bFocused)
{
	bIsFocused = bFocused;
}

void AWJ_InteractionActor::SetWidgetVisible()
{
	Widget->SetVisibility(bIsFocused);
}

void AWJ_InteractionActor::SetRenderCustomDepth()
{
	StaticMesh->SetRenderCustomDepth(bIsFocused);
	
}

void AWJ_InteractionActor::SetWidgetPercentage(float Percent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Widget Percant Set!"));

	if (CurrentWidget)
	{
		CurrentWidget->SetProgressPercent(Percent);
	}
}

void AWJ_InteractionActor::UpdateTimer()
{
}

void AWJ_InteractionActor::AdvanceTimer()
{
	--Count;
	UpdateTimer();

	if (Count < 1)
	{
		GetWorldTimerManager().ClearTimer(CountTimerHandle);
		CountFinished();
	}
}

void AWJ_InteractionActor::CountFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Count Finish!"));
}

bool AWJ_InteractionActor::GetIsChecked()
{
	return bIsChecked;
}

void AWJ_InteractionActor::SetIsChecked()
{
	if (HasAuthority())
	{
		Multicast_SetIsChecked();
	}
	else
	{
		Server_SetIsChecked();
	}
}

bool AWJ_InteractionActor::Server_SetIsChecked_Validate()
{
	return true;
}

void AWJ_InteractionActor::Server_SetIsChecked_Implementation()
{
	Multicast_SetIsChecked();
}

bool AWJ_InteractionActor::Multicast_SetIsChecked_Validate()
{
	return true;
}

void AWJ_InteractionActor::Multicast_SetIsChecked_Implementation()
{
	bIsChecked = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor is Checked!"));
}

void AWJ_InteractionActor::SetIsTest(bool IsTest)
{

	if (HasAuthority())
	{
		Multicast_SetIsTest(IsTest);
	}
	else
	{
		Server_SetIsTest(IsTest);
	}
}

bool AWJ_InteractionActor::Server_SetIsTest_Validate(bool IsTest)
{
	return true;
}

void AWJ_InteractionActor::Server_SetIsTest_Implementation(bool IsTest)
{
	Multicast_SetIsTest(IsTest);
}

bool AWJ_InteractionActor::Multicast_SetIsTest_Validate(bool IsTest)
{
	return true;
}

void AWJ_InteractionActor::Multicast_SetIsTest_Implementation(bool IsTest)
{
	bIsTest = IsTest;
}

bool AWJ_InteractionActor::Server_IsCanInteract_Validate()
{
	return true;
}

void AWJ_InteractionActor::Server_IsCanInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Server Function Called"));
	UE_LOG(LogTemp, Warning, TEXT("Server Function Called"));

	Multicast_IsCanInteract();
}

bool AWJ_InteractionActor::Multicast_IsCanInteract_Validate()
{
	return true;
}

void AWJ_InteractionActor::Multicast_IsCanInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Multicast Function Called"));
	UE_LOG(LogTemp, Warning, TEXT("Multicast Function Called"));

	bCanInteract = false;
}

void AWJ_InteractionActor::Interacting()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interacting Called!"));
	//if (InteractingWidgetClass)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("InteractingWidgetClass is Valid!"));
	//	InteractingWidget = Cast<UWJ_InteractingWidget>(CreateWidget(GetWorld(), InteractingWidgetClass));
	//	InteractingWidget->AddToViewport();

	//	class APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//	
	//	if (PC->IsLocalController())
	//	{
	//		//Scene2D->TextureTarget = RenderTarget2D;
	//	}
	//	
	//	class AWJ_PlayerController* WJPC = Cast<AWJ_PlayerController>(PC);

	//	if (WJPC)
	//	{
	//		WJPC->InteractingWidget = InteractingWidget;
	//		WJPC->IA_SpringArm = SpringArm_Scene2D;
	//	}

	//	Scene2D->ShowOnlyActorComponents(this);
	//	
	//	class ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//	Character->DisableInput(PC);
	//}

	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interacting Function is Called!"));
	
}

void AWJ_InteractionActor::Investigating()
{
	if (InvestigatingWidgetClass)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("IA's ProgressiveNum is : %d"), ProgressiveNum));
		InvestigatingWidget = Cast<UWJ_InvestigatingWidget>(CreateWidget(GetWorld(), InvestigatingWidgetClass));
		InvestigatingWidget->ProgressiveNum = ProgressiveNum;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("IW's ProgressiveNum is : %d"), InvestigatingWidget->ProgressiveNum));
		InvestigatingWidget->GetArrayNum();
		//InvestigatingWidget->SetActionsNum();
		InvestigatingWidget->AddToViewport();

		class APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		class AWJ_PlayerController* WJPC = Cast<AWJ_PlayerController>(PC);
		if (WJPC)
		{
		}
	}
}

void AWJ_InteractionActor::UpdateInvestigatingWidget(int ComponentNumber, bool bVisible)
{
	if (InvestigatingWidget)
	{
		if(bVisible)
		{
			InvestigatingWidget->ShowActionWidget(ComponentNumber);
		}
		else
		{
			InvestigatingWidget->HideActionWidget(ComponentNumber);
		}
	}
}

void AWJ_InteractionActor::GetComponentIndex()
{
}

void AWJ_InteractionActor::IsFocus()
{
	IsFocused = true;
}


void AWJ_InteractionActor::IsNotFocus()
{
	IsFocused = false;
}

void AWJ_InteractionActor::Connect()
{
	Widget->SetVisibility(true);
}

void AWJ_InteractionActor::Disconnect()
{
	Widget->SetVisibility(false);
}

void AWJ_InteractionActor::SetGuideVisible(bool Visibillity)
{
	GuideWidget->SetVisibility(Visibillity);
}

bool AWJ_InteractionActor::GetIsCanInteract()
{
	return bCanInteract;
}

void AWJ_InteractionActor::SetInteractPossible()
{
	bCanInteract = true;
}

void AWJ_InteractionActor::SetInteractImPossible()
{
	bCanInteract = false;
}

void AWJ_InteractionActor::SetIsCanInteract(bool NewValue)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetIsCanInteract Called"));
	UE_LOG(LogTemp, Warning, TEXT("SetIsCanInteract Called"));

	//if (HasAuthority())
	//{
		Server_IsCanInteract();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Function Called Authority"));
	//}
	//else
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Function Not Called"));
	//}
}

void AWJ_InteractionActor::IsCanInteract()
{
	if (HasAuthority())
	{
		Multicast_IsCanInteract();
	}
	else
	{
		Server_IsCanInteract();
	}
}
