// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menu Interfaces/MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class WEEK59_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize();

	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinSwitch;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void QuitGame();
};
