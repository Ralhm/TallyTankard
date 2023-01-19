// Fill out your copyright notice in the Description page of Project Settings.

#include "TallyTankardPlayer.h"
#include "TallyTankardGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	PlayerInputComponent->BindAction("Raise", IE_Pressed, this, &ATallyTankardPlayer::RaiseTankard);
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

void ATallyTankardPlayer::RaiseTankard() {
	if (GameMode->inBeat) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Good!"));

		Score += 1;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bad!"));
	}
}