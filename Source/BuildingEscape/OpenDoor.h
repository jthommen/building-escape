// Building Escape copyright by Aetherwings, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime = 0.f;

	AActor* ActorThatOpens; // pawn inherits from actor
	AActor* Owner; // The owning door
	FRotator OwnerRotation; // Starting rotation of the door
	bool isOpen = false; // Door State

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	void OpenDoor();
	void CloseDoor();
	void LogRotation();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};
