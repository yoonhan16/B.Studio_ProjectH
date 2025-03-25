// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_PlayerController.h"
#include "WJ_Character.h"
#include "WJ_PlayerState.h"
#include "WJ_GameModeBase.h"
#include "WJ_HUD.h"
#include "WJ_GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/WJ_InteractingWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"

AWJ_PlayerController::AWJ_PlayerController()
{
	GDCMotionMatching = nullptr;
	CameraActionMappingContext = nullptr;
	CameraMoveAction = nullptr;
	CameraRotateAction = nullptr;

	bIsFocus = false;
	bIsReady = false;
	PlayerIndex = -1;
	bReplicates = true;
	bIsComplete = false;
	bIsTest = true;
	bIsGettingInfomation = false;

	IA_SpringArm = nullptr;

	Arrow_Interact = nullptr;
	SpringArm_Interact = nullptr;
	Camera_Interact = nullptr;

	ActionsWidget = nullptr;
}

void AWJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);

		if (HoldAction)
		{
			EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Triggered, this, &AWJ_PlayerController::FocusHold);
			EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Completed, this, &AWJ_PlayerController::UnlinkSubsystem);
		}

		if(CameraMoveAction)
		{
			EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Triggered, this, &AWJ_PlayerController::CameraMove);
		}
		
		if (CameraRotateAction)
		{
			EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &AWJ_PlayerController::CameraRotate);
		}
	}


	//if (Subsystem && HoldAction)
	//{
	//	Subsystem->AddMappingContext(InteractMappingContext, 0);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interact Mapping Contexted!"));

	//	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);

	//	EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Triggered, this, &AWJ_PlayerController::FocusHold);
	//}
}

void AWJ_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AWJ_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (0)
	{
		
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(PlayerCameraManager->GetCameraRotation());
		FVector EndLocation = StartLocation + (ForwardVector * 1000);
		FHitResult _HitOut;
		FCollisionQueryParams _TraceParams;
		
		GetWorld()->LineTraceSingleByChannel(_HitOut, StartLocation, EndLocation, ECC_Visibility, _TraceParams);

		if (_HitOut.GetActor())
		{
			//InteractionActor = Cast<AWJ_InteractionActor>(_HitOut.GetActor());

			AWJ_InteractionActor* HitActor = Cast<AWJ_InteractionActor>(_HitOut.GetActor());

			if (InteractionActor != nullptr)
			{
				InteractionActor->SetIsFocused(false);
				InteractionActor->SetWidgetVisible();
				InteractionActor->SetRenderCustomDepth();
			}

			if (HitActor)
			{
				InteractionActor = HitActor;
				InteractionActor->SetIsFocused(true);
				InteractionActor->SetWidgetVisible();
				InteractionActor->SetRenderCustomDepth();
			}

		}
	}
}

void AWJ_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWJ_PlayerController, PlayerIndex);
	DOREPLIFETIME(AWJ_PlayerController, PlayerName);
}

void AWJ_PlayerController::Look(const FInputActionValue& Value)
{
	if(IsInteract)
	{
		bIsFocus = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Is Can Focus!"));
	}
}

void AWJ_PlayerController::StopLook(const FInputActionValue& Value)
{
	if(IsInteract)
	{
		bIsFocus = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Is Can not Focus"));
	}
}

void AWJ_PlayerController::Observe(const FInputActionValue& Value)
{
}

void AWJ_PlayerController::FocusHold(const FInputActionInstance& Instance)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("FocusHold Called"));

	//if (InteractionActor && InteractionActor->IsFocusWidget)
	//{
		

		float Seconds = Instance.GetElapsedTime();

		//InteractionActor->IsFocusWidget->SetProgressPercent(Seconds);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Second is : % f"), Seconds));

		if(InteractionActor)
		{ 
			if (Seconds >= 1.0f)
			{
				//bIsComplete = true;
				//InteractionActor->Interacting();
				
				ACharacter* Chacracter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

				AWJ_Character* WJ_Character = Cast<AWJ_Character>(Chacracter);

				if (WJ_Character)
				{
					SpringArm_Character = WJ_Character->CurrentCameraBoom;
					Camera_Character = WJ_Character->CurrentCamera;

					Arrow_Interact = WJ_Character->Arrow_Interact;
					SpringArm_Interact = WJ_Character->SpringArm_Interact;
					Camera_Interact = WJ_Character->Camera_Interact;

					InteractingActor();
					//Interact_Camera();
				}

				UnlinkSubsystem();

				return;
			}

			InteractionActor->SetWidgetPercentage(Seconds);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("InteractionActor is Valid"));
		}
	//}
}

void AWJ_PlayerController::RequestPhaseChange(const FInputActionInstance& Instance)
{
	AWJ_GameModeBase* GM = Cast<AWJ_GameModeBase>(GetWorld()->GetAuthGameMode());

	float Seconds = Instance.GetElapsedTime();
	}

void AWJ_PlayerController::SetActionWidget(AWJ_InteractionActor* TargetActor)
{
	AWJ_HUD* Hud = Cast<AWJ_HUD>(GetHUD());

	if (Hud)
	{
		Hud->SetActionListWidget(TargetActor->GetActions());
	}

}

UWJ_ActionsWidget* AWJ_PlayerController::GetActionsWidget()
{
	if (!ActionsWidget)
	{
		if(!ActionsWidgetClass) return nullptr;

		ActionsWidget = CreateWidget<UWJ_ActionsWidget>(this, ActionsWidgetClass);

		if (ActionsWidget)
		{
			ActionsWidget->InitializeWidget(this);
			ActionsWidget->AddToViewport();
			//ActionsWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		SetShowMouseCursor(true);
	}

	return ActionsWidget;
	
}

void AWJ_PlayerController::InteractingActor()
{

	if (InteractionActor)
	{
		AWJ_HUD* Hud = Cast<AWJ_HUD>(GetHUD());

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (Subsystem && GDCMotionMatching)
		{
			Subsystem->RemoveMappingContext(GDCMotionMatching);

			CameraStartLoc = Arrow_Interact->GetComponentLocation();
			CameraStartRot = Arrow_Interact->GetComponentRotation();

			CameraEndLoc = InteractionActor->SpringArm_Interact->GetComponentLocation();
			CameraEndRot = InteractionActor->SpringArm_Interact->GetComponentRotation();

			SpringArm_Interact->bUsePawnControlRotation = false;
			SpringArm_Interact->bDoCollisionTest = false;

			Arrow_Interact->SetWorldLocation(CameraEndLoc);
			Arrow_Interact->SetWorldRotation(CameraEndRot);

			Camera_Character->SetActive(false);
			Camera_Interact->SetActive(true);
		}

		InteractionActor->OnInteract(this);
	}



	//UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//if (Subsystem)
	//{
	//	Subsystem->AddMappingContext(InteractMappingContext, 0);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interact Mapping Contexted!"));

	//	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);

	//	EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Triggered, this, &AWJ_PlayerController::FocusHold);

	//	bShowMouseCursor = true;
	//}
}

void AWJ_PlayerController::EndInteractingActor()
{
	if (bIsGettingInfomation)
	{
		AWJ_HUD* Hud = Cast<AWJ_HUD>(GetHUD());
	}
}

void AWJ_PlayerController::DisconnectingActor()
{
	if (InteractionActor && InteractingWidget)
	{
		InteractingWidget->RemoveFromParent();

		ACharacter* Chac = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		AWJ_Character* WJChac = Cast<AWJ_Character>(Chac);

		if (WJChac)
		{
			WJChac->EnableInput(this);
			
		}

		InteractionActor->Destroy();
		SetInputMode(FInputModeGameOnly());

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		Subsystem->RemoveMappingContext(InteractMappingContext);

		bShowMouseCursor = false;
	}
	else if (0)
	{

		SetInputMode(FInputModeGameOnly());

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		bShowMouseCursor = false;

		ACharacter* Chac = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		AWJ_Character* WJChac = Cast<AWJ_Character>(Chac);

		if (WJChac)
		{
			//WJChac->EnableInput(this);
			WJChac->EndInvestigating();
		}
	}
}

void AWJ_PlayerController::MultiInteractingActor()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(InteractMappingContext, 0);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interact Mapping Contexted!"));

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);

		bShowMouseCursor = true;
	}
}

void AWJ_PlayerController::CheckCharacter()
{
	// Using GetControlledPawn
	//ACharacter* Char = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AWJ_Character* WJChar = Cast<AWJ_Character>(GetPawn());
	if (WJChar)
	{
		FString CharName = WJChar->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Character is Valid , Character Name : %s"), *CharName));
	}

}

void AWJ_PlayerController::CheckArray(int32 ProgressNum)
{
	AWJ_Character* WJChar = Cast<AWJ_Character>(GetPawn());
	if (WJChar)
	{
		WJChar->CheckArrayActor(ProgressNum);
	}
}

void AWJ_PlayerController::Focusing(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Is Can Focus!"));

	if (IsInteract)
	{
		bIsFocus = true;
	}
}

void AWJ_PlayerController::StopFocus(const FInputActionValue& Value)
{
	if (IsInteract)
	{
		bIsFocus = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Is Can not Focus"));
	}
}

void AWJ_PlayerController::MovingActor(const FInputActionValue& Value)
{
	FVector2D ObserveVector = Value.Get<FVector2D>();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%f") , ObserveVector.X) );
	//UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);
	
	if (IA_SpringArm)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("SpringArm!"));

		FRotator NewRotator;
		FRotator CurRotator = IA_SpringArm->GetRelativeRotation();
		NewRotator.Pitch = (ObserveVector.Y * 5) + CurRotator.Pitch;
		NewRotator.Yaw = (ObserveVector.X * 5) + CurRotator.Yaw;

		IA_SpringArm->SetRelativeRotation(NewRotator);
	}
}

void AWJ_PlayerController::MovingMesh(const FInputActionValue& Value)
{
	FVector2D MovingVector = Value.Get<FVector2D>();

	if (MultiActor)
	{
		FRotator NewRotator;
		FRotator CurRotator = MultiActor->StaticMesh->GetRelativeRotation();
		NewRotator.Pitch = (MovingVector.Y * 5) + CurRotator.Pitch;
		NewRotator.Yaw = (MovingVector.X * 5) + CurRotator.Yaw;

		MultiActor->StaticMesh->SetRelativeRotation(NewRotator);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MovingMesh Called"));
	}
}

void AWJ_PlayerController::CameraMove(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (SpringArm_Interact && Arrow_Interact)
	{
		FRotator NewSpringRotator;
		FRotator NewArrowRotator;
		FRotator CurrentRotator = SpringArm_Interact->GetRelativeRotation();
		float NewPitch = FMath::Clamp((MoveVector.Y * 3) + CurrentRotator.Pitch, -44, 44);
		float NewYaw = (MoveVector.X * 5) + Arrow_Interact->GetRelativeRotation().Yaw;

		NewSpringRotator.Pitch = NewPitch;
		NewArrowRotator.Yaw = NewYaw;
			
		SpringArm_Interact->SetRelativeRotation(NewSpringRotator);
		Arrow_Interact->SetRelativeRotation(NewArrowRotator);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Camera Move Called, %f"), NewPitch));
	}
}

void AWJ_PlayerController::CameraRotate(const FInputActionValue& Value)
{
	FVector2D RotateVector = Value.Get<FVector2D>();

	if (Camera_Interact)
	{
		FRotator NewRotator;
		FRotator CurrentRotator = Camera_Interact->GetRelativeRotation();
		float NewPitch = FMath::Clamp((RotateVector.Y * 3) + CurrentRotator.Pitch, -30, 30);
		float NewYaw = FMath::Clamp((RotateVector.X * 3) + CurrentRotator.Yaw, -30, 30);

		NewRotator.Pitch = NewPitch;
		NewRotator.Yaw = NewYaw;

		Camera_Interact->SetRelativeRotation(NewRotator);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Camera Move Called, %f, %f"), NewPitch, NewYaw));
	}
}

bool AWJ_PlayerController::GetIsReady()
{
	return bIsReady;
}

void AWJ_PlayerController::SetIsGettingInfomation(bool NewGetting)
{
	bIsGettingInfomation = NewGetting;
}

void AWJ_PlayerController::SequanceChangeReady()
{
	if (HasAuthority())
	{
		AWJ_GameStateBase* GSB = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

		bIsReady = !bIsReady;

		//GM->
	}
	else
	{
		Server_SequanceChangeReady();
	}
}

bool AWJ_PlayerController::Server_SequanceChangeReady_Validate()
{
	return true;
}

void AWJ_PlayerController::Server_SequanceChangeReady_Implementation()
{
	
}

void AWJ_PlayerController::LinkSubsystem()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem && HoldAction)
	{
		Subsystem->AddMappingContext(InteractMappingContext, 0);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interact Mapping Contexted!"));

		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		if (MyCharacter)
		{
			MyCharacter->DisableInput(this);

			AWJ_Character* WJCharacter = Cast<AWJ_Character>(MyCharacter);

			if (WJCharacter && WJCharacter->TraceComponent)
			{
				InteractionActor = WJCharacter->TraceComponent->GetInteractionActor();
			}
		}

	}
}

void AWJ_PlayerController::UnlinkSubsystem()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->RemoveMappingContext(InteractMappingContext);
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Mapping is Removed"));

		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		if (MyCharacter)
		{
			MyCharacter->EnableInput(this);
		}

		if (InteractionActor)
		{
			InteractionActor->SetWidgetPercentage(0.0f);
			InteractionActor = nullptr;
		}

		bIsComplete = false;
	}
}

void AWJ_PlayerController::Interact_Camera()
{
	//GetPawn()->DisableInput(this);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem && GDCMotionMatching)
	{
		if(bIsTest)
		{
			Subsystem->RemoveMappingContext(GDCMotionMatching);
			Subsystem->AddMappingContext(CameraActionMappingContext, 0);
			bIsTest = false;

			CameraStartLoc = Arrow_Interact->GetComponentLocation();
			CameraStartRot = Arrow_Interact->GetComponentRotation();

			CameraEndLoc = InteractionActor->SpringArm_Camera->GetComponentLocation();
			CameraEndRot = InteractionActor->SpringArm_Camera->GetComponentRotation();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("End Location is : %s"), *CameraEndLoc.ToString()));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Before Arrow Location is : %s"), *Arrow_Interact->GetComponentLocation().ToString()));

			SpringArm_Interact->bUsePawnControlRotation = false;
			SpringArm_Interact->bDoCollisionTest = false;
			Arrow_Interact->SetWorldLocation(CameraEndLoc);
			Arrow_Interact->SetWorldRotation(CameraEndRot);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("After Arrow Location is : %s"), *Arrow_Interact->GetComponentLocation().ToString()));


			Camera_Character->SetActive(false);
			Camera_Interact->SetActive(true);

			AddItemStruct(InteractionActor->ItemStruct);
		}
		else
		{
			SpringArm_Interact->bUsePawnControlRotation = true;
			Arrow_Interact->SetWorldLocation(CameraStartLoc);
			Arrow_Interact->SetWorldRotation(CameraStartRot);
			SpringArm_Interact->bDoCollisionTest = true;

			Subsystem->RemoveMappingContext(CameraActionMappingContext);
			Subsystem->AddMappingContext(GDCMotionMatching, 0);

			Camera_Character->SetActive(true);
			Camera_Interact->SetActive(false);

			bIsTest = true;
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interact_Camera is Called"));
}

void AWJ_PlayerController::GetPlayersNum()
{
	AWJ_GameStateBase* GS = Cast<AWJ_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	if (GS)
	{
		GS->GetPlayersNum();
	}
	
}

void AWJ_PlayerController::DialogTest()
{
	AWJ_HUD* HUD = Cast<AWJ_HUD>(GetHUD());

	if (HUD)
	{
		HUD->RevealInfomation();
	}
}

void AWJ_PlayerController::SetPlayerIndex(int32 NewIndex)
{
	if (HasAuthority())
	{
		Multi_SetPlayerIndex(NewIndex);
	}
	else
	{
		Server_SetPlayerIndex(NewIndex);
	}
}

bool AWJ_PlayerController::Server_SetPlayerIndex_Validate(int32 NewIndex)
{
	return true;
}

void AWJ_PlayerController::Server_SetPlayerIndex_Implementation(int32 NewIndex)
{
	Multi_SetPlayerIndex(NewIndex);
}

bool AWJ_PlayerController::Multi_SetPlayerIndex_Validate(int32 NewIndex)
{
	return true;
}

void AWJ_PlayerController::Multi_SetPlayerIndex_Implementation(int32 NewIndex)
{
	PlayerIndex = NewIndex;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Index is : %d"), PlayerIndex));
}

int32 AWJ_PlayerController::GetPlayerIndex()
{
	return PlayerIndex;
}

void AWJ_PlayerController::GetPlayerIndexGm()
{
	AWJ_GameModeBase* WJ_GM = Cast<AWJ_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (WJ_GM)
	{
		PlayerIndex = WJ_GM->GetPlayerIndex(this);
	}
}

void AWJ_PlayerController::SetPlayerControllerID(int32 NewID)
{
	PlayerIndex = NewID;
}

bool AWJ_PlayerController::Server_CallInEar_Validate(AWJ_PlayerController* MyController)
{
	return true;
}

void AWJ_PlayerController::Server_CallInEar_Implementation(AWJ_PlayerController* MyController)
{
	TArray<AActor*> PlayerControllers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWJ_PlayerController::StaticClass(), PlayerControllers);

	for (auto& PlayerController : PlayerControllers)
	{
		AWJ_PlayerController* WJ_PlayerController = Cast<AWJ_PlayerController>(PlayerController);

		if (WJ_PlayerController)
		{
			if (WJ_PlayerController != MyController)
			{
				WJ_PlayerController->Client_CallInEar();
			}
		}
	}
}

bool AWJ_PlayerController::Client_CallInEar_Validate()
{
	return true;
}

void AWJ_PlayerController::Client_CallInEar_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Client CallInEar is Called!"));
}

void AWJ_PlayerController::AddItemStruct(FItemStruct NewItemStruct)
{
	AWJ_PlayerState* PS = Cast<AWJ_PlayerState>(GetPlayerState<APlayerState>());
	
	if(PS)
	{
		FItemCheckerStruct ItemCheckerStruct = FItemCheckerStruct();
		ItemCheckerStruct.ItemStruct = NewItemStruct;
		//ItemCheckerStruct.IsChecked = true;

		PS->AddItemChecker(ItemCheckerStruct);
	}
}

void AWJ_PlayerController::SubmitClueToProfiler(const FClueMessage& ClueMessage)
{

}

bool AWJ_PlayerController::Server_SubmitClueToProfiler_Validate(const FClueMessage& ClueMessage)
{
	return true;
}

void AWJ_PlayerController::Server_SubmitClueToProfiler_Implementation(const FClueMessage& ClueMessage)
{

}

bool AWJ_PlayerController::Client_ReceiveClueFromInvestigator_Validate(const FClueMessage& ClueMessage)
{
	return true;
}

void AWJ_PlayerController::Client_ReceiveClueFromInvestigator_Implementation(const FClueMessage& ClueMessage)
{

}

FClueMessage AWJ_PlayerController::CreateClueMessageFromClue(const FClueData& Clue, const FString& CustomDescription)
{
	FClueMessage Message;

	Message.ClueID = Clue.ClueID;
	Message.ClueTitle = Clue.Title;
	Message.CustomDescription = CustomDescription;
	Message.SenderPlayerID = PlayerIndex;
	Message.SentTime = FDateTime::Now();

	return Message;
}

void AWJ_PlayerController::SwapPlayerRole()
{
	AWJ_PlayerState* PS = GetPlayerState<AWJ_PlayerState>();
	
	AWJ_GameStateBase* GS = Cast<AWJ_GameStateBase>(GetWorld()->GetGameState());

	if (!PS || !GS) return;

	if (!GS->IsSingleGame()) return;

	if (PS->GetPlayerRole() == EPlayerRole::Profiler)
	{
		PS->SetPlayerRole(EPlayerRole::Investigator);
	}
	else
	{
		PS->SetPlayerRole(EPlayerRole::Profiler);
	}
}
