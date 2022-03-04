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

void AHD_Hero::HeroAttackBasicStart(AHD_Enemy* target)
{
	if (target)
	{
		//이미 기본공격시도중입니다
		if (_info_hero.atk_basic_status == EAttackBasicStatus::TRY) return;

		_info_hero.atk_basic_status = EAttackBasicStatus::TRY;
		_info_hero.target = target;
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_hero.target->GetActorLocation()), 0.f));
		_anim_instance->Montage_Play(_info_hero.wp_equip->GetInfoWP().anim_attack_basic, (_info_hero.GetASTotal() / 60.f) / _info_hero.anim_rate_base);
	}
}
void AHD_Hero::HeroAttackBasicNotify()
{
	if (!_info_hero.target || !_info_hero.target->GetInfoUnit().is_hit_valid)
	{
		/*피해를 주려고 했지만 애니메이션도중 적의 상태가 피격이 무효하게 바뀌었습니다*/
		_info_hero.atk_basic_status = EAttackBasicStatus::DETECT;
	}
	else
	{
		/*피해를 주고 다시 기본공격대기상태로 돌아갑니다*/
		//무기마다 기본공격양상이 다르기 때문에 무기클래스에서 공격을 시도합니다
		_info_hero.wp_equip->WPAttackBasic(_info_hero.target);
		_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}

bool AHD_Hero::HeroUpdateAS(const uint8 i_tick_1frame)
{
	return UnitUpdateAS(_info_hero.atk_basic_status, _info_hero.as_delay, _info_hero.GetASTotalDelay(), i_tick_1frame);
}

const FInfoHero& AHD_Hero::GetInfoHero() { return _info_hero; }