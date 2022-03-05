// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/HD_UI_Info.h"
#include "UI/HD_UI_Main.h"
#include "HD_UI_Info_Bottom.h"
#include "HD_UI_Info_Top.h"

void UHD_UI_Info::UIInfoPostInit(UHD_UI_Main* ui_main)
{
	_ui_info_bottom->InfoBottomPostInit();
	ui_main->UIMainSetUIInfoBottom(_ui_info_bottom);
	ui_main->UIMainSetUIInfoTop(_ui_info_top);
}