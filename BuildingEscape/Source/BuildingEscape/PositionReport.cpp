// Copyright Jarod Sjogren 2018.

#include "PositionReport.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include <string>

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    
//    FVector ObjectPosVector =
    FString ObjectName = GetOwner() -> GetName();
    FString ObjectPos = GetOwner() -> GetTransform().GetLocation().ToString();
	// ...
    UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

