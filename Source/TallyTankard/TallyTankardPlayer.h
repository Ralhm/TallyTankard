// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TallyTankardPlayer.generated.h"

UCLASS()
class TALLYTANKARD_API ATallyTankardPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATallyTankardPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SlamTankard();

	void RaiseTankard();

	int Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gx;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gz;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int GravitySum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString GyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString NewGyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<int> GravityArray;

	UFUNCTION(BlueprintCallable)
		void ParseGyroString();

	UFUNCTION(BlueprintCallable)
		void CalculateGravity(FString gyro);

	UFUNCTION(BlueprintCallable) //Check and compare the values in the GravityArray
		bool CheckRaise();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATallyTankardGameMode* GameMode;

};
