// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/GameOver/HD_UI_GameOver.h"
#include "Logic/HD_GM.h"

#include "Components/Button.h"

void UHD_UI_GameOver::UIGameOverPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	_return_to_home->OnClicked.AddDynamic(this, &UHD_UI_GameOver::ClickedReturnToHome);
}
void UHD_UI_GameOver::ClickedReturnToHome()
{
	_gm->WorldReturnToHome();
}