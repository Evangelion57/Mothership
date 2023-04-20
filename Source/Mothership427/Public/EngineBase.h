#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineBase.generated.h"

// Forward declaration
class AShipPawn;

UCLASS()
class MOTHERSHIP427_API AEngineBase : public AActor
{
    GENERATED_BODY()

public:
    AEngineBase();

    UFUNCTION(BlueprintCallable, Category = "Engine")
        FVector GetEngineForce() const;

    UFUNCTION()
        void SetTargetDirection(const FVector& TargetDirection);
        
        const FVector& GetTargetDirection() const;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "Engine Properties")
        float MaxSpeed;

    UPROPERTY(EditAnywhere, Category = "Engine Properties")
        float AccelerationTime;

    UPROPERTY(EditAnywhere, Category = "Engine Properties")
        float DecelerationTime;

    UPROPERTY(EditAnywhere, Category = "Engine Properties")
        float EnergyConsumptionPerSecond;

    FVector TargetDirection;

    float CurrentSpeed;

    AShipPawn* OwningShipPawn;
};
