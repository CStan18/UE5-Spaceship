// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceshipController.generated.h"

UCLASS()
class SPACESHIP_API ASpaceshipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceshipController();
	
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float Acceleration = 60.f;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float MinSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float MaxSpeed = 10000.f;
	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float CurrentSpeed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float BoostValue = 250.f;

	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float CurrentYawSpeed;
	
	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float CurrentPitchSpeed;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float PitchRateMultiplier = 200.f;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float PitchInterpRate = .2f;

	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float CurrentRollSpeed;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float RollRateMultiplier = 200.f;
	UPROPERTY(EditAnywhere, Category = "Flight Speeds")
	float RollInterpRate = .2f;

	// To balance mouse vs key inputs
	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float KeyToMouseOffset = 2.f;

	// Reduces axis function calls by checking if key is pressed
	UPROPERTY(VisibleAnywhere, Category = "Flight Speeds")
	float MinAbsAxisValue = .2f;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void KeyPitch(float AxisValue);
	void KeyRoll(float AxisValue);

	void ProcessMouseYInput(float AxisValue);
	void ProcessMouseXInput(float AxisValue);

	void ProcessRoll(float AxisValue);
	void ProcessPitch(float AxisValue);

	void Boost(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
