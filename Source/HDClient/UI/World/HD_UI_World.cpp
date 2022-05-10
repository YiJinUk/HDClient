// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HD_UI_World.h"
#include "UI/HD_UI_Main.h"
#include "Information/HD_UI_Info.h"
#include "GameOver/HD_UI_GameOver.h"
#include "WorldClear/HD_UI_WorldClear.h"
#include "WaveClear/HD_UI_WaveClear.h"
#include "Logic/HD_GM.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UHD_UI_World::WorldPostInit(UHD_UI_Main* ui_main)
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_ui_info->UIInfoPostInit(ui_main);
	_ui_game_over->UIGameOverPostInit();
	_ui_world_clear->UIWorldClearPostInit();
	_ui_wave_clear->UIWaveClearPostInit(ui_main);

}
void UHD_UI_World::WorldInit()
{
}

void UHD_UI_World::UIWorldGameOver()
{
	_switcher->SetActiveWidgetIndex(1);
}
void UHD_UI_World::UIWorldReturnToHome()
{
	_switcher->SetActiveWidgetIndex(0);
}
void UHD_UI_World::UIWorldWorldClear()
{
	_switcher->SetActiveWidgetIndex(2);
}
void UHD_UI_World::UIWorldClearToHome()
{
	_switcher->SetActiveWidgetIndex(0);
}

void UHD_UI_World::UIWorldWaveStart()
{
}
void UHD_UI_World::UIWorldWaveClear()
{
	//_ui_wave_clear->UIWaveClearInit();
}
void UHD_UI_World::UIWorldWaveNext()
{
}