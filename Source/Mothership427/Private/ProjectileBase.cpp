#pragma once

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyBase.h"
#include "ShipPawn.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    RootComponent = ProjectileMesh;
    ProjectileMesh->SetNotifyRigidBodyCollision(true);
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

    // Movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 20.0f;
    ProjectileMovement->MaxSpeed = 20.0f;
    ProjectileMovement->ProjectileGravityScale = 0.0f; // No gravity


    Speed = 20.0f;
    LifeSpan = 10.0f;
    Damage = 10.0f;
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(LifeSpan);

    UE_LOG(LogTemp, Warning, TEXT("Projectile created"));
}

void AProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());


    if ( !(OtherActor == this) && OtherActor->IsA(AProjectileBase::StaticClass()))
    {
        Destroy();
    }

    if (OtherActor->IsA(AEnemyBase::StaticClass()))
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
        if (Enemy)
        {
            Enemy->TakeDamage(Damage, OtherComp);
        }
    }
    else if (OtherActor->IsA(AShipPawn::StaticClass()))
    {
        AShipPawn* Ship = Cast<AShipPawn>(OtherActor);

        if (Ship)
        {
            Ship->TakeDamage(Damage, OtherComp);
        }
    }

    Destroy();
}

void AProjectileBase::SetDamage(float NewDamage)
{
    Damage = NewDamage;
}

void AProjectileBase::SetSpeed(float NewSpeed)
{
    Speed = NewSpeed;
}