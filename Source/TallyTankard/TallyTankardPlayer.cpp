// Fill out your copyright notice in the Description page of Project Settings.

#include "TallyTankardPlayer.h"
#include "TallyTankardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


//Make an array of ints, these ints are the sums of the absolute values of the gravitational x y and zforces experienced by the thing
//

// Sets default values
ATallyTankardPlayer::ATallyTankardPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATallyTankardPlayer::BeginPlay()
{
	Super::BeginPlay();

	GameMode = (ATallyTankardGameMode*)UGameplayStatics::GetGameMode(GetWorld());
	
}

// Called every frame
void ATallyTankardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATallyTankardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Slam", IE_Pressed, this, &ATallyTankardPlayer::SlamTankard);
	//PlayerInputComponent->BindAction("Raise", IE_Pressed, this, &ATallyTankardPlayer::RaiseTankard);
}

void ATallyTankardPlayer::ParseGyroString() {
	//NewGyroString.TrimStart();
	GravityArray.Empty();
	GyroArray.Empty();
	numLines = 0;
	NewGyroString = "";
	for (int i = 0; i < GyroString.Len(); i++) {
		
		NewGyroString.AppendChar(GyroString[i]);
		if (GyroString[i] == '\n') {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hit a newline!"));
			GyroArray.Add(NewGyroString);
			numLines++;
			linesIndex.Add(i);

			//CalculateGravity(NewGyroString);
			NewGyroString = "";



			/*
			if (j == 4) { //I only care about the most recent readings, so if there are more than 4, just break at 4
				break;
			}
			*/

			

			
		}
	}
	
	//CalculateGravity(GyroArray[0]);
	
	int j = 0;
	for (int i = GyroArray.Num() - 1; i >= 0; i--) {
		CalculateGravity(GyroArray[i]);
		j++;
		if (j == 4) {
			break;
		}
	}
	

	



}

void ATallyTankardPlayer::CalculateGravity(FString gyro) {
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::White, gyro);
	FString ls;
	FString rsx;
	FString rsy;
	FString rsz;

	gyro.Split("gx = ", &ls, &rsx);
	rsx = rsx.TrimStart();
	Gx = UKismetStringLibrary::Conv_StringToInt(rsx);

	rsx.Split("gy = ", &ls, &rsy);
	rsy = rsy.TrimStart();
	Gy = UKismetStringLibrary::Conv_StringToInt(rsy);



	rsy.Split("gz = ", &ls, &rsz);
	rsz = rsz.TrimStart();
	Gz = UKismetStringLibrary::Conv_StringToInt(rsz);



	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Black, FString::Printf(TEXT("Gx: %d"), Gx));
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Black, FString::Printf(TEXT("Gy: %d"), Gy));
	//GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Black, FString::Printf(TEXT("Gz: %d"), Gz));
	GravitySum = abs(Gx) + abs(Gy) + abs(Gz);
	GravityArray.Add(GravitySum);
}

bool ATallyTankardPlayer::CheckRaise() {
	bool heldStill = false;
	if (GravityArray.Num() == 0) { //failsafe
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit Failsafe 0!"));
		return false;
	}
	else if (GravityArray.Num() == 1) { //failsafe in case we only have one queued up
		if (GravityArray[0] > 1500) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Hit Failsafe 1!"));
			return true;
		}
	}
	else if (GravityArray.Num() == 2) { //failsafe in case we only have 2 queued up
		if (GravityArray[0] > 1500 || GravityArray[1] > 1500) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hit Failsafe 2!"));
			return true;
		}
	}
	else {
		for (int i = 1; i < GravityArray.Num() - 1; i++) { //Check if the player has held the tankard still in recent seconds
			if (GravityArray[i] < 2000) {
				heldStill = true;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, TEXT("Held Still Found!"));
				break;
			}
		}
		if (heldStill) {
			if (GravityArray[0] > 1500 || GravityArray[1] > 1500) { //if 2 of the most recent checks are high then return true 
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Raise Successfull!"));
				return true;
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Failed to Raise Properly!"));
				return false;
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Failed to Hold Still!"));
			return false;
		}

	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Final False!"));
	return false;
}

void ATallyTankardPlayer::SlamTankard() {
	if (GameMode->inBeat) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));

		Score += 1;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
	}
}

bool ATallyTankardPlayer::RaiseTankard() {
	if (GameMode->inBeat) {
		if (CheckRaise()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));
			Score += 1;
			return true;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Miss!"));
			return false;
		}

		

		

		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
		return false;
	}
}