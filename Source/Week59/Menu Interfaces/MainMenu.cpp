// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (HostButton == nullptr || JoinSwitch == nullptr || ConfirmJoinGame == nullptr || CancelJoinMenu == nullptr || QuitButton == nullptr)
	{
		return false;
	}
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinSwitch->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	ConfirmJoinGame->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);
	CancelJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}





void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	FInputModeGameOnly InputModeData;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Error, TEXT("U Want Sum Host?"))
		if (MenuInterface != nullptr)
		{
			MenuInterface->Host();
		}
}

void UMainMenu::OpenMainMenu()
{
	if (MainMenu && JoinMenu)
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}


void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher && JoinMenu)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
	UE_LOG(LogTemp, Error, TEXT("U Tryin To Join?"))
}

void UMainMenu::JoinGame()
{
	if (MenuInterface && IPAddressField)
	{
		MenuInterface->Join(IPAddressField->GetText().ToString());
	}
}

void UMainMenu::QuitGame()
{	
	CloseGame();
}

