// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HD_UI_Main.h"
#include "Home/HD_UI_Home.h"
#include "World/HD_UI_World.h"
#include "World/Information/HD_UI_Info_Bottom.h"

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
	_switcher->SetActiveWidgetIndex(1);
}

void UHD_UI_Main::UIMainUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value, const float f_value)
{
	switch (e_unit_stat_type)
	{
	case EUnitStatType::HP:
		_ui_info_bottom->InfoBottomSetHPBar(f_value);
		break;
	default:
		break;
	}
}

void UHD_UI_Main::UIMainSetUIInfoBottom(UHD_UI_Info_Bottom* ui_info_bottom) { _ui_info_bottom = ui_info_bottom; }