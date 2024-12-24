// Fill out your copyright notice in the Description page of Project Settings.


#include "WJ_StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"

UWJ_StaticMeshComponent::UWJ_StaticMeshComponent()
{
	ColorNum = 0;
	ProgressiveNum = 0;

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT(TEXT("/Game/Develop/WooJoong/WJ_Material/WJ_ColorMaterial.WJ_ColorMaterial"));

	if (MAT.Object != NULL)
	{
		MaterialDynamic = (UMaterial*)MAT.Object;
	}
}

void UWJ_StaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MaterialDynamic)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(MaterialDynamic, this);
	}

	if (MaterialInstance)
	{
		this->SetMaterial(0, MaterialInstance);
	}
}

void UWJ_StaticMeshComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWJ_StaticMeshComponent, ColorNum);
}

void UWJ_StaticMeshComponent::InteractAction()
{
	SetColorNum();
}

void UWJ_StaticMeshComponent::SetColorNum()
{
	if (ColorNum < 3)
	{
		ColorNum = ColorNum + 1;
	}
	else
	{
		ColorNum = 0;
	}

	ChangeColor();
}

void UWJ_StaticMeshComponent::ChangeColor()
{
	switch (ColorNum)
	{
		case 0:
			MaterialInstance->SetVectorParameterValue("MaterialColor", FColor::Black);
			break;

		case 1:
			MaterialInstance->SetVectorParameterValue("MaterialColor", FColor::Red);
			break;

		case 2:
			MaterialInstance->SetVectorParameterValue("MaterialColor", FColor::Yellow);
			break;

		case 3:
			MaterialInstance->SetVectorParameterValue("MaterialColor", FColor::Blue);
			break;
	}
		
}
