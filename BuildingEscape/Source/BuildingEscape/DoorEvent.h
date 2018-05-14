// Copyright Jarod Sjogren 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorEvent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere)
        float TriggerMass = 30.0f;
	
    UPROPERTY(EditAnywhere)
        ATriggerVolume * PressurePlate = nullptr;
    
    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnClose;

    float GetTotalMassOnPlate();
};
