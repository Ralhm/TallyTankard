// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TALLYTANKARD_API ATTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATTGameMode();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USongComponent* CurrentSong;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class USongComponent*> SongStorage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentBPM;

	
};
