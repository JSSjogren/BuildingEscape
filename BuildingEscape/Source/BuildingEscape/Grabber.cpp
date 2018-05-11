// Copyright Jarod Sjogren 2018.
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
}

///Look for attached input component (appears at run-time)
void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        ///Found InputComponent
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this,
                                   &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Input Component was nullptr for actor %s"), *GetOwner()->GetName());
    }
}

///Looks for Physics Handle component
void UGrabber::FindPhysicsHandleComponent()
{
    ///Look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        ///Found PhysicsHandle
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Physics Handle was nullptr for actor %s"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
    
    /// LINE TRACE and see if we reach any actors with physics body collision channel set
    
    ///If we hit something then try and attach a physics handle
    //TODO Attach Physics handle
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Released!"));
    
    //TODO Release physics handle
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    GetFirstPhysicsBodyInReach();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    FVector OutLocation;
    FRotator OutRotation;
    /// Get player viewpoint during this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT OutLocation, OUT OutRotation);
    
    /// UE_LOG(LogTemp, Warning, TEXT("Location: %s and Rotation: %s"), *outLocation.ToString(), *outRotation.ToString());
    
    /// Calculating end of line trace
    FVector LineTraceEnd = OutLocation + OutRotation.Vector() * Reach;
    
    /// Creating FCollisionQueryParams
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// Ray-cast to reach distance
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
                                            HitResult,
                                            OutLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECC_PhysicsBody),
                                            TraceParameters
                                            );
    
    /// See what we 'hit'
    AActor * ActorHit = HitResult.GetActor();
    if (ActorHit)
    {
        FString ActorName = HitResult.GetActor()->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *ActorName);
    }
}

