// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/HeadUp/HD_UI_HeadUp_Monster.h"
#include "Actor/Unit/Monster/HD_Monster.h"

#include "Components/ProgressBar.h"

void UHD_UI_HeadUp_Monster::UIEnemyHeadUpInit(AHD_Monster* mob_owner)
{
	_hp_bar->SetPercent(1.f);
}

void UHD_UI_HeadUp_Monster::UIEnemyHeadUpSetHPBar(const float f_hp_rate)
{
	_hp_bar->SetPercent(f_hp_rate);
}