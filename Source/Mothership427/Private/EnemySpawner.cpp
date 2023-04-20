#pragma once
#include "EnemySpawner.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    SpawnInterval = 5.0f;
    MaxEnemies = 10;
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);
}

void AEnemySpawner::SpawnEnemy()
{
    if (GetEnemyCount() < MaxEnemies && EnemyClass)
    {
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();

        GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, SpawnLocation, SpawnRotation);
    }
}

int32 AEnemySpawner::GetEnemyCount() const
{
    int32 EnemyCount = 0;

    for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
    {
        EnemyCount++;
    }

    return EnemyCount;
}