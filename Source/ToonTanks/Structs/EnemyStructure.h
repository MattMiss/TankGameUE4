#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/PawnBase.h"

#include "EnemyStructure.generated.h"

class APawnBase;

USTRUCT(BlueprintType)
struct FEnemySpawn
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        APawnBase* Enemy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        FRotator Rotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        bool CanRoam;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        bool CanRoam2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
        TArray<FVector> PatrolPoints;
};