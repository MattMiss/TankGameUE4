// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/Components/WaveEnemySpawner.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

class APAwnBase;
class APawnTank;
class APawnTurret;

ATankGameModeBase::ATankGameModeBase()
{
	
	

}


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameover(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			if (CurrentWave == WavesAmount - 1)
			{
				HandleGameover(true);
			}
			else
			{
				HandleNextWave();
			}
			
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	UGameplayStatics::GetAllActorsWithTag(this, "WaveSpawner", WaveSpawner);
	
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerTank) {
		SpawnLocation = PlayerTank->GetActorLocation();
		SpawnRotation = PlayerTank->GetActorRotation();
	}

	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (WaveSpawner.Num() == 1) {
		WaveSpawnerRef = Cast<UWaveEnemySpawner>(WaveSpawner[0]->GetRootComponent());
		SpawnNextWave(CurrentWave);
		CurrentWave++;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaveSpawner NOT HERE"));
	}

	if (PlayerControllerRef)
	{
		PlayerTank->SetCanMoveRotate(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerTank,
			&APawnTank::SetCanMoveRotate, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

		//PlayerControllerRef->SetPlayerEnableState(false);
		//FTimerHandle PlayerEnableHandle;
		//FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
		//	&APlayerControllerBase::SetPlayerEnableState, true);
		//GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}

	TargetTurrets = GetTargetTurretCount();
}

void ATankGameModeBase::HandleGameover(bool PlayerWon)
{
	GameOver(PlayerWon);

	if (PlayerControllerRef)
	{
		PlayerTank->SetCanMoveRotate(false);
		//PlayerControllerRef->SetPlayerEnableState(false);
	}
}

void ATankGameModeBase::HandleNextWave()
{
	NextRound(CurrentWave);

	if (WaveSpawner.Num() == 1) {
		WaveSpawnerRef = Cast<UWaveEnemySpawner>(WaveSpawner[0]->GetRootComponent());
		SpawnNextWave(CurrentWave);
		CurrentWave++;
	}

	if (PlayerControllerRef)
	{
		PlayerTank->SetCanMoveRotate(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerTank,
			&APawnTank::SetCanMoveRotate, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay + 2, false);

		//PlayerControllerRef->SetPlayerEnableState(false);
		//FTimerHandle PlayerEnableHandle;
		//FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
		//	&APlayerControllerBase::SetPlayerEnableState, true);
		//GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay + 2, false);
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}









