#include "ShipPawn.h"
#include "EngineBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AShipPawn::AShipPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create components
    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    RootComponent = Body;

    Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
    Shield->SetupAttachment(Body);

    // Set default values
    Health = 100.0f;
    ShieldEnergy = 100.0f;
    ThrustEnergy = 100.0f;
    WeaponEnergy = 100.0f;

    HealthRegen = 1.0f;
    ShieldEnergyRegen = 1.0f;
    ThrustEnergyRegen = 1.0f;
    WeaponEnergyRegen = 1.0f;
}

void AShipPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AShipPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Calculate Engines vector
    FVector TotalForce = FVector::ZeroVector;
    for (AEngineBase* Engine : Engines)
    {
        TotalForce += Engine->GetEngineForce();
    }

    // Perform movement
    FVector NewLocation = GetActorLocation() + TotalForce * DeltaTime;
    SetActorLocation(NewLocation, true);

    // Perform smooth rotation
    FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
    SetActorRotation(NewRotation);

    //Energy Regen Calculations
    Health = FMath::Min(Health + HealthRegen * DeltaTime, 100.0f);
    ShieldEnergy = FMath::Min(ShieldEnergy + ShieldEnergyRegen * DeltaTime, 100.0f);
    ThrustEnergy = FMath::Min(ThrustEnergy + ThrustEnergyRegen * DeltaTime, 100.0f);
    WeaponEnergy = FMath::Min(WeaponEnergy + WeaponEnergyRegen * DeltaTime, 100.0f);

    if (Health <= 0)
    {
        // UE_LOG
        UE_LOG(LogTemp, Warning, TEXT("Game Over"));

        // Print to screen
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Game Over"));
        }

        // Print to console
        if (GetWorld() && GetWorld()->GetFirstPlayerController())
        {
            GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Log LogTemp Warning 'Game Over'"));
        }

        // Disable ticking after the game is over
        SetActorTickEnabled(false);
    }
}

void AShipPawn::ReceiveEnergy(EEnergyType EnergyType, float Amount)
{
    switch (EnergyType)
    {
    case EEnergyType::Shield:
        ShieldEnergy = FMath::Min(ShieldEnergy + Amount, 100.0f);
        break;
    case EEnergyType::Thrust:
        ThrustEnergy = FMath::Min(ThrustEnergy + Amount, 100.0f);
        break;
    case EEnergyType::Weapon:
        WeaponEnergy = FMath::Min(WeaponEnergy + Amount, 100.0f);
        break;
    }
}

void AShipPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShipPawn::SetTargetDirection(const FVector2D& Target)
{
    FVector TargetDirection = FVector(Target.X, Target.Y, 0.0f);
    TargetRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, TargetDirection);

    // Target direction for all engines
    for (AEngineBase* Engine : Engines)
    {
        if (Engine)
        {
            Engine->SetTargetDirection(TargetDirection);
        }
    }

    // Get current pawn direction

    FVector PawnDirection = GetActorForwardVector();

    // Searching for engine with closest direction to target

    AEngineBase* ClosestEngine = nullptr;
    float ClosestDistance = FLT_MAX;

    for (AEngineBase* Engine : Engines)
    {
        FVector EngineDirection = Engine->GetTargetDirection();
        float Distance = FVector::DotProduct(TargetDirection, EngineDirection);
        if (Distance < ClosestDistance)
        {
            ClosestEngine = Engine;
            ClosestDistance = Distance;
        }
    }

    // If closest engine not found, return
    if (!ClosestEngine)
    {
        return;
    }


    // Find angle between pawn direction and closest engine direction
    /*

    FVector ClosestEngineDirection = ClosestEngine->GetTargetDirection();
    float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetDirection.GetSafeNormal(), ClosestEngineDirection.GetSafeNormal())));
    FRotator CurrentRotation = GetActorRotation();
    TargetRotation = CurrentRotation + FRotator(0.0f, Angle, 0.0f);
    */

    /*
    // Angle to pawn rotate
    FVector ClosestEngineDirection = ClosestEngine->GetTargetDirection();
    FQuat CurrentRotationQuat = GetActorRotation().Quaternion();
    FQuat TargetRotationQuat = FQuat::FindBetweenNormals(GetActorForwardVector(), ClosestEngineDirection);
    TargetRotation = (CurrentRotationQuat * TargetRotationQuat).Rotator();
    */

    /*
    // Находим угол, на который необходимо повернуть паун
    FVector ClosestEngineDirection = ClosestEngine->GetTargetDirection();
    TargetRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, ClosestEngineDirection * 100.0f);
    */
}

void AShipPawn::SetShieldDirection(const FVector2D& Target)
{
    FVector TargetDirection = FVector(Target.X, Target.Y, 0.0f);
    ShieldRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, TargetDirection);
}

void AShipPawn::AddEngine(AEngineBase* Engine)
{
    if (Engine)
    {
        Engines.AddUnique(Engine);
    }
}

void AShipPawn::RemoveEngine(AEngineBase* Engine)
{
    if (Engine)
    {
        Engines.Remove(Engine);
    }
}

float AShipPawn::GetHealth() const
{
    return Health;
}

void AShipPawn::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, -20.0f, 100.0f);
    CheckDeath();
}

void AShipPawn::TakeDamage(float DamageAmount, UPrimitiveComponent* HitComponent)
{
    if (HitComponent == Shield)
    {
        TakeShieldDamage(DamageAmount);
    }
    else
    {
        Health -= DamageAmount;
        CheckDeath();
    }
}


void AShipPawn::CheckDeath()
{
    if (Health <= 0)
    {
        Destroy();
        // OnShipDestroyed.Broadcast();
    }
}

//Shield

UStaticMeshComponent* AShipPawn::GetShieldMesh() const
{
    return Shield;
}

float AShipPawn::GetShieldEnergy() const
{
    return ShieldEnergy;
}

void AShipPawn::SetShieldEnergy(float NewShieldEnergy)
{
    ShieldEnergy = FMath::Clamp(NewShieldEnergy, 0.0f, 100.0f);
}

void AShipPawn::TakeShieldDamage(float Damage)
{
    float RemainingDamage = Damage - ShieldEnergy;

    if (RemainingDamage > 0.0f)
    {
        // Apply the remaining damage to health
        Health -= RemainingDamage;
        CheckDeath();

        // Set shield energy to 0
        ShieldEnergy = 0.0f;
    }
    else
    {
        // Absorb the damage with the shield energy
        ShieldEnergy -= Damage;
    }
}

//Thrust
float AShipPawn::GetThrustEnergy() const
{
    return ThrustEnergy;
}

void AShipPawn::SetThrustEnergy(float NewThrustEnergy)
{
    ThrustEnergy = FMath::Clamp(NewThrustEnergy, 0.0f, 100.0f);
}

float AShipPawn::GetWeaponEnergy() const
{
    return WeaponEnergy;
}

void AShipPawn::SetWeaponEnergy(float NewWeaponEnergy)
{
    WeaponEnergy = FMath::Clamp(NewWeaponEnergy, 0.0f, 100.0f);
}


