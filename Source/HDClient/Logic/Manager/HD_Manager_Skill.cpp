// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Skill.h"
#include "HD_Manager_Buff.h"
#include "Logic/HD_GM.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "Actor/Unit/Friend/MagicStone/HD_MagicStone.h"
#include "Actor/Unit/Monster/HD_Monster.h"

void AHD_Manager_Skill::SKPostInit(AHD_GM* gm, AHD_Manager_Buff* manager_bf)
{
	_gm = gm;
	_manager_bf = manager_bf;
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

void AHD_Manager_Skill::DoSkillCPAN(AHD_Companion* cpan, AHD_Unit* unit, const FDataSkill* s_data_sk)
{
	if (!s_data_sk || !cpan)  return;
	//Ư����ų�� ���� ��� �ߵ��� �� ����

	switch (s_data_sk->GetID())
	{
	case 10001:
	{
		/*�������� value_1��ŭ ���ݷ� �ο�*/
		_manager_bf->BFCastStart("BF00001", cpan, unit, EBuffPhase::IMMEDIATELY, EBuffTimer::TIMER, s_data_sk->GetValue2(), EBuffOverlap::NEW, "0", s_data_sk->GetValue1());
	}
	break;
	case 10002:
	{
		_gm->BattleSend(cpan, unit, s_data_sk->GetValue1() * (cpan->GetInfoCPAN().GetSKAPTotal() * 0.01f), EAttackType::SKILL);
	}
	break;
	default:
		break;
	}
}

void AHD_Manager_Skill::DoSkillMS(AHD_MagicStone* ms, AHD_Monster* mob, const FDataSkill* s_data_sk)
{
	if (!s_data_sk || !ms)  return;
	//Ư����ų�� ���� ��� �ߵ��� �� ����

	switch (s_data_sk->GetID())
	{
	case 20001:
	{
		_gm->BattleSend(ms, mob, s_data_sk->GetValue1() * (ms->GetInfoMS().GetMPTotal() * 0.01f), EAttackType::SKILL);
	}
	break;
	default:
		break;
	}
}