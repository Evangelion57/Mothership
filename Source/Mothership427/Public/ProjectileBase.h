#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class MOTHERSHIP427_API AProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    AProjectileBase();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Projectile")
        void SetDamage(float NewDamage);

    UFUNCTION(BlueprintCallable, Category = "Projectile")
        void SetSpeed(float NewSpeed);

    UFUNCTION(BlueprintCallable, Category = "Projectile")
        void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
        UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
        float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
        float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
        float LifeSpan;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
        UProjectileMovementComponent* ProjectileMovement;

private:

    
};
