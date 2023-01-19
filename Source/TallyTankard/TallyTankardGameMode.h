// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TallyTankardGameMode.generated.h"

USTRUCT(BlueprintType)
struct FCountDownType {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Beat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName BeatStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName BeatEnd;

	float BeatTimer;
	float BeatStartTimer;
	float BeatEndTimer;



	FTimerHandle BeatHandle; //For Cooldown on Dash move
	FTimerHandle BeatStartHandle; //For Cooldown on Dash move
	FTimerHandle BeatEndHandle; //For Cooldown on Dash move



	FCountDownType() {
		Beat = FName(TEXT("Beat"));
		BeatStart = FName(TEXT("BeatStart"));
		BeatEnd = FName(TEXT("BeatEnd"));


	}
};


UCLASS()
class ATallyTankardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATallyTankardGameMode();


public:


	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USongComponent* Song1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USongComponent* Song2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USongComponent* Song3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class USongComponent*> SongStorage;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentBPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentSongLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentWindow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BeatsPerSecond;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BeatRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BeatPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SecondsPerTick;

	int NumBeats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool inBeat;

	UPROPERTY(BlueprintReadWrite)
		FCountDownType TimeManager;

	UFUNCTION()
		void AdvanceBeatTimer();

	UFUNCTION()
		void AdvanceBeatStartTimer();

	UFUNCTION()
		void AdvanceBeatEndTimer();

	UFUNCTION(BlueprintCallable)
		void BeginCountDown(FName Type);

};
