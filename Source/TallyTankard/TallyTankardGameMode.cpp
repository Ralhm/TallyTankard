// Copyright Epic Games, Inc. All Rights Reserved.

#include "TallyTankardGameMode.h"
#include "TallyTankardCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SongComponent.h"



ATallyTankardGameMode::ATallyTankardGameMode()
{

}


void ATallyTankardGameMode::ParseGyroString() {
	for (int i = 0; i < GyroString.Len(); i++) {
		if (GyroString[i] == '\n') {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("Newline Found!"));
		}
	}
}


void ATallyTankardGameMode::AdvanceBeatTimer() {
	NumBeats += 1;
	TimeManager.BeatTimer -= BeatRate;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("Beats: %d"), NumBeats));
	if (TimeManager.BeatTimer < 0) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Song Over!!"));
		GetWorldTimerManager().ClearTimer(TimeManager.BeatHandle);
	}
}
     
void ATallyTankardGameMode::AdvanceBeatStartTimer() {
	TimeManager.BeatStartTimer -= BeatRate;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("BeatStart!"));
	inBeat = true;
	if (TimeManager.BeatStartTimer < 0) {
		GetWorldTimerManager().ClearTimer(TimeManager.BeatStartHandle);
	}
}

void ATallyTankardGameMode::AdvanceBeatEndTimer() {
	TimeManager.BeatEndTimer -= BeatRate;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("BeatEnd!"));
	inBeat = false;
	if (TimeManager.BeatEndTimer < 0) {
		GetWorldTimerManager().ClearTimer(TimeManager.BeatEndHandle);
	}
}

void ATallyTankardGameMode::BeginCountDown(FName Type) {
	if (Type == "Beat") {

		BeatsPerSecond = CurrentBPM / 60;
		BeatRate = 1 / BeatsPerSecond;
		TimeManager.BeatTimer = CurrentSongLength;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Beat Rate: %f"), BeatRate));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BPM: %f"), CurrentBPM));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("BeatsPerSecond: %f"), BeatsPerSecond));

		GetWorldTimerManager().SetTimer(TimeManager.BeatHandle, this, &ATallyTankardGameMode::AdvanceBeatTimer, BeatRate, true);
	}
	if (Type == "BeatStart") {
		TimeManager.BeatStartTimer = CurrentSongLength;
		GetWorldTimerManager().SetTimer(TimeManager.BeatStartHandle, this, &ATallyTankardGameMode::AdvanceBeatStartTimer, BeatRate, true, BeatRate - CurrentWindow);
	}
	if (Type == "BeatEnd") {
		TimeManager.BeatEndTimer = CurrentSongLength;
		GetWorldTimerManager().SetTimer(TimeManager.BeatEndHandle, this, &ATallyTankardGameMode::AdvanceBeatEndTimer, BeatRate, true, BeatRate + CurrentWindow);
	}
}