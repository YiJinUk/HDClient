// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Enemy/HD_UI_Enemy_HeadUp.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"

#include "Components/ProgressBar.h"

void UHD_UI_Enemy_HeadUp::UIEnemyHeadUpInit(AHD_Enemy* enemy_owner)
{
	_hp_bar->SetPercent(1.f);
}

void UHD_UI_Enemy_HeadUp::UIEnemyHeadUpSetHPBar(const float f_hp_rate)
{
	_hp_bar->SetPercent(f_hp_rate);
}