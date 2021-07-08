// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyActionRPGGameMode.h"
#include "MyActionRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyActionRPGGameMode::AMyActionRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
