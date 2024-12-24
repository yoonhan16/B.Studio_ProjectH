// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_Character.h"
#include "WJ_PlayerController.h"
#include "WJ_PlayerState.h"
#include "WJ_GameModeBase.h"
#include "WJ_HUD.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectBase.h"
#include "Components.h"
#include "Components/ArrowComponent.h"
#include "Widgets/WJ_MultiInteractingWidget.h"
#include "CollisionQueryParams.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWJ_Character::AWJ_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsCanInteract = false;
	IsFocus = false;
	IsCanInvestigate = false;
	IsCanMultiInteract = false;
	IsEndInteract = false;
	bIsCrouch = true;
	bIsTestOverlaped = false;

	CurrentCamera = nullptr;
	CurrentCameraBoom = nullptr;
	CurrentComponent = nullptr;
	FocusActor = nullptr;
	IA = nullptr;
	MovingCameraTimelineFloatCurve = nullptr;

	MovingCameraTimeline = CreateDefaultSubobject<UTimelineComponent>("MovingCameraTimeline");

	TraceComponent = CreateDefaultSubobject<UWJ_TraceComponent>("TraceComponent");

	Arrow_Interact = CreateDefaultSubobject<UArrowComponent>("Arrow_Interact");
	Arrow_Interact->SetupAttachment(RootComponent);

	SpringArm_Interact = CreateDefaultSubobject<USpringArmComponent>("SpringArm_Interact");
	SpringArm_Interact->SetupAttachment(Arrow_Interact);
	SpringArm_Interact->TargetArmLength = 450.f;

	Camera_Interact = CreateDefaultSubobject<UCameraComponent>("Camera_Interact");
	Camera_Interact->SetupAttachment(SpringArm_Interact);
	Camera_Interact->SetActive(false);

}

// Called when the game starts or when spawned
void AWJ_Character::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("BeginPlay Called!"));

	SetupInteractionTrace();

	CurrentComponent = nullptr;

	if (MovingCameraTimelineFloatCurve)
	{
		UpdateFunctionFloat.BindDynamic(this, &AWJ_Character::UpdateTimelineComp);
		CurveFTimeline.AddInterpFloat(MovingCameraTimelineFloatCurve, UpdateFunctionFloat);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("FloatCurve is Valid!"));

		CurveFinishedCallback.BindDynamic(this, &AWJ_Character::TimelineFinished);
	}

}

// Called every frame
void AWJ_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveFTimeline.TickTimeline(DeltaTime);

	//if(CurrentCamera)
	//{
	//	FVector StartLocation = CurrentCamera->GetComponentLocation();
	//	//FRotator _Rotation = CurrentCamera->GetRelativeRotation();

	//	FVector EndLocation = StartLocation + (CurrentCamera->GetForwardVector() * 1000);

	//	FHitResult _HitOut;

	//	FCollisionQueryParams _TraceParams;

	//	GetWorld()->LineTraceSingleByChannel(_HitOut, StartLocation, EndLocation, ECC_Visibility, _TraceParams);

	//	if (IsCanInvestigate)
	//	{

	//		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.0f, 0.0f, 5.0f);

	//		if (_HitOut.GetComponent())
	//		{
	//			UPrimitiveComponent* HitComponent = _HitOut.GetComponent();

	//			if (HitComponent != CurrentComponent)
	//			{
	//				CurrentComponent = HitComponent;
	//				UpdateComponentReference(HitComponent);
	//			}

	//			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Hit Component Name: %s"), *HitComponent->GetName()));
	//		}
	//	}
	//	else if (!IsCanInvestigate)
	//	{
	//		if (_HitOut.GetActor())
	//		{
	//			//InteractionActor = Cast<AWJ_InteractionActor>(_HitOut.GetActor());

	//			AWJ_InteractionActor* HitActor = Cast<AWJ_InteractionActor>(_HitOut.GetActor());

	//			if (InteractionActor != nullptr)
	//			{
	//				InteractionActor->SetIsFocused(false);
	//				InteractionActor->SetWidgetVisible();
	//				InteractionActor->SetRenderCustomDepth();
	//			}

	//			if (CanInteractActors.Contains(HitActor))
	//			{
	//				InteractionActor = HitActor;
	//				InteractionActor->SetIsFocused(true);
	//				InteractionActor->SetWidgetVisible();
	//				InteractionActor->SetRenderCustomDepth();
	//			}

	//		}
	//	}
	//}


}

// Called to bind functionality to input
void AWJ_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWJ_Character::CanInteract()
{
	IsCanInteract = true;
}

void AWJ_Character::CannotInteract()
{
	IsCanInteract = false;
}

void AWJ_Character::Interacting()
{
	if (InteractionActor && CanInteractActors.Contains(InteractionActor))
	{
		SetIsCrouch(InteractionActor);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), InteractionActor->GetIsCanInteract() ? TEXT("True"):TEXT("False")));

		//if(InteractionActor->GetIsCanInteract())
		//{
		//	//InteractionActor->SetOwner(this);

		//	if (HasAuthority())
		//	{
		//		InteractionActor->IsCanInteract();
		//	}
		//	else
		//	{
		//		Server_Interacting(InteractionActor);
		//	}

		//	FActorSpawnParameters SpawnParams;
		//	FVector SpawnLocation = FVector(0, 0, 2000);
		//	FRotator SpawnRotation;

		//	IA = GetWorld()->SpawnActor<AWJ_InteractionActor>(InteractionActor->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);

		//	if (IA)
		//	{
		//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interaction Actor is Spawn!"));
		//	}

		//	IA->Interacting();

		//	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		//	PC->SetInputMode(FInputModeGameAndUI());

		//	AWJ_PlayerController* CurrentPC = Cast<AWJ_PlayerController>(PC);

		//	if (CurrentPC)
		//	{
		//		CurrentPC->IsInteract = true;
		//		CurrentPC->InteractionActor = IA;
		//		CurrentPC->InteractingActor();
		//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interacting Function is Called"));
		//	}

		//	this->DisableInput(PC);
		//}
		//else
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Someone has This Actor"));
		//}
	}
}

bool AWJ_Character::Server_Interacting_Validate(AWJ_InteractionActor* WJIA)
{
	return true;
}

void AWJ_Character::Server_Interacting_Implementation(AWJ_InteractionActor* WJIA)
{
	if (WJIA)
	{
		WJIA->Server_IsCanInteract();
	}
}

void AWJ_Character::EndInteracting()
{
	//if (InteractionActor)
	//{
	//	InteractionActor->SetInteractPossible();
	//}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AWJ_PlayerController* CurrentPC = Cast<AWJ_PlayerController>(PC);

	if (CurrentPC)
	{
		CurrentPC->IsInteract = false;
		CurrentPC->InteractionActor = nullptr;
	}

}

void AWJ_Character::Investigating()
{
	if (InteractionActor)
	{
		if(CurrentCamera)
		{
			CameraStartLoc = CurrentCamera->GetComponentLocation();
			CameraStartRot = CurrentCamera->GetComponentRotation();

			OriginLoc = CameraStartLoc;
			OriginRot = CameraStartRot;

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Start Loc : X : %f , Y : %f, Z : %f"), CameraStartLoc.X, CameraStartLoc.Y, CameraStartLoc.Z));

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Start Loc : X : %f , Y : %f, Z : %f"), CameraStartLoc.X, CameraStartLoc.Y, CameraStartLoc.Z));

			CameraEndLoc = InteractionActor->SpringArm_Camera->GetComponentLocation();
			CameraEndRot = InteractionActor->SpringArm_Camera->GetComponentRotation();

			CurrentCamera->SetWorldLocation(CameraEndLoc);
			CurrentCamera->SetWorldRotation(CameraEndRot);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera End Loc : X : %f , Y : %f, Z : %f"), CameraEndLoc.X, CameraEndLoc.Y, CameraEndLoc.Z));

			//CurveFTimeline.PlayFromStart();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Camera Move to Timeline!"));
		}

		SetIsCrouch(InteractionActor);

		TargetComponents = InteractionActor->TargetComponents;

		IsCanInvestigate = true;

		InteractionActor->Investigating();

		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->SetInputMode(FInputModeGameAndUI());

		AWJ_PlayerController* CurrentPC = Cast<AWJ_PlayerController>(PC);
		
		if(CurrentPC)
		{
			CurrentPC->CurrentCamera = this->CurrentCamera;
			this->DisableInput(PC);
		}

	}
}

void AWJ_Character::EndInvestigating()
{
	IsEndInteract = true;

	CameraEndLoc = OriginLoc;
	CameraEndRot = OriginRot;

	CameraStartLoc = CurrentCamera->GetComponentLocation();
	CameraStartRot = CurrentCamera->GetComponentRotation();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Start Loc : X : %f , Y : %f, Z : %f"), CameraStartLoc.X, CameraStartLoc.Y, CameraStartLoc.Z));

	IsCanInvestigate = false;
	CurveFTimeline.PlayFromStart();

	CurveFTimeline.SetTimelineFinishedFunc(CurveFinishedCallback);
}

void AWJ_Character::NoticeMultiActor()
{
	if (MultiInteractionActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("You Can Interact MultiActor"));
	}
}

void AWJ_Character::MultiInteracting()
{
	if (MultiInteractionActor && MultiInteractionActor->GetInteractingWidget())
	{
		SetIsCrouch(MultiInteractionActor);

		UWJ_MultiInteractingWidget* MultiWidget = Cast<UWJ_MultiInteractingWidget>(CreateWidget(GetWorld(), MultiInteractionActor->GetInteractingWidget()));

		MultiWidget->AddToViewport();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, TEXT("MultiInteracting Called!"));

		if (CurrentCameraBoom && CurrentCamera)
		{
			CameraStartLoc = CurrentCameraBoom->GetComponentLocation();
			CameraStartRot = CurrentCameraBoom->GetComponentRotation();

			OriginLoc = CameraStartLoc;
			OriginRot = CameraStartRot;

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Start Loc : X : %f , Y : %f, Z : %f"), CameraStartLoc.X, CameraStartLoc.Y, CameraStartLoc.Z));

			CameraEndLoc = MultiInteractionActor->SpringArm->GetComponentLocation();
			CameraEndRot = MultiInteractionActor->SpringArm->GetComponentRotation();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Start Loc : X : %f , Y : %f, Z : %f"), CameraEndLoc.X, CameraEndLoc.Y, CameraEndLoc.Z));

			CurrentCameraBoom->SetWorldLocation(CameraEndLoc);
			CurrentCameraBoom->SetWorldRotation(CameraEndRot);

			FVector CamLoc = CurrentCamera->GetRelativeLocation();
			CamLoc.X = CamLoc.X - 400;

			CurrentCamera->SetRelativeLocation(CamLoc);

			//CurrentCameraBoom->TargetArmLength = 400.f;

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera End Loc : X : %f , Y : %f, Z : %f"), CameraEndLoc.X, CameraEndLoc.Y, CameraEndLoc.Z));

			//CurveFTimeline.PlayFromStart();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Camera Move to Timeline!"));
		}

		AWJ_PlayerController* MyController = Cast<AWJ_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (MyController && CurrentCameraBoom)
		{
			CurrentCameraBoom->bUsePawnControlRotation = false;
			MyController->IA_SpringArm = this->CurrentCameraBoom;
			MyController->MultiInteractingActor();
			MyController->SetInputMode(FInputModeGameAndUI());
			//MyController->SetViewTargetWithBlend(MultiInteractionActor, 1.f);
			//this->DisableInput(MyController);
		}

		IsCanMultiInteract = true;

		//MultiInteractionActor->SetCharacterArray(this);
	}
}

void AWJ_Character::InteractToComponent()
{
	if (CurrentCamera)
	{
		FVector StartLocation = CurrentCamera->GetComponentLocation();
		FVector EndLocation = StartLocation + (CurrentCamera->GetForwardVector() * 1000);
		FHitResult _HitOut;
		FCollisionQueryParams _TraceParams;
		_TraceParams.AddIgnoredActor(this);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ITC is Work"));

		if (GetWorld()->LineTraceSingleByChannel(_HitOut, StartLocation, EndLocation, ECC_Visibility, _TraceParams))
		{
			UWJ_StaticMeshComponent* WJ_Component = Cast<UWJ_StaticMeshComponent>(_HitOut.GetComponent());

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ITC has HitOut"));

			if (WJ_Component && MultiInteractionActor)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ITC Found Component"));
				if (MultiInteractionActor->GetContainComponent(WJ_Component))
				{
					if(HasAuthority())
					{
						MultiInteractionActor->ComponentInteract(WJ_Component);
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ITC Call Function"));
					}
					else
					{
						Server_InteractToComponent(WJ_Component);
					}
				}
			}
		}
	}
}

bool AWJ_Character::Server_InteractToComponent_Validate(UWJ_StaticMeshComponent* Component)
{
	return true;
}

void AWJ_Character::Server_InteractToComponent_Implementation(UWJ_StaticMeshComponent* Component)
{
	MultiInteractionActor->ComponentInteract(Component);
}

void AWJ_Character::SetFocusActor()
{
	if (FocusActor)
	{
		FocusActor->Disconnect();
	}


	if (CanInteractActors.Num() > 0) 
	{
		int32 FocusNum;

		FocusNum = CanInteractActors.IndexOfByKey(FocusActor);

		if (FocusNum != INDEX_NONE)
		{
			if (FocusNum == CanInteractActors.Num() - 1)
			{
				FocusActor = CanInteractActors[0];
				FocusActor->Connect();

				//CanInteractActors.Top()
			}
			else
			{
				FocusActor = CanInteractActors[FocusNum + 1];
				FocusActor->Connect();
			}
		}
		else
		{
			FocusActor = CanInteractActors[0];
			FocusActor->Connect();
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Array Num is : %i"), CanInteractActors.Num()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Current Num is : %i"), CanInteractActors.IndexOfByKey(FocusActor)));
	}
}

void AWJ_Character::UpdateTimelineComp(float Output)
{
	CurrentCamera->SetWorldLocation(CameraStartLoc + ((CameraEndLoc - CameraStartLoc) * Output));
	CurrentCamera->SetWorldRotation(CameraStartRot + ((CameraEndRot - CameraStartRot) * Output));
}

void AWJ_Character::UpdateComponentReference(UPrimitiveComponent* Component)
{
	int32 Index = 0;

	for (UPrimitiveComponent* TargetComponent : TargetComponents)
	{
		if (TargetComponent == CurrentComponent)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Target Component : %s"), *UKismetSystemLibrary::GetObjectName(TargetComponent)/*GetObjectName(Component)*/));

			InteractionActor->UpdateInvestigatingWidget(Index , true);
		}
		else
		{
			InteractionActor->UpdateInvestigatingWidget(Index, false);
		}

		Index = Index + 1;
	}
}

void AWJ_Character::TimelineFinished()
{
	if(IsEndInteract)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

		this->EnableInput(PC);

		IsEndInteract = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("TimelineFinished Call!"));
	}
}

void AWJ_Character::AddInteractActor(AWJ_InteractionActor* NewActor)
{
	if (!TraceComponent->GetIsNearActor(NewActor))
	{
		CanInteractActors.AddUnique(NewActor);
		NewActor->SetIsFocused(true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Actor Added!"));
	}
}

void AWJ_Character::RemoveInteractActor(AWJ_InteractionActor* NewActor)
{
	if (CanInteractActors.Contains(NewActor))
	{
		CanInteractActors.Remove(NewActor);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Actor Removed!"));
	}
}

void AWJ_Character::SpawnItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("SpawnItem is Called!"));

	if (TestActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("TestActor is Valid!"));

		FActorSpawnParameters SpawnParams;
		
		FVector SpawnLocation = FVector(0,0,50);
		//SpawnLocation.Z = 2000;
		FRotator SpawnRotation;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(TestActor->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
	}
}

void AWJ_Character::RepTestTrue()
{
	if(CurrentCamera)
	{
		FVector StartLocation = CurrentCamera->GetComponentLocation();
		FVector EndLocation = StartLocation + (CurrentCamera->GetForwardVector() * 1000);
		FHitResult _HitOut;
		FCollisionQueryParams _TraceParams;
		_TraceParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(_HitOut, StartLocation, EndLocation, ECC_Visibility, _TraceParams))
		{
			AWJ_Actor* WJActor = Cast<AWJ_Actor>(_HitOut.GetActor());

			if (WJActor && !(WJActor->bWidgetVisibility))
			{
				if(HasAuthority())
				{
					WJActor->SetWidgetVisibleTrue();
				}
				else
				{
					Server_RepTestTrue(WJActor);
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Widget is already Visible"));
			}
		}
	}
}

bool AWJ_Character::Server_RepTestTrue_Validate(AWJ_Actor* Actor)
{
	return true;
}

void AWJ_Character::Server_RepTestTrue_Implementation(AWJ_Actor* Actor)
{
	if (Actor)
	{
		Actor->SetWidgetVisibleTrue();
	}

}
//
//void AWJ_Character::RepTestFalse()
//{
//}
//
//bool AWJ_Character::Server_RepTestFalse_Validate(AWJ_Actor* Actor)
//{
//	return true;
//}
//
//void AWJ_Character::Server_RepTestFalse_Implementation(AWJ_Actor* Actor)
//{
//	
//}

void AWJ_Character::GetMultiActorControl()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AWJ_PlayerController* CurrentPC = Cast<AWJ_PlayerController>(PC);

	CurrentPC->MultiActor = MultiInteractionActor;
	CurrentPC->MultiInteractingActor();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Get Control!"));
}

void AWJ_Character::CheckArrayActor(int32 ProgressNum)
{
	AWJ_PlayerState* PS = Cast<AWJ_PlayerState>(GetPlayerState());

	if (PS)
	{
		PS->SetActorGuide(ProgressNum - 1, false);
		PS->SetActorGuide(ProgressNum, true);
	}
}

void AWJ_Character::SetIsCrouch(AActor* IActor)
{
	float Height = IActor->GetActorLocation().Z;

	if (Height > 60)
	{
		bIsCrouch = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Character Is Not Crouch"));
	}
	else
	{
		bIsCrouch = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Character Is Crouch"));
	}
}

bool AWJ_Character::GetIsCrouch()
{
	return bIsCrouch;
}

void AWJ_Character::FocusHold()
{
	AWJ_PlayerController* PC = Cast<AWJ_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		
	}
}

void AWJ_Character::SetupInteractionTrace()
{
	if (IsLocallyControlled() && TraceComponent)
	{
		TraceComponent->SetComponentTickEnabled(true);
	}
}

void AWJ_Character::DialogTest()
{
	AWJ_PlayerController* PC = Cast<AWJ_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC && bIsTestOverlaped)
	{
		PC->DialogTest();
	}
}
