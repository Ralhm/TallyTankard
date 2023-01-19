// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TallyTankardGameMode.generated.h"


UCLASS()
class ATallyTankardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATallyTankardGameMode();

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USongComponent* CurrentSong;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class USongComponent*> SongStorage;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentBPM;


};
