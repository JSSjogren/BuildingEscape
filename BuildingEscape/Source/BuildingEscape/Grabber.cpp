// Copyright Jarod Sjogren 2018.
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector outLocation;
    FRotator outRotation;
	// Get player viewpoint during this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT outLocation, OUT outRotation);
    
    // UE_LOG(LogTemp, Warning, TEXT("Location: %s and Rotation: %s"), *outLocation.ToString(), *outRotation.ToString());
    
    //Drawing debug line
    FVector LineTraceEnd = outLocation + outRotation.Vector() * Reach;
    DrawDebugLine(GetWorld(), outLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);
    
    // Ray-cast to reach distance
    
    // See what we 'hit'
}

