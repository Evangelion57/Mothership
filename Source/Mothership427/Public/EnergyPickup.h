#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/Pawn.h"
#include "EnergyPickup.generated.h"


class AShipPawn;

UENUM(BlueprintType)
enum class EEnergyType : uint8
{
    Shield,
    Thrust,
    Weapon
};

UCLASS()
class MOTHERSHIP427_API AEnergyPickup : public AActor
{
    GENERATED_BODY()

public:
    AEnergyPickup();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* PickupMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        float EnergyAmount;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        EEnergyType EnergyType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        FLinearColor PickupColor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        float ShieldWeight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        float ThrustWeight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
        float WeaponWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy", meta = (AllowPrivateAccess = "true"))
        float LifeSpan;

    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void TransferEnergyToPlayer(AShipPawn* PlayerPawn);
    void DestroyPickup();

private:
    FTimerHandle TimerHandle;
};
