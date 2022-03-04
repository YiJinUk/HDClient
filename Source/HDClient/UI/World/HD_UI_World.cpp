// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HD_UI_World.h"
#include "UI/HD_UI_Main.h"
#include "Information/HD_UI_Info_Bottom.h"

void UHD_UI_World::WorldPostInit(UHD_UI_Main* ui_main)
{
	_ui_info_bottom->InfoBottomPostInit();
	ui_main->UIMainSetUIInfoBottom(_ui_info_bottom);
}