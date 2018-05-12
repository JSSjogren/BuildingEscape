// Copyright Jarod Sjogren 2018.

#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}


void UOpenDoor::OpenDoor() {
    //Check if Owner is nullptr
    if (!Owner) { return; }
    
    // Set the Owner's Rotator to NewRotator
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() {
    //Check if Owner is nullptr
    if (!Owner) { return; }
    
    // Set the Owner's Rotator to NewRotator
    Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    
    Owner = GetOwner();
    
    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("PressurePlate was nullptr"));
    }
    
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("Owner was nullptr"));
    }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (GetTotalMassOnPlate() > 30.0f)
    {
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay)
    {
        CloseDoor();
    }
}

float UOpenDoor::GetTotalMassOnPlate()
{
    float TotalMass = 0.0f;
    TArray<AActor *> OverlappingActors;
    
    if (!PressurePlate) { return TotalMass; }
    
    ///Getting overlapping actors
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    for (const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *Actor->GetName());
    }
    
    return TotalMass;
}

