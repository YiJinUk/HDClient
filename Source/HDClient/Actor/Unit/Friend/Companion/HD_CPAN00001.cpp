// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Companion/HD_CPAN00001.h"
#include "../Hero/HD_Hero.h"
#include "Logic/HD_GM.h"
#include "Logic/Manager/HD_Manager_Skill.h"

void AHD_CPAN00001::CPANAttackSKNotify()
{
	_gm->GetManagerSK()->DoSkillCPAN(this, _gm->GetHero(), _info_cpan.sk_data);
	_info_cpan.atk_sk_status = EAttackSkillStatus::COOLDOWN;
}