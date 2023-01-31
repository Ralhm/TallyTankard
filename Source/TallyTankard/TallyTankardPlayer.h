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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties") //Should be high but not too high, like somewhere between 2000 and 6000
		float ForceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties") //Max force player should be allowed to exert to register as 'holding still', should be less than ForceThreshold
		float HoldStillThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties") //What's the angle the tankard should be at to register a drink? Should be between 0 and 1
		float DrinkThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		float MaxDrunkenness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		float MaxCamaraderie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int Drunkenness;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int Camaraderie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		bool HitSlam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int numLinestoCompare;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
	TArray<FString> GyroArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int Gx;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int Gy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int Gz;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int xAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int yAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int zAccel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		double xAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		double yAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		double zAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		int GravitySum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		FString GyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		FString NewGyroString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Physics")
		TArray<int> GravityArray;

	int numLines;

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

	UFUNCTION(BlueprintCallable)
		void IncreaseDrunkenness();

	UFUNCTION(BlueprintCallable)
		void IncreaseCamaraderie();

	UFUNCTION(BlueprintCallable)
		void DecreaseDrunkenness();

	UFUNCTION(BlueprintCallable)
		void DecreaseCamaraderie();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATallyTankardGameMode* GameMode;

};
