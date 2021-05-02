// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

	void AddActorTrigger();
	void RemoveActorTrigger();

// -------------
// PROPERTIES
// -------------
private:
	UPROPERTY(EditAnywhere, Category = "Move Settings")
	float MoveSpeed = 5.f;

	// Target location relative to the moving platform. FVector::Zero is pivot of actor
	UPROPERTY(EditAnywhere, Category = "Move Settings", Meta =(MakeEditWidget = true))
	FVector TargetLocation = FVector::ZeroVector;

// -------------
// VARIABLES
// -------------
private:
	FVector GlobalTargetLocation = FVector::ZeroVector;
	FVector GlobalStartLocation = FVector::ZeroVector;
	float DistanceToTargetLocation = 0;	
	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
};
