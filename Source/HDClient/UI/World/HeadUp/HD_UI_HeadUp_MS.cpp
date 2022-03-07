// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HeadUp/HD_UI_HeadUp_MS.h"

#include "Components/ProgressBar.h"

void UHD_UI_HeadUp_MS::UISetCooldown(const float f_cd_rate)
{
	_cooldown->SetPercent(f_cd_rate);
}