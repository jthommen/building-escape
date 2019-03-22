// Building Escape copyright by Aetherwings, all rights reserved.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts (like constructor)
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	OwnerRotation = Owner->GetActorRotation();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	LogRotation();
}

void UOpenDoor::LogRotation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s rotation: %s"), *Owner->GetName(), *OwnerRotation.ToString());
}

void UOpenDoor::OpenDoor()
{
	// set door rotation
	if (isOpen == false)
	{
		isOpen = true;
		OwnerRotation.Yaw += OpenAngle;
		Owner->SetActorRotation(OwnerRotation);
		LogRotation();
	}
}

void UOpenDoor::CloseDoor()
{
	// set door rotation
	if (isOpen == true)
	{
		isOpen = false;
		OwnerRotation.Yaw += OpenAngle * (-1);
		Owner->SetActorRotation(OwnerRotation);
		LogRotation();
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume every frame
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		// If ActorThatOpens is in the volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it's time to close the door
	if (isOpen && GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
	
}

