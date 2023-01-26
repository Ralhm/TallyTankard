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

	UFUNCTION(BlueprintCallable)
	bool SlamTankard();

	UFUNCTION(BlueprintCallable)
	bool RaiseTankard();

	//Debug functions for non-gyroscope based input
	UFUNCTION(BlueprintCallable)
	void RaiseTankardInput();

	//Debug functions for non-gyroscope based input
	UFUNCTION(BlueprintCallable)
	void SlamTankardInput();

	int Score;

	int numLines;

	//Let this be the location of the end of each line on the string. Loop backwards from this to get the most recent gyro lines
	TArray<int> linesIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool HitSlam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> GyroArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gx;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Gz;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int xAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int yAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int zAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		double xAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		double yAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		double zAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int GravitySum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString GyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString NewGyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<int> GravityArray;

	//Split up the string into parsable strings
	UFUNCTION(BlueprintCallable)
		void ParseGyroString();

	//Turn said strings into actual data
	UFUNCTION(BlueprintCallable)
		void CalculateGravity(FString gyro);

	//Calculate rotation from gravity
	UFUNCTION(BlueprintCallable)
		void CalculateRotation(FString gyro);

	UFUNCTION(BlueprintCallable) //Check and compare the values in the GravityArray
		bool CheckRaise();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATallyTankardGameMode* GameMode;

};
