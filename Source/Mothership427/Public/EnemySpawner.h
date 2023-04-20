#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MOTHERSHIP427_API AEnemySpawner : public AActor
{
    GENERATED_BODY()

public:
    AEnemySpawner();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "Spawner")
        TSubclassOf<AEnemyBase> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
        float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
        int32 MaxEnemies;

private:
    void SpawnEnemy();

    int32 GetEnemyCount() const;

    FTimerHandle SpawnTimerHandle;
};
