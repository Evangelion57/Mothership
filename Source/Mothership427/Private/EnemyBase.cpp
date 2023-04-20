#pragma once
#include "EnemyBase.h"
#include "ShipPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    RootComponent = EnemyMesh;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(EnemyMesh);
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlap);

    Health = 100;
    MovementSpeed = 100.0f;
    Price = 10.0f;
    Exp = 5.0f;
    DamageOverlap = 10.0f;
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();


    DamageOverlap = 10.0f;

}

void AEnemyBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Player)
    {
        Player = Cast<AShipPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        if (Player)
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy - Player detected: %s"), *Player->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemy - Player not detected"));
        }
    }

    if (Player)
    {
        MoveTowardsPlayer(DeltaTime);
    }

}

void AEnemyBase::MoveTowardsPlayer(float DeltaTime)
{
    FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}

void AEnemyBase::TakeDamage(float DamageAmount, UPrimitiveComponent* HitComponent)
{
    Health -= DamageAmount;

    if (Health <= 0)
    {
        Die();
    }
}

void AEnemyBase::Die()
{  
    Destroy();
    // exp to player
}

float AEnemyBase::GetPrice() const
{
	return Price;
}

void AEnemyBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapped actor is the player's pawn
    AShipPawn* PlayerPawn = Cast<AShipPawn>(OtherActor);
    if (PlayerPawn)
    {
        // Deal damage to the player
        PlayerPawn->TakeDamage(DamageOverlap, OverlappedComponent);

        // Destroy the enemy
        Die();
    }
}