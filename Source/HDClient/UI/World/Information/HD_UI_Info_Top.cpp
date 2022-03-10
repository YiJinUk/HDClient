// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/HD_UI_Info_Top.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHD_UI_Info_Top::InfoTopInit()
{
	_stage->SetText(FText::AsNumber(1));
	_wave->SetText(FText::AsNumber(1));
	_boss_hp_bar->SetVisibility(ESlateVisibility::Hidden);
}

void UHD_UI_Info_Top::InfoTopWaveNextAndStart(const int32 i_round_stage, const int32 i_round_wave, const EWaveType e_wave_type)
{
	InfoTopSetRound(i_round_stage, i_round_wave);
	InfoTopUpdateWaveType(e_wave_type);
}

void UHD_UI_Info_Top::InfoTopUpdateWaveType(const EWaveType e_wave_type)
{
	switch (e_wave_type)
	{
	case EWaveType::MONSTER:
		_boss_hp_bar->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EWaveType::BOSS:
		_boss_hp_bar->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}

	_boss_hp_bar->SetPercent(1.f);
}

void UHD_UI_Info_Top::InfoTopSetRound(const int32 i_round_stage, const int32 i_round_wave)
{
	_stage->SetText(FText::AsNumber(i_round_stage));
	_wave->SetText(FText::AsNumber(i_round_wave));
}

void UHD_UI_Info_Top::InfoTopSetBossHPBar(const float f_boss_hp_rate) { _boss_hp_bar->SetPercent(f_boss_hp_rate); }