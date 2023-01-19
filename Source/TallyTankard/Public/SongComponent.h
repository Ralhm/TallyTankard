// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "SongComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TALLYTANKARD_API USongComponent : public UAudioComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BPM;
	
};
