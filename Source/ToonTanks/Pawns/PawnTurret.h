// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool CanRoam = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TArray<FVector> PatrolPoints;

	int CurPatrolPointIndex = 1;
	bool bShouldMove = false;
	bool bShouldRotate = true;
	float RotationRate = 1.0f;
	FVector MoveDirection;
	FRotator RotationDirection;
	FTimerHandle FireRateTimerHandle;
	FTimerHandle PatrolRateTimerHandle;
	APawnTank* PlayerPawn;

	void CheckFireCondition();
	void Move();
	void Rotate(float DeltaTime);
	void CalculateMoveDirection(FVector Target);
	void CalculateRotateAngle(FVector Target, float DeltaTime);
	void CheckForPatrolPosition(float DeltaTime);
	void GoToNextPatrolPoint();
	float ReturnDistanceToTarget(FVector Target);
	FVector GetNextPatrolPoint();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void HandleDestruction() override;

	UFUNCTION(BlueprintCallable)
	void UnfreezeAtStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
};
