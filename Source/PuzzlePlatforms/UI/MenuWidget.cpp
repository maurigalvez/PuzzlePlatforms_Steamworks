// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

bool UMenuWidget::Initialize()
{	
	return Super::Initialize();
}

void UMenuWidget::Setup()
{
	this->AddToViewport();
	// get world
	UWorld* World = this->GetWorld();
	if (World == nullptr) return;

	// get hold of player controller
	APlayerController* controller = World->GetFirstPlayerController();
	if (controller == nullptr) return;

	FInputModeUIOnly inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputMode.SetWidgetToFocus(this->TakeWidget());
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;
}

void UMenuWidget::Remove()
{
	// remove from viewport
	this->RemoveFromViewport();
	// get world
	UWorld* World = this->GetWorld();
	if (World == nullptr) return;

	APlayerController* controller = World->GetFirstPlayerController();
	if (controller == nullptr) return;

	FInputModeGameOnly inputMode;
	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = false;
}

void UMenuWidget::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	this->MenuInterface = NewMenuInterface;
}
