#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

UCLASS()
class MOTHERSHIP427_API AShipPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AShipPlayerController();

    virtual void Tick(float DeltaTime) override;

    void HandleGamepadX(float Value);
    void HandleGamepadY(float Value);

    void RightGamepadX(float Value);
    void RightGamepadY(float Value);

    void OnLeftMouseClick();
    void OnRightMouseClick();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    FVector2D MousePosition;
    FVector2D MouseShieldPosition;
    float AxisValueX;
    float AxisValueY;
    float RightValueX;
    float RightValueY;
};
