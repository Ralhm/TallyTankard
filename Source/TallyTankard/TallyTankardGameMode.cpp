// Copyright Epic Games, Inc. All Rights Reserved.

#include "TallyTankardGameMode.h"
#include "TallyTankardCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SongComponent.h"



ATallyTankardGameMode::ATallyTankardGameMode()
{

}

void ATallyTankardGameMode::IncrementBeats() {
	if (NumBeats < TotalBeats) {

		DebugMapping++;
		if (DebugMapping == 3) {
			DebugMapping = 0;
		}

		NumBeats++;
	}

}
