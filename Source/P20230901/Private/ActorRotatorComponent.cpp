// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRotatorComponent.h"

// Sets default values for this component's properties
UActorRotatorComponent::UActorRotatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorRotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorRotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	for (int32 i = 0; i < Propellers.Num(); ++i)
	{
		Propellers[i]->AddLocalRotation(FRotator(
			0,
			0,
			PropellerRotationSpeed * DeltaTime
		));
	}
}

void UActorRotatorComponent::AddPropeller(USceneComponent* NewPropeller)
{
	if (NewPropeller)
		Propellers.Add(NewPropeller);
}

