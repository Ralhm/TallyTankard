// Fill out your copyright notice in the Description page of Project Settings.


#include "TallyTankardPlayer.h"

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

	PlayerInputComponent->BindAction("Dive", IE_Pressed, this, &ATallyTankardPlayer::SlamTankard);
	PlayerInputComponent->BindAction("Dive", IE_Pressed, this, &ATallyTankardPlayer::RaiseTankard);
}

void ATallyTankardPlayer::SlamTankard() {

}

void ATallyTankardPlayer::RaiseTankard() {

}