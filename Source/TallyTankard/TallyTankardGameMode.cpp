// Copyright Epic Games, Inc. All Rights Reserved.

#include "TallyTankardGameMode.h"
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

FString ATallyTankardGameMode::CurrentBeatCheck() {
	if (DebugMapping == 0 || DebugMapping == 1) {
		return "Slam";
	}
	else if (DebugMapping == 2) {
		return "Drink";
	}
	else {
		return "NULL";
	}
}

FString ATallyTankardGameMode::GetCurrentBeatMap(int index) {
	return BeatMap[index];
}

