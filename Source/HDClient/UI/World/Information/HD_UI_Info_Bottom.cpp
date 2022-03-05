// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/HD_UI_Info_Bottom.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHD_UI_Info_Bottom::InfoBottomPostInit()
{
	_hp_bar->SetPercent(1.f);
	_armor_bar->SetPercent(0.f);
	_armor->SetText(FText::AsNumber(0));
}

void UHD_UI_Info_Bottom::InfoBottomSetHPBar(const float f_hp_rate)
{
	_hp_bar->SetPercent(f_hp_rate);
}
void UHD_UI_Info_Bottom::InfoBottomSetArmorBar(const float f_armor_rate)
{
	_armor_bar->SetPercent(f_armor_rate);
}
void UHD_UI_Info_Bottom::InfoBottomSetArmorText(const int32 i_armor)
{
	_armor->SetText(FText::AsNumber(i_armor));
}