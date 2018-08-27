// Fill out your copyright notice in the Description page of Project Settings.

#include "PassAFistCharacter.h"
#include "Components/InputComponent.h"



// Sets default values
APassAFistCharacter::APassAFistCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APassAFistCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassAFistCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APassAFistCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

