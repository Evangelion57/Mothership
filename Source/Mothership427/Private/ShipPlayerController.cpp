#include "ShipPlayerController.h"
#include "ShipPawn.h"

AShipPlayerController::AShipPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;

    bShowMouseCursor = true;
    bEnableClickEvents = true;
}

void AShipPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AShipPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AShipPawn* ControlledPawn = Cast<AShipPawn>(GetPawn());
    if (ControlledPawn)
    {
        FVector2D InputDirection = FVector2D::ZeroVector;
        FVector2D ShieldDirection = FVector2D::ZeroVector;

        if (!MousePosition.IsNearlyZero())
        {
            AxisValueX = MousePosition.X;
            AxisValueY = MousePosition.Y;
            InputDirection = FVector2D(AxisValueX, AxisValueY);
        }
        else
        {
            InputDirection = FVector2D(AxisValueX, AxisValueY);
        }

        ControlledPawn->SetTargetDirection(InputDirection);

        if (!MouseShieldPosition.IsNearlyZero())
        {
            RightValueX = -MousePosition.X;
            RightValueY = MousePosition.Y;
            ShieldDirection = FVector2D(RightValueX, RightValueY);
        }
        else
        {
            ShieldDirection = FVector2D(RightValueX, RightValueY);
        }

        ControlledPawn->SetShieldDirection(ShieldDirection);
    }
}

void AShipPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Gamepad bindings
    InputComponent->BindAxis("MoveX", this, &AShipPlayerController::HandleGamepadX);
    InputComponent->BindAxis("MoveY", this, &AShipPlayerController::HandleGamepadY);

    InputComponent->BindAxis("ShieldX", this, &AShipPlayerController::RightGamepadX);
    InputComponent->BindAxis("ShieldY", this, &AShipPlayerController::RightGamepadY);


    // Mouse bindings
    InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AShipPlayerController::OnLeftMouseClick);
}

void AShipPlayerController::HandleGamepadX(float Value)
{
    AxisValueX = Value;
}

void AShipPlayerController::HandleGamepadY(float Value)
{
    AxisValueY = Value;
}

void AShipPlayerController::RightGamepadX(float Value)
{
    RightValueX = Value;
}

void AShipPlayerController::RightGamepadY(float Value)
{
    RightValueY = Value;
}

void AShipPlayerController::OnLeftMouseClick()
{
    float MouseX, MouseY;
    if (GetMousePosition(MouseX, MouseY))
    {
        FVector WorldLocation, WorldDirection;
        DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

        FVector2D WorldDirection2D = FVector2D(WorldDirection.X, WorldDirection.Y);
        MousePosition = WorldDirection2D.GetSafeNormal();
    }
}

void AShipPlayerController::OnRightMouseClick()
{
    float MouseX, MouseY;
    if (GetMousePosition(MouseX, MouseY))
    {
        FVector WorldLocation, WorldDirection;
        DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

        FVector2D WorldDirection2D = FVector2D(WorldDirection.X, WorldDirection.Y);
        MouseShieldPosition = WorldDirection2D.GetSafeNormal();
    }
}