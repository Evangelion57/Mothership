#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.h"
#include "ShipPawn.h"
#include "WeaponBase.generated.h"

UCLASS()
class MOTHERSHIP427_API AWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponBase();
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
        void Fire();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        TSubclassOf<AProjectileBase> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float MaxDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float Angle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float EnergyCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float ProjectileDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float ProjectileSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
        float Spread;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
        float SpawnOffset = 5.0f;

private:
    AActor* FindClosestEnemyInAngle();



    UPROPERTY()
        AShipPawn* OwnerPawn;

    float LastFireTime;
};
