// Copyright Jarod Sjogren 2018.

#include "DoorEvent.h"
#define OUT

// Sets default values for this component's properties
UDoorEvent::UDoorEvent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}

// Called when the game starts
void UDoorEvent::BeginPlay()
{
    Super::BeginPlay();
    
    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("PressurePlate was nullptr"));
    }
}


// Called every frame
void UDoorEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (GetTotalMassOnPlate() > TriggerMass)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
}

float UDoorEvent::GetTotalMassOnPlate()
{
    float TotalMass = 0.0f;
    TArray<AActor *> OverlappingActors;
    
    if (!PressurePlate) { return TotalMass; }
    
    ///Getting overlapping actors
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    for (const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    
    return TotalMass;
}

