// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "PawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


class PawnBase;

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	PlayerControllerRef->bShowMouseCursor = true;

}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	// Hide Player and Set not alive
	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCanRotate)
	{
		Rotate();
	}
	if (bCanMove)
	{
		Move();
	}
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		HitLocation = TraceHitResult.ImpactPoint;
		
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *TraceHitResult.ToString());
		if (true)	// TODO check to see if mouse is on screen or something
		{

		}
		
		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::FireBP);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APawnTank::FireReleaseBP);
}

void APawnTank::CalculateMoveInput(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	
}

void APawnTank::CalculateRotateInput(float Value)
{
	// Reverse Turn Direction While Backing Up
	if (MoveDirection.X < 0) 
	{
		Value *= -1;
	}
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::SetCanMoveRotate(bool Value)
{
	bCanMove = Value;
	bCanRotate = Value;
	SetCanFire(Value);
}
