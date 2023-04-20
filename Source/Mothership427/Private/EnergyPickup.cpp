#include "EnergyPickup.h"
#include "ShipPawn.h"

AEnergyPickup::AEnergyPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    RootComponent = PickupMesh;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAll"));
    CollisionBox->SetGenerateOverlapEvents(true);
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickup::OnOverlapBegin);

    EnergyAmount = 50.0f;

    ShieldWeight = 1.0f;
    ThrustWeight = 1.0f;
    WeaponWeight = 2.0f;

    LifeSpan     = 10.0f;


    // Select type with weights
    float TotalWeight = ShieldWeight + ThrustWeight + WeaponWeight;
    float RandomValue = FMath::RandRange(0.0f, TotalWeight);

    if (RandomValue < ShieldWeight)
    {
        EnergyType = EEnergyType::Shield;
    }
    else if (RandomValue < ShieldWeight + ThrustWeight)
    {
        EnergyType = EEnergyType::Thrust;
    }
    else
    {
        EnergyType = EEnergyType::Weapon;
    }

    // Set the color of the pickup based on the energy type
    switch (EnergyType)
    {
    case EEnergyType::Shield:
        PickupColor = FLinearColor::Blue;
        break;
    case EEnergyType::Thrust:
        PickupColor = FLinearColor::Yellow;
        break;
    case EEnergyType::Weapon:
        PickupColor = FLinearColor::Red;
        break;
    }


}

void AEnergyPickup::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(LifeSpan);

    
    
    // Apply the color to the pickup mesh
    UMaterialInstanceDynamic* DynamicMaterial = PickupMesh->CreateDynamicMaterialInstance(0);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(FName("Color"), PickupColor);
    }

    // Set a timer to destroy the pickup after 15 seconds
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnergyPickup::DestroyPickup, 15.0f, false);
}

void AEnergyPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if OtherActor is the player
    AShipPawn* PlayerPawn = Cast<AShipPawn>(OtherActor);
    if (PlayerPawn)
    {
        // Transfer energy to the player
        TransferEnergyToPlayer(PlayerPawn);

        // Destroy the pickup
        Destroy();
    }
}

void AEnergyPickup::TransferEnergyToPlayer(AShipPawn* PlayerPawn)
{
    if (!PlayerPawn) return;

    UE_LOG  (LogTemp, Warning, TEXT("Energy Pickup: Transfering energy to player"));
        
    PlayerPawn->ReceiveEnergy(EnergyType, EnergyAmount);
}

void AEnergyPickup::DestroyPickup()
{
    Destroy();
}

/*
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
*/