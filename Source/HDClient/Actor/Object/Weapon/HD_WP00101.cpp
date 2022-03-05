// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Weapon/HD_WP00101.h"
#include "Logic/HD_GM.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Monster/HD_Monster.h"

void AHD_WP00101::WPAttackBasic(AHD_Monster* target)
{
	_gm->PROJSpawn(_info_wp.code_proj, _info_wp.owner_hero->GetActorLocation(), _info_wp.owner_hero, target);
}