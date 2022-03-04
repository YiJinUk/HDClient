// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_PC.h"
#include "HD_GM.h"
#include "UI/HD_UI_Main.h"

void AHD_PC::PCPostInit()
{
	PCBPPostInit();
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_ui_main = PCBPCreateWidgetMain();
	_ui_main->UIMainPostInit();
}

void AHD_PC::PCWorldStart()
{
	_ui_main->UIMainWorldStart();
	_gm->WorldStart();
}

void AHD_PC::PCUIUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value, const float f_value)
{
	_ui_main->UIMainUpdateStat(e_unit_stat_type, e_unit_stat_by, i_value, f_value);
}