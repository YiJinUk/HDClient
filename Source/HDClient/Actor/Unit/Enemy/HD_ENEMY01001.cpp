// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Enemy/HD_ENEMY01001.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Logic/HD_GM.h"


void AHD_ENEMY01001::EnemyAttackBasic()
{
	_gm->PROJSpawn(_info_enemy.code_proj, GetActorLocation(), this, _info_enemy.target, _info_enemy.target->GetActorLocation2D());
}