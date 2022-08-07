// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASpaceshipController::ASpaceshipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	RootComponent =  CapsuleComp;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CapsuleComp);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASpaceshipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceshipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Thrust
	const float CurrentAcc = -GetActorRotation().Pitch * DeltaTime * Acceleration;
	const float NewForwardSpeed = CurrentSpeed + CurrentAcc;
	CurrentSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

	const FVector ForwardMove = FVector(CurrentSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(ForwardMove, true);

	// Rotation
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

}

void ASpaceshipController::KeyPitch(float AxisValue)
{
	if (FMath::Abs(AxisValue) > MinAbsAxisValue)
	{
		ASpaceshipController::ProcessPitch(AxisValue * KeyToMouseOffset);
	}
}

void ASpaceshipController::KeyRoll(float AxisValue)
{
	if (FMath::Abs(AxisValue) > MinAbsAxisValue)
	{
		ASpaceshipController::ProcessRoll(AxisValue * KeyToMouseOffset);
	}
}

void ASpaceshipController::ProcessMouseYInput(float AxisValue)
{
	ASpaceshipController::ProcessPitch(AxisValue);
}

void ASpaceshipController::ProcessMouseXInput(float AxisValue)
{
	ASpaceshipController::ProcessRoll(AxisValue);
}

void ASpaceshipController::ProcessRoll(float AxisValue)
{
	float TargetRollSpeed = AxisValue * RollRateMultiplier;
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), RollInterpRate);
}

void ASpaceshipController::ProcessPitch(float AxisValue)
{
	float TargetPitchSpeed = AxisValue * PitchRateMultiplier;
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), PitchInterpRate);
}

void ASpaceshipController::Boost(float AxisValue)
{
	CurrentSpeed += BoostValue;
}

void ASpaceshipController::Fire()
{
	
}

// Called to bind functionality to input
void ASpaceshipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ASpaceshipController::ProcessMouseXInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASpaceshipController::ProcessMouseYInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpaceshipController::ProcessRoll);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpaceshipController::ProcessPitch);
	PlayerInputComponent->BindAxis("Boost", this, &ASpaceshipController::Boost);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceshipController::Fire);
}

