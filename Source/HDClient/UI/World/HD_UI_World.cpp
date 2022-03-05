// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HD_UI_World.h"
#include "UI/HD_UI_Main.h"
#include "Information/HD_UI_Info.h"
#include "GameOver/HD_UI_GameOver.h"
#include "WorldClear/HD_UI_WorldClear.h"
#include "Logic/HD_GM.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UHD_UI_World::NativeConstruct()
{
	Super::NativeConstruct();

	//_wave_next->OnClicked.AddDynamic(this, &UHD_UI_World::ClickedWaveNext);
}
void UHD_UI_World::WorldPostInit(UHD_UI_Main* ui_main)
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_ui_info->UIInfoPostInit(ui_main);
	_ui_game_over->UIGameOverPostInit();
	_ui_world_clear->UIWorldClearPostInit();

	_wave_next->SetVisibility(ESlateVisibility::Hidden);
	_wave_start->SetVisibility(ESlateVisibility::Visible);

	_wave_next->OnClicked.AddDynamic(this, &UHD_UI_World::ClickedWaveNext);
}
void UHD_UI_World::WorldInit()
{
	_wave_next->SetVisibility(ESlateVisibility::Hidden);
	_wave_start->SetVisibility(ESlateVisibility::Visible);
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
	_wave_next->SetVisibility(ESlateVisibility::Hidden);
}
void UHD_UI_World::UIWorldClearToHome()
{
	_switcher->SetActiveWidgetIndex(0);
}

void UHD_UI_World::UIWorldWaveStart()
{
	_wave_start->SetVisibility(ESlateVisibility::Hidden);
	_wave_next->SetVisibility(ESlateVisibility::Hidden);
}
void UHD_UI_World::UIWorldWaveEnd()
{
	_wave_next->SetVisibility(ESlateVisibility::Visible);
}
void UHD_UI_World::UIWorldWaveNext()
{
	_wave_next->SetVisibility(ESlateVisibility::Hidden);
	_wave_start->SetVisibility(ESlateVisibility::Visible);
}

void UHD_UI_World::ClickedWaveNext()
{
	_gm->WaveNext();
}