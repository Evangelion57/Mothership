#pragma once
#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ProjectileBase.h"
#include "EngineUtils.h"
#include "EnemyBase.h"

AWeaponBase::AWeaponBase()
{
    
    PrimaryActorTick.bCanEverTick = true;
    /*
    //static ConstructorHelpers::FClassFinder<AProjectileBase> ProjectileBPClass(TEXT("/Game/Blueprints/ProjectileBase_BP"));

    if (ProjectileBPClass.Class)
    {
        ProjectileClass = ProjectileBPClass.Class;
    }
    */

    MaxDistance = 1000.0f;
    Angle = 40.0f;
    FireRate = 1.0f;
    EnergyCost = 10.0f;
    Spread = 4.0f;

    LastFireTime = 0.0f;
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();
    OwnerPawn = Cast<AShipPawn>(GetOwner());

    if (OwnerPawn)
    {
		UE_LOG(LogTemp, Warning, TEXT("Owner detected: %s"), *OwnerPawn->GetName());
	}
    else
    {
		UE_LOG(LogTemp, Warning, TEXT("Owner not detected"));
	}

    OwnerPawn = Cast<AShipPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (OwnerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player detected: %s"), *OwnerPawn->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player not detected"));
    }

}

AActor* AWeaponBase::FindClosestEnemyInAngle()
{
    AActor* ClosestEnemy = nullptr;
    float ClosestDistance = MaxDistance;

    for (TActorIterator<AEnemyBase> It(GetWorld()); It; ++It)
    {
        AEnemyBase* Enemy = *It;

        FVector DirectionToEnemy = Enemy->GetActorLocation() - GetActorLocation();
        float DistanceToEnemy = DirectionToEnemy.Size();

        if (DistanceToEnemy <= MaxDistance)
        {
            FVector WeaponForward = GetActorForwardVector();
            DirectionToEnemy.Normalize();

            float AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WeaponForward, DirectionToEnemy)));

            if (AngleBetween <= Angle)
            {
                if (DistanceToEnemy < ClosestDistance)
                {
                    ClosestDistance = DistanceToEnemy;
                    ClosestEnemy = Enemy;
                }
            }
        }
    }

    return ClosestEnemy;
}

void AWeaponBase::Fire()
{
    if (!ProjectileClass) return;

    if (GetWorld()->GetTimeSeconds() - LastFireTime < 1.0f / FireRate)
    {
        return;
    }

    AActor* Target = FindClosestEnemyInAngle();

    if (Target)
    {
        if (OwnerPawn && OwnerPawn->GetWeaponEnergy() >= EnergyCost)
        {
            OwnerPawn->SetWeaponEnergy(OwnerPawn->GetWeaponEnergy() - EnergyCost);

            LastFireTime = GetWorld()->GetTimeSeconds();

            FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * SpawnOffset;
            FRotator SpawnRotation = (Target->GetActorLocation() - SpawnLocation).Rotation();
            //Spread shooting
            float RandomZSpread = FMath::RandRange(-Spread, Spread);
            SpawnRotation.Add(0, 0, RandomZSpread);

            AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);

            if (Projectile)
            {
                Projectile->SetDamage(ProjectileDamage);
                Projectile->SetSpeed(ProjectileSpeed);
            }


        }
    }
}

void AWeaponBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Fire();
}