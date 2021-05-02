// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatforms/UI/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& address) override;

	void LoadMainMenu() override;

protected:
	virtual void Init() override;

	TSubclassOf<class UUserWidget> MenuClass = nullptr;

	TSubclassOf<class UUserWidget> InGameMenuClass = nullptr;

private:
	class UMainMenu* MainMenu = nullptr;	
};
