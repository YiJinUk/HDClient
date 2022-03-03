// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Weapon/HD_WP00201.h"
#include "Logic/HD_GM.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"

void AHD_WP00201::WPAttackBasic(AHD_Enemy* target)
{
	_gm->PROJSpawn(_info_wp.code_proj, EPROJTargetType::STRAIGHT, EPROJAttackType::HERO_ATTACK_BASIC, _info_wp.owner_hero->GetActorLocation(), _info_wp.owner_hero, nullptr, target->GetActorLocation2D());
}
