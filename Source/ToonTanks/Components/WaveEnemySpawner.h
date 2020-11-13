// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "GameFramework/Actor.h"
#include "WaveEnemySpawner.generated.h"

class APawnBase;

UENUM(BlueprintType)
enum EnemyType
{
	Turret     UMETA(DisplayName = "Turret"),
	Cannon      UMETA(DisplayName = "Cannon"),
};


USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APawnBase> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EnemyType> EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator SpawnRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanRoam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> PatrolPoints;
};



USTRUCT(BlueprintType)
struct FWaveSpawnInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<struct FEnemySpawnInfo> EnemiesInfo;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UWaveEnemySpawner : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWaveEnemySpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TArray<struct FWaveSpawnInfo> WaveSpawnInfo;

	FWaveSpawnInfo GetWaveInfo(int32 WaveNum);
};
