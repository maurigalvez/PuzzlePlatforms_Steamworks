// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Add trigger volume box component and make it a root
	this->TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	if (this->TriggerVolume == nullptr)
	{
		return;
	}
	this->RootComponent = this->TriggerVolume;
	// add a mesh component
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetupAttachment(this->RootComponent);
	
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	// overlap begin hooks
	this->TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);	
	this->TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AMovingPlatform* platform : this->PlatformsToTrigger)
	{
		platform->AddActorTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (AMovingPlatform* platform : this->PlatformsToTrigger)
	{
		platform->RemoveActorTrigger();
	}
}

