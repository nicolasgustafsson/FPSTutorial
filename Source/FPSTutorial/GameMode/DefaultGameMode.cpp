// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DefaultGameMode.h"
#include "../Player/FPSTutorialHUD.h"
#include "Player/FPSTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADefaultGameMode::ADefaultGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSTutorialHUD::StaticClass();
}
