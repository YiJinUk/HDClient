// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HeadUp/HD_UI_HeadUp_CPAN.h"

#include "Components/ProgressBar.h"

void UHD_UI_HeadUp_CPAN::UISetCooldown(const float f_cd_rate)
{
	_cooldown->SetPercent(f_cd_rate);
}