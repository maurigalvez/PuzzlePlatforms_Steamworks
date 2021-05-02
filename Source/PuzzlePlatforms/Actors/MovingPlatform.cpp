// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	// make sure this platform is movable
	this->SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	// make sure this only happens in server
	if (this->HasAuthority())
	{
		// set property to be reflected on clients
		this->SetReplicates(true);
		this->SetReplicateMovement(true);
	}
	this->GlobalStartLocation = this->GetActorLocation();
	this->GlobalTargetLocation = this->GetTransform().TransformPosition(this->TargetLocation);
	this->DistanceToTargetLocation = (this->GlobalTargetLocation - this->GlobalStartLocation).Size(); //length of vector
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// make sure platform doesn't move if <= 0 
	if (this->ActiveTriggers <= 0)
		return;

	// check if this doesnt' have authority (client)
	if (!this->HasAuthority())
		return;

	// get how far we have traveled
	float DistanceTraveled = (this->GetActorLocation() - this->GlobalStartLocation).Size();

	if (DistanceTraveled >= this->DistanceToTargetLocation)
	{
		// swap
		FVector previousTarget = this->GlobalTargetLocation;
		this->GlobalTargetLocation = this->GlobalStartLocation;
		this->GlobalStartLocation = previousTarget;
	}

	FVector MoveDirection = (this->GlobalTargetLocation - this->GlobalStartLocation).GetSafeNormal();	
	// move platform in move direction
	FVector currentLocation = this->GetActorLocation() + (MoveDirection * this->MoveSpeed * DeltaTime);
	// update location
	this->SetActorLocation(currentLocation);
}

void AMovingPlatform::AddActorTrigger()
{
	this->ActiveTriggers++;
}

void AMovingPlatform::RemoveActorTrigger()
{
	if (this->ActiveTriggers > 0)
	{
		this->ActiveTriggers--;
	}
}
