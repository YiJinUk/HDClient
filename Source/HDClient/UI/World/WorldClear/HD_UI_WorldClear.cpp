// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/WorldClear/HD_UI_WorldClear.h"
#include "Logic/HD_GM.h"

#include "Components/Button.h"

void UHD_UI_WorldClear::UIWorldClearPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_clear_to_home->OnClicked.AddDynamic(this, &UHD_UI_WorldClear::ClickedClearToHome);
}
void UHD_UI_WorldClear::ClickedClearToHome()
{
	_gm->WorldClearToHome();
}