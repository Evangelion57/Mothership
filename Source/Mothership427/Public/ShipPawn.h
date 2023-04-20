#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnergyPickup.h"
#include "EngineBase.h"
#include "Components/StaticMeshComponent.h"
#include "ShipPawn.generated.h"

// Forward declaration
class AEngineBase;

UCLASS()
class MOTHERSHIP427_API AShipPawn : public APawn
{
    GENERATED_BODY()

public:
    AShipPawn();

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        UStaticMeshComponent* Body;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
        UStaticMeshComponent* Shield;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float Health;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float ShieldEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float ThrustEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float WeaponEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float HealthRegen;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float ShieldEnergyRegen;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float ThrustEnergyRegen;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Parameters")
        float WeaponEnergyRegen;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Engines")
        TArray<AEngineBase*> Engines;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float RotationSpeed = 0.5f;

    UFUNCTION()
        void ReceiveEnergy(EEnergyType EnergyType, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Movement")
        void SetTargetDirection(const FVector2D& Target);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
        void SetShieldDirection(const FVector2D& Target);

    // Health
    UFUNCTION(BlueprintCallable, Category = "Ship")
        float GetHealth() const;
    UFUNCTION(BlueprintCallable, Category = "Ship")
        void SetHealth(float NewHealth);
    UFUNCTION(BlueprintCallable, Category = "Ship")
        void TakeDamage(float DamageAmount, UPrimitiveComponent* HitComponent);


    // ShieldEnergy
    UFUNCTION(BlueprintCallable, Category = "Ship")
        float GetShieldEnergy() const;
   
    UFUNCTION(BlueprintCallable, Category = "Ship")
        void SetShieldEnergy(float NewShieldEnergy);

    UFUNCTION(BlueprintCallable, Category = "Ship")
        void TakeShieldDamage(float Damage);

        // Get the shield mesh component
    UFUNCTION(BlueprintPure, Category = "Ship")
        UStaticMeshComponent* GetShieldMesh() const;


    // ThrustEnergy
    UFUNCTION(BlueprintCallable, Category = "Ship")
        float GetThrustEnergy() const;
    UFUNCTION(BlueprintCallable, Category = "Ship")
        void SetThrustEnergy(float NewThrustEnergy);

    // WeaponEnergy
    UFUNCTION(BlueprintCallable, Category = "Ship")
        float GetWeaponEnergy() const;
    UFUNCTION(BlueprintCallable, Category = "Ship")
        void SetWeaponEnergy(float NewWeaponEnergy);


    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AddEngine(AEngineBase* Engine);
    void RemoveEngine(AEngineBase* Engine);


private:
    FRotator TargetRotation;
    FRotator ShieldRotation;

    void CheckDeath();


protected:
    
};
