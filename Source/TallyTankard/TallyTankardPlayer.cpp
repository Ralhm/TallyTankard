// Fill out your copyright notice in the Description page of Project Settings.

#include "TallyTankardPlayer.h"
#include "TallyTankardGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


//MAPPING NOTES
//To map the beats to certain actions, make an array of strings to represent each beat (Slam, Drink, Raise)
//For every beat, check the string and see if the input matches the desired input
//Compare the beat num with the string index to get the desired beat input

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

	//PlayerInputComponent->BindAction("Slam", IE_Pressed, this, &ATallyTankardPlayer::SlamTankardInput);
	PlayerInputComponent->BindAction("Raise", IE_Pressed, this, &ATallyTankardPlayer::RaiseTankardInput);
}

void ATallyTankardPlayer::ParseGyroString() {
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

			NewGyroString = "";
	
		}
	}
	
	int j = 0;
	for (int i = GyroArray.Num() - 1; i >= 0; i--) {
		CalculateGravity(GyroArray[i]); //Calculate gravity and rotation for each line of the array
		CalculateRotation(GyroArray[i]);
		j++;
		if (j == numLinestoCompare) {
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

	GravitySum = abs(Gx) + abs(Gy) + abs(Gz);
	GravityArray.Add(GravitySum);
}

void ATallyTankardPlayer::CalculateRotation(FString gyro) {
	int xFactor = 0, yFactor = 0, zFactor = 0;
	FString ls;
	FString rsx;
	FString rsy;
	FString rsz;

	gyro.Split("ax = ", &ls, &rsx);
	rsx = rsx.TrimStart();
	xAccel = UKismetStringLibrary::Conv_StringToInt(rsx);

	rsx.Split("ay = ", &ls, &rsy);
	rsy = rsy.TrimStart();
	yAccel = UKismetStringLibrary::Conv_StringToInt(rsy);

	rsy.Split("az = ", &ls, &rsz);
	rsz = rsz.TrimStart();
	zAccel = UKismetStringLibrary::Conv_StringToInt(rsz);


	xAngle = atan(xAccel / (sqrt(FMath::Square(yAccel) + FMath::Square(zAccel))));
	yAngle = atan(yAccel / (sqrt(FMath::Square(xAccel) + FMath::Square(zAccel))));
	zAngle = atan(sqrt(FMath::Square(xAccel) + FMath::Square(yAccel)) / zAccel);

	xAngle *= 180.00;   yAngle *= 180.00;   zAngle *= 180.00;
	xAngle /= 3.141592; yAngle /= 3.141592; zAngle /= 3.141592;


}

bool ATallyTankardPlayer::CheckRaise() {
	bool heldStill = false;
	if (GravityArray.Num() == 0) { //failsafe
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit Failsafe 0!"));
		return false;
	}
	else if (GravityArray.Num() == 1) { //failsafe in case we only have one queued up
		if (GravityArray[0] > ForceThreshold) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Hit Failsafe 1!"));
			return true;
		}
	}
	else if (GravityArray.Num() == 2) { //failsafe in case we only have 2 queued up
		if (GravityArray[0] > ForceThreshold || GravityArray[1] > ForceThreshold) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hit Failsafe 2!"));
			return true;
		}
	}
	else {
		for (int i = 1; i < GravityArray.Num() - 1; i++) { //Check if the player has held the tankard still in recent seconds
			if (GravityArray[i] < ForceThreshold) {
				heldStill = true;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, TEXT("Held Still Found!"));
				break;
			}
		}
		if (heldStill) {
			if (GravityArray[0] > ForceThreshold || GravityArray[1] > ForceThreshold) { //if 2 of the most recent checks are high then return true 
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

bool ATallyTankardPlayer::SlamTankard() {
	if (GameMode->inBeat) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));
		return true;
		Score += 1;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
		return false;
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

void ATallyTankardPlayer::RaiseTankardInput() {
	if (GameMode->inBeat) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));
		Score += 1;

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
		
	}
}


void ATallyTankardPlayer::SlamTankardInput() {
	if (GameMode->inBeat) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));

		Score += 1;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
	}
}

void ATallyTankardPlayer::IncreaseDrunkenness() {
	if (Drunkenness < MaxDrunkenness) {
		Drunkenness++;
	}
}

void ATallyTankardPlayer::IncreaseCamaraderie() {
	if (Camaraderie < MaxCamaraderie) {
		Camaraderie++;
	}
}

void ATallyTankardPlayer::DecreaseDrunkenness() {
	if (Drunkenness > 0) {
		Drunkenness--;
	}
}

void ATallyTankardPlayer::DecreaseCamaraderie() {
	if (Camaraderie > 0) {
		Camaraderie--;
	}
}