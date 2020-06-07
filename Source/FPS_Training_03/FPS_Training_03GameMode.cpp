// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPS_Training_03GameMode.h"
#include "FPS_Training_03HUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_Training_03GameMode::AFPS_Training_03GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS_Training_03HUD::StaticClass();
}
