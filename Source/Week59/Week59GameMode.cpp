// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Week59GameMode.h"
#include "Week59PlayerController.h"
#include "Week59Character.h"
#include "UObject/ConstructorHelpers.h"

AWeek59GameMode::AWeek59GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWeek59PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}