#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

void AMyPlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (LocalPlayerSystem && DefaultMappingContext)
	{
		LocalPlayerSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
