// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveEnemySpawner.h"

// Sets default values for this component's properties
UWaveEnemySpawner::UWaveEnemySpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWaveEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Wave Spawner Ready!!"));
	
}


FWaveSpawnInfo UWaveEnemySpawner::GetWaveInfo(int32 WaveNum)
{
	
	FWaveSpawnInfo WaveInfo = WaveSpawnInfo[WaveNum];

	//UE_LOG(LogTemp, Warning, TEXT("It is wave %s"), WaveInfo.EnemiesInfo);
	//UE_LOG(LogTemp, Warning, TEXT("It is wave %d"), WaveSpawnInfo[WaneNum].Enem);

	return WaveInfo;
}

