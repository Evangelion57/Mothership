// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mothership427GameMode.h"
#include "Mothership427Pawn.h"

AMothership427GameMode::AMothership427GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AMothership427Pawn::StaticClass();
}

