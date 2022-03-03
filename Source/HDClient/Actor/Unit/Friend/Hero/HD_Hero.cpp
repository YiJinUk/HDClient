// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_FunctionLibrary.h"

void AHD_Hero::HeroChangeWeapon(AHD_Weapon* wp_change)
{
	if (!wp_change) return;
	_info_hero.str_base = wp_change->GetInfoWP().str;
	_info_hero.as_base = wp_change->GetInfoWP().as;
	_info_hero.code_wp_equip = wp_change->GetInfoWP().code;
	_info_hero.wp_equip = wp_change;
	_info_hero.anim_rate_base = _info_hero.as_base / 60.f;
}

void AHD_Hero::AttackBasicStart(AHD_Enemy* target)
{
	if (target)
	{
		//이미 기본공격시도중입니다
		if (_info_hero.atk_basic_status == EHeroAttackBasicStatus::TRY) return;

		_info_hero.atk_basic_status = EHeroAttackBasicStatus::TRY;
		_info_hero.target = target;
		_anim_instance->Montage_Play(_info_hero.wp_equip->GetInfoWP().anim_attack_basic);
	}
}
void AHD_Hero::AttackBasicNotify()
{
	//if (!_info_hero.target || _info_hero.target->GetInfoEnemy().is_death)
	if (!_info_hero.target)
	{
		/*피해를 주려고 했지만 애니메이션도중 적이 죽어서 다시 적을 찾습니다*/
		_info_hero.atk_basic_status = EHeroAttackBasicStatus::DETECT;
	}
	else
	{
		/*피해를 주고 다시 기본공격대기상태로 돌아갑니다*/
		_info_hero.atk_basic_status = EHeroAttackBasicStatus::DELAY;
	}
}

bool AHD_Hero::HeroUpdateAS(const uint8 i_tick)
{
	switch (_info_hero.atk_basic_status)
	{
	case EHeroAttackBasicStatus::DETECT:
		break;
	case EHeroAttackBasicStatus::TRY:
		if (_info_hero.as_delay < _info_hero.GetASTotalDelay())
			_info_hero.as_delay += i_tick;
		break;
	case EHeroAttackBasicStatus::DELAY:
		if (_info_hero.as_delay >= _info_hero.GetASTotalDelay())
		{
			_info_hero.as_delay = 0;
			_info_hero.atk_basic_status = EHeroAttackBasicStatus::DETECT;
		}
		else
			_info_hero.as_delay += i_tick;
		break;
	default:
		break;
	}

	if (_info_hero.atk_basic_status == EHeroAttackBasicStatus::DETECT)
		return true;
	else
		return false;
}

const FInfoHero& AHD_Hero::GetInfoHero() { return _info_hero; }