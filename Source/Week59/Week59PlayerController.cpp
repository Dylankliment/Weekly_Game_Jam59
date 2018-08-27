// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Week59PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Week59Character.h"
#include "Engine/World.h"

AWeek59PlayerController::AWeek59PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AWeek59PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		RotateCharacter();
	}
}

void AWeek59PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AWeek59PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AWeek59PlayerController::OnSetDestinationReleased);

	InputComponent->BindAxis("MoveForward", this, &AWeek59PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AWeek59PlayerController::MoveRight);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AWeek59PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AWeek59PlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AWeek59PlayerController::OnResetVR);
}

void AWeek59PlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AWeek59PlayerController::RotateCharacter()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{

	}
	else
	{


		if (AWeek59Character* MyPawn = Cast<AWeek59Character>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{

				FVector MouseLocation, MouseDirection, MouseLocationEnd;
				FHitResult HitResult;

				this->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

				MouseLocationEnd = (MouseDirection * 10000) + MouseLocation;

				FCollisionQueryParams TraceSettings;
				FCollisionResponseParams TraceResponses;

				if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, MouseLocationEnd, ECollisionChannel::ECC_WorldStatic, TraceSettings, TraceResponses) == true)
				{
					FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), HitResult.ImpactPoint);

					MyPawn->SetActorRotation(FRotator(GetControlRotation().Pitch, NewRotation.Yaw, GetControlRotation().Roll));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Didn't work"));
				}
				/*UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());*/
			}
		}




		// Trace to see what is under the mouse cursor
		//FHitResult Hit;
		//GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		//if (Hit.bBlockingHit)
		//{
		//	// We hit something, move there
		//	UE_LOG(LogTemp, Error, TEXT("Failing to find pawn"));
		//	SetNewMoveDestination(Hit.ImpactPoint);
		//}
	}
}

void AWeek59PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AWeek59PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AWeek59PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AWeek59PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}


void AWeek59PlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			MyPawn->AddMovementInput(Direction, Value);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find Pawn in MoveForward"));
		}
	}
}

void AWeek59PlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			MyPawn->AddMovementInput(Direction, Value);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find Pawn in MoveRight"));
		}
	}
}