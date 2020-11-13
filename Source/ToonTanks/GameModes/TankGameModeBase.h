// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks/Components/WaveEnemySpawner.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	
	APlayerControllerBase* PlayerControllerRef;
	UWaveEnemySpawner* WaveSpawnerRef;
	TArray<AActor*> WaveSpawner;
	int32 GetTargetTurretCount();
	void HandleGameStart();
	void HandleGameover(bool PlayerWon);
	void HandleNextWave();
	

public:
	ATankGameModeBase();

	void ActorDied(AActor* DeadActor);
	

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Waves")
	int32 CurrentWave = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Waves")
	int32 WavesAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SpawnLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator SpawnRotation;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void NextRound(int32 RoundNum);
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnNextWave(int32 WaveIndex);
};
