#pragma once
#include "CoreMinimal.h"
#include "EnergyPickupColor.generated.h"

USTRUCT(BlueprintType)
struct FEnergyPickupColor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Energy Pickup Color")
        FLinearColor ShieldColor = FLinearColor::Blue;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Energy Pickup Color")
        FLinearColor ThrustColor = FLinearColor::Yellow;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Energy Pickup Color")
        FLinearColor WeaponColor = FLinearColor::Red;
};
