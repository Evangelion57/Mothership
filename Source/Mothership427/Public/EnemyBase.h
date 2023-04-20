#pragma once
#include "CoreMinimal.h"
#include "ShipPawn.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "EnemyBase.generated.h"

UCLASS()
class MOTHERSHIP427_API AEnemyBase : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    AEnemyBase();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
        float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
        float MovementSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
        float Price;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
        float Exp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
        float DamageOverlap;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* EnemyMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
        USphereComponent* CollisionSphere;

    UFUNCTION()
        void MoveTowardsPlayer(float DeltaTime);

    UFUNCTION()
        void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
            AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, Category = "Enemy")
        void TakeDamage(float DamageAmount, UPrimitiveComponent* HitComponent);

    UFUNCTION(BlueprintCallable, Category = "Enemy")
        void Die();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
        float GetPrice() const;

private:
    AShipPawn* Player;
};
