// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorRotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P20230901_API UActorRotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorRotatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<USceneComponent*> Propellers;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void AddPropeller(USceneComponent* NewPropeller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float PropellerRotationSpeed = 3060;
		
};
