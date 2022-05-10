// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/WaveClear/HD_UI_WaveClear.h"
#include "Reward/HD_UI_Wave_Clear_Reward.h"
#include "../../HD_UI_Main.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GM.h"
#include "Logic/Manager/HD_Manager_Reward.h"

#include "Components/WidgetSwitcher.h"

void UHD_UI_WaveClear::UIWaveClearPostInit(UHD_UI_Main* ui_main)
{
	ui_main->UIMainSetUIWaveClear(this);
	_ui_reward->UIRewardPostInit();

	_switcher->SetActiveWidgetIndex(0);
}
void UHD_UI_WaveClear::UIWaveClearReward()
{
	_ui_reward->UIRewardInit();

	_switcher->SetActiveWidgetIndex(1);
}
