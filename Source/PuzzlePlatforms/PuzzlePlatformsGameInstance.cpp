// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UI/MenuWidget.h"
#include "UI/InGameMenu.h"
#include "UI/MainMenu.h"
// -------
// Gets called even in editor
// -------
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// create menu instance
	ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetBPClass(TEXT("/Game/Blueprints/Menu/WBP_MainMenu"));
	if (MenuWidgetBPClass.Class == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Class not found"));
		return;
	}
	// save menu class
	this->MenuClass = MenuWidgetBPClass.Class;

	// in game menu
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Class not found"));
		return;
	}
	this->InGameMenuClass = InGameMenuBPClass.Class;
}

// -----------
// Init only gets called when we play the game
// ---------
void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{	
	if (this->MenuClass != NULL)
	{
		// display menu
		this->MainMenu = CreateWidget<UMainMenu>(this, this->MenuClass);
		if (this->MainMenu != nullptr)
		{
			this->MainMenu->Setup();
			// set interface
			this->MainMenu->SetMenuInterface(this);
		}		
	}
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (this->InGameMenuClass != NULL)
	{
		UInGameMenu* InGameMenu = CreateWidget<UInGameMenu>(this, this->InGameMenuClass);
		if (InGameMenu != nullptr)
		{
			InGameMenu->Setup();
			InGameMenu->SetMenuInterface(this);
		}
	}
}

void UPuzzlePlatformsGameInstance::Host()
{
	// remove menu 
	if (this->MainMenu != nullptr)
	{
		this->MainMenu->Remove();
	}
	UE_LOG(LogTemp, Warning, TEXT("HOSTING"));
	
	UEngine* engine = this->GetEngine();
	if (engine == nullptr)
	{
		return;
	}
	engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HOSTING"));
	// server travel through world
	UWorld* world = this->GetWorld();
	if (world == nullptr)
	{
		return;
	}
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	// remove menu 
	if (this->MainMenu != nullptr)
	{
		this->MainMenu->Remove();
	}
	UEngine* engine = this->GetEngine();
	if (engine == nullptr)
	{
		return;
	}
	engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("JOINING %s"), *Address));
	// client travel through server controller
	APlayerController* controller = this->GetFirstLocalPlayerController();
	if (controller == nullptr)
	{
		return;
	}	
	controller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	// client travel through server controller
	APlayerController* controller = this->GetFirstLocalPlayerController();
	if (controller == nullptr)
	{
		return;
	}
	controller->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}