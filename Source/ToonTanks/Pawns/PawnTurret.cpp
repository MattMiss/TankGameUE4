// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	UE_LOG(LogTemp, Warning, TEXT("Starting Turret"))
}

void APawnTurret::UnfreezeAtStart()
{
	if (CanRoam)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can Roam"))
		//UE_LOG(LogTemp, Warning, TEXT("%d"), PatrolPoints.Num())
		if (PatrolPoints.Num() > 0)
		{
			PatrolPoints[0] = GetActorLocation();
			CalculateMoveDirection(PatrolPoints[CurPatrolPointIndex]);
			CalculateRotateAngle(PatrolPoints[CurPatrolPointIndex], GetWorld()->GetDeltaSeconds());
			bShouldMove = true;
			bShouldRotate = true;

			UE_LOG(LogTemp, Error, TEXT("Patrol Point Index: "));
			UE_LOG(LogTemp, Error, TEXT("%d"), CurPatrolPointIndex);
		}
	}

}

void APawnTurret::HandleDestruction()
{
	// Call base pawn class HandleDestruction to play effects
	Super::HandleDestruction();
	Destroy();
}


// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldRotate)
	{
		//CalculateRotateAngle(PatrolPoints[0]);
		Rotate(DeltaTime);
	}
	

	if (CanRoam && bShouldMove)
	{
		CheckForPatrolPosition(DeltaTime);
		Move();
		//UE_LOG(LogTemp, Warning, TEXT("Moving"));
	}

	if (!PlayerPawn || ReturnDistanceToTarget(PlayerPawn->GetActorLocation()) > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
	
}

void APawnTurret::CheckFireCondition()
{
	// If player == null || is Dead, then stop firing!
	if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}

	// If player IS in range, then fire!
	if (ReturnDistanceToTarget(PlayerPawn->GetActorLocation()) <= FireRange)
	{
		FireBP();
	}
}

float APawnTurret::ReturnDistanceToTarget(FVector Target)
{
	if (!PlayerPawn)
	{
		return 0.f;
	}

	return FVector::Dist(Target, GetActorLocation());
}

void APawnTurret::CalculateMoveDirection(FVector Target)
{
	MoveDirection = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Target) * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MoveDirection.ToString());
	

}

void APawnTurret::CalculateRotateAngle(FVector Target, float DeltaTime)
{
	FRotator TargetRotation = FVector(Target - GetActorLocation()).Rotation();
	RotationDirection = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 1.0f);
}

void APawnTurret::Move()
{
	AddActorWorldOffset(MoveDirection, false);
}

void APawnTurret::Rotate(float DeltaTime)
{
	SetActorRotation(RotationDirection);
}

FVector APawnTurret::GetNextPatrolPoint()
{
	CurPatrolPointIndex++;
	if (CurPatrolPointIndex == PatrolPoints.Num())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Patrol Point Reset to 0"));
		CurPatrolPointIndex = 0;
	}
	//UE_LOG(LogTemp, Error, TEXT("Patrol Point Index: "));
	//UE_LOG(LogTemp, Error, TEXT("%d"), CurPatrolPointIndex);

	return PatrolPoints[CurPatrolPointIndex];
}


void APawnTurret::CheckForPatrolPosition(float DeltaTime)
{
	float DistanceCheck = ReturnDistanceToTarget(PatrolPoints[CurPatrolPointIndex]);
	//UE_LOG(LogTemp, Error, TEXT("Distance Check: %d"), UKismetMathLibrary::Abs(DistanceCheck));
	//UE_LOG(LogTemp, Error, TEXT("%s"), *MoveDirection.ToString());


	if (UKismetMathLibrary::Abs(DistanceCheck) < 10)
	{
		//UE_LOG(LogTemp, Error, TEXT("Distance is Under 10!"));
		bShouldMove = false;

		// This advances the patrol point index by 1
		CalculateRotateAngle(GetNextPatrolPoint(), DeltaTime);

		float MoveDelay = FMath::RandRange(1.0f, 3.0f);
		GetWorldTimerManager().SetTimer(PatrolRateTimerHandle, this, &APawnTurret::GoToNextPatrolPoint, MoveDelay, false);
	}
}

void APawnTurret::GoToNextPatrolPoint()
{
	//UE_LOG(LogTemp, Error, TEXT("Current Point is %d"), CurPatrolPointIndex);
	CalculateMoveDirection(PatrolPoints[CurPatrolPointIndex]);
	//UE_LOG(LogTemp, Error, TEXT("Current Point is now %d"), CurPatrolPointIndex);
	bShouldMove = true;
}