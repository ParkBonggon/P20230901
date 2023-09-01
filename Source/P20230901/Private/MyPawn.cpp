#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ActorRotatorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20, 20, 20));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.257852f, -21.f, 0.986638f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.257852f, 21.0f, 0.986638f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->AddLocalOffset(FVector(300.0f, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	ActorRotatorComponent = CreateDefaultSubobject<UActorRotatorComponent>(TEXT("ActorRotatorComponent"));

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedBoost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::EnhancedUnBoost);

		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedFire);

		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedPitchAndRoll);

	}
}

void AMyPawn::EnhancedBoost(const FInputActionValue& Value)
{
	BoostValue = 1.0f;
}

void AMyPawn::EnhancedUnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5;
}

void AMyPawn::EnhancedFire(const FInputActionValue& Value)
{
	if (RocketTemp != nullptr)
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(
			RocketTemp,
			Arrow->GetComponentLocation(),
			Arrow->GetComponentRotation());
}

void AMyPawn::EnhancedPitchAndRoll(const FInputActionValue& Value)
{
	FVector2D VectorValue = Value.Get<FVector2D>();

	double Pitch = VectorValue.Y * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;
	double Roll = VectorValue.X * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

	FRotator PitchRotation(Pitch, 0, 0);
	FRotator RollRotation(0, 0, Roll);

	AddActorLocalRotation(PitchRotation);
	AddActorLocalRotation(RollRotation);

}

