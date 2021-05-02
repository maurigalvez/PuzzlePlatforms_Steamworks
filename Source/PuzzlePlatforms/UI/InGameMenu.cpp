// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// initialize buttons
	if (this->ResumeGameButton == nullptr) return false;
	this->ResumeGameButton->OnClicked.AddDynamic(this, &UInGameMenu::ResumeGame);

	if (this->ExitGameButton == nullptr) return false;
	this->ExitGameButton->OnClicked.AddDynamic(this, &UInGameMenu::GoToMainMenu);
		
	return true;
}

void UInGameMenu::ResumeGame()
{
	this->Remove();
}

void UInGameMenu::GoToMainMenu()
{
	// get game instance
	if (this->MenuInterface != nullptr)
	{
		this->Remove();
		this->MenuInterface->LoadMainMenu();
	}
}