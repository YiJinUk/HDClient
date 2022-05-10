// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HD_UI_Main.h"
#include "Home/HD_UI_Home.h"
#include "World/HD_UI_World.h"
#include "World/Information/HD_UI_Info_Bottom.h"
#include "World/Information/HD_UI_Info_Top.h"
#include "World/WaveClear/HD_UI_WaveClear.h"

#include "Components/WidgetSwitcher.h"

//void UHD_UI_Main::NativeConstruct()
//{
//	Super::NativeConstruct();
//}

void UHD_UI_Main::UIMainPostInit()
{
	_ui_home->HomePostInit();
	_ui_world->WorldPostInit(this);
}

void UHD_UI_Main::UIMainWorldStart()
{
	_ui_world->WorldInit();

	_ui_info_bottom->InfoBottomSetHPBar(1.f);
	_ui_info_top->InfoTopInit();

	_switcher->SetActiveWidgetIndex(1);
}
void UHD_UI_Main::UIMainWorldGameOver()
{
	_ui_world->UIWorldGameOver();
}
void UHD_UI_Main::UIMainReturnToHome()
{
	_switcher->SetActiveWidgetIndex(0);
	_ui_world->UIWorldReturnToHome();
}
void UHD_UI_Main::UIMainWorldClear()
{
	_ui_world->UIWorldWorldClear();
}
void UHD_UI_Main::UIMainClearToHome()
{
	_switcher->SetActiveWidgetIndex(0);
	_ui_world->UIWorldClearToHome();
}

void UHD_UI_Main::UIMainWaveNextAndStart(const int32 i_round_stage, const int32 i_round_wave, const EWaveType e_wave_type)
{
	_ui_info_top->InfoTopWaveNextAndStart(i_round_stage, i_round_wave, e_wave_type);
}
void UHD_UI_Main::UIMainWaveClear()
{
	_ui_world->UIWorldWaveClear();
}
void UHD_UI_Main::UIMainWaveClearReward()
{
	_ui_wave_clear->UIWaveClearReward();
}

void UHD_UI_Main::UIMainUpdateBossHPRate(const float f_boss_hp_rate)
{
	_ui_info_top->InfoTopSetBossHPBar(f_boss_hp_rate);
}

void UHD_UI_Main::UIMainRewardToSelect()
{
	//_ui_wave_clear->UIWaveClearRewardToSelect();
}

void UHD_UI_Main::UIMainUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value, const float f_value)
{
	switch (e_unit_stat_type)
	{
	case EUnitStatType::HP:
		_ui_info_bottom->InfoBottomSetHPBar(f_value);
		break;
	case EUnitStatType::ARMOR_HEAL_TICK:
	case EUnitStatType::ARMOR_RECOVERY_TICK:
		_ui_info_bottom->InfoBottomSetArmorBar(f_value);
		break;
	case EUnitStatType::ARMOR:
		_ui_info_bottom->InfoBottomSetArmorText(i_value);
		break;
	case EUnitStatType::SK_COOLDOWN_TICK:
		_ui_info_bottom->InfoBottomSetSKCooldownBar(f_value);
		break;
	default:
		break;
	}
}

void UHD_UI_Main::UIMainSetUIInfoBottom(UHD_UI_Info_Bottom* ui_info_bottom) { _ui_info_bottom = ui_info_bottom; }
void UHD_UI_Main::UIMainSetUIInfoTop(UHD_UI_Info_Top* ui_info_top) { _ui_info_top = ui_info_top; }
void UHD_UI_Main::UIMainSetUIWaveClear(UHD_UI_WaveClear* ui_wave_clear) { _ui_wave_clear = ui_wave_clear; }