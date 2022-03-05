// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/MOB01/HD_MOB01001.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Logic/HD_GM.h"


void AHD_MOB01001::MOBAttackBasic()
{
	_gm->PROJSpawn(_info_monster.code_proj, GetActorLocation(), this, _info_monster.target, _info_monster.target->GetActorLocation2D());
}