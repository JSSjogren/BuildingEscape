// Copyright Jarod Sjogren 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    //How far we can reach
    float Reach = 100.0f;
    
    UPhysicsHandleComponent * PhysicsHandle = nullptr;
    
    UInputComponent * InputComponent = nullptr;
	
    //Raycast and grab what's in reach
    void Grab();
    
    //Raycast and release what's in reach
    void Release();
    
    //Find attached physics handle
    void FindPhysicsHandleComponent();
    
    //Sets up (Assumed) attached input component
    void SetupInputComponent();
    
    //Return hit for first physics body in reach
    FHitResult GetFirstPhysicsBodyInReach() const;
    
    //Return the end point of the line-trace
    FVector CalculateLineTraceEnd() const;
    
    //Return the start point of the line-trace
    FVector CalculateLineTraceStart() const;
};
