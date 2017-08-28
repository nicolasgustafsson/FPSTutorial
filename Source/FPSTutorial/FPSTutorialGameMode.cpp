// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSTutorialGameMode.h"
#include "FPSTutorialHUD.h"
#include "FPSTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSTutorialGameMode::AFPSTutorialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSTutorialHUD::StaticClass();
}
