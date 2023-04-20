#include "EngineBase.h"
#include "ShipPawn.h"



AEngineBase::AEngineBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MaxSpeed = 1000.0f;
    AccelerationTime = 2.0f;
    DecelerationTime = 3.0f;
    EnergyConsumptionPerSecond = 1.0f;
    CurrentSpeed = 0.0f;
}

void AEngineBase::SetTargetDirection(const FVector& InTargetDirection)
{
    TargetDirection = InTargetDirection;
}

void AEngineBase::BeginPlay()
{
    Super::BeginPlay();

    OwningShipPawn = Cast<AShipPawn>(GetAttachParentActor());

    if (OwningShipPawn)
    {
        OwningShipPawn->AddEngine(this);
    }

}


void AEngineBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (OwningShipPawn)
    {
        OwningShipPawn->RemoveEngine(this);
    }

    Super::EndPlay(EndPlayReason);
}


void AEngineBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector ForwardDirection = GetActorForwardVector();
    float CosAngle = FVector::DotProduct(ForwardDirection, TargetDirection);

    // Проверяем, находится ли двигатель в радиусе +-46 градусов от направления курсора
    if (CosAngle >= FMath::Cos(FMath::DegreesToRadians(46.0f)))
    {
        // Увеличиваем скорость двигателя
        CurrentSpeed = FMath::Min(CurrentSpeed + MaxSpeed * DeltaTime / AccelerationTime, MaxSpeed);
    }
    else
    {
        // Уменьшаем скорость двигателя
        CurrentSpeed = FMath::Max(CurrentSpeed - MaxSpeed * DeltaTime / DecelerationTime, 0.0f);
    }
}

FVector AEngineBase::GetEngineForce() const
{
    return GetActorForwardVector() * CurrentSpeed;
}

const FVector& AEngineBase::GetTargetDirection() const
{
    return TargetDirection;
}