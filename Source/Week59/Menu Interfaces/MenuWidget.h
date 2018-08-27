// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEEK59_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMenuInterface(IMenuInterface * InMenuInterface) { MenuInterface = InMenuInterface; }

	void Setup();

	void TearDown();

	void CloseGame();
	

protected:

	IMenuInterface * MenuInterface;
	
};
