// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 5, 5));
	Box->SetGenerateOverlapEvents(true);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0;
	Movement->InitialSpeed = 1200.0f;
	Movement->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.f);

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), GetActorRotation(),FVector(1,1,1), true);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, GetActorLocation());
	Destroy();
}

