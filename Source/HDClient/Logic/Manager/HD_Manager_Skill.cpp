// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Skill.h"
#include "Logic/HD_GM.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Monster/HD_Monster.h"

void AHD_Manager_Skill::SKPostInit(AHD_GM* gm)
{
	_gm = gm;
}

void AHD_Manager_Skill::DoSkillHero(AHD_Hero* hero, AHD_Monster* mob, const FDataSkill* s_data_sk)
{
	if (!s_data_sk || !hero)  return; 
	//Ư����ų�� ���� ��� �ߵ��� �� ����

	switch (s_data_sk->GetID())
	{
	case 1:
	{
		_gm->BattleSend(hero, mob, s_data_sk->GetValue1() * (hero->GetInfoHero().GetSKAPTotal() * 0.01f), EAttackType::SKILL);
	}
		break;
	default:
		break;
	}
}