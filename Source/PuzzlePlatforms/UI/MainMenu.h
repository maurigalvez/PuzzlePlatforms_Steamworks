// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void Host();

	UFUNCTION()
	void GoToJoinMenu();

	UFUNCTION()
	void GoToMainMenu();

	UFUNCTION()
	void Join();

	UFUNCTION()
	void ExitGame();

// ----------
// PROPERTIES
// ----------
private:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu = nullptr;
    // ---------
	// MAIN MENU
	// --------
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton = nullptr;

	// ---------
	// JOIN MENU
	// --------
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackToMenuButton = nullptr;	

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressTextBox = nullptr;
};
