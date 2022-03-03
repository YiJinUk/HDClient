// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HD_UI_Main.h"
#include "Home/HD_UI_Home.h"
#include "World/HD_UI_World.h"

#include "Components/WidgetSwitcher.h"

//void UHD_UI_Main::NativeConstruct()
//{
//	Super::NativeConstruct();
//}

void UHD_UI_Main::UIMainPostInit()
{
	_ui_home->HomePostInit();
	_ui_world->WorldPostInit();
}

void UHD_UI_Main::UIMainWorldStart()
{
	_switcher->SetActiveWidgetIndex(1);
}