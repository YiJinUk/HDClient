// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/HD_UI_Info_Bottom.h"

#include "Components/ProgressBar.h"

void UHD_UI_Info_Bottom::InfoBottomPostInit()
{
	_hp_bar->SetPercent(1.f);
}

void UHD_UI_Info_Bottom::InfoBottomSetHPBar(const float f_hp_rate)
{
	_hp_bar->SetPercent(f_hp_rate);
}