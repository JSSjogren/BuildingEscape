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
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Physics Handle was nullptr for actor %s"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab()
{
    /// LINE TRACE and see if we reach any actors with physics body collision channel set
    /// If we hit something then try and attach a physics handle
    
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    /// Attach Physics handle
    if (ActorHit)
    {
        ///Check for nullptr physicshandle
        if (!PhysicsHandle) { return; }
        
        PhysicsHandle->GrabComponentAtLocationWithRotation(
                                                           ComponentToGrab,
                                                           NAME_None,
                                                           ComponentToGrab->GetOwner()->GetActorLocation(),
                                                           ComponentToGrab->GetOwner()->GetActorRotation());
    }
}

void UGrabber::Release()
{
    ///Check for nullptr physicshandle
    if (!PhysicsHandle) { return; }
    
    ///Release physics handle
    PhysicsHandle->ReleaseComponent();
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    ///Check for nullptr physicshandle
    if (!PhysicsHandle) { return; }
    
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(CalculateLineTraceEnd());
    }
}

FVector UGrabber::CalculateLineTraceEnd() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    /// Get player viewpoint during this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    /// Calculating end of line trace
    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::CalculateLineTraceStart() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    /// Get player viewpoint during this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    /// Returning OutLocation;
    return PlayerViewPointLocation;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    /// Ray-cast to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    GetWorld()->LineTraceSingleByObjectType(
                                            HitResult,
                                            CalculateLineTraceStart(),
                                            CalculateLineTraceEnd(),
                                            FCollisionObjectQueryParams(ECC_PhysicsBody),
                                            TraceParameters
                                            );
    return HitResult;
}

