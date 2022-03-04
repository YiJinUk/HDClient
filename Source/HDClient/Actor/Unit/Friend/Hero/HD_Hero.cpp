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
		//�̹� �⺻���ݽõ����Դϴ�
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
		/*���ظ� �ַ��� ������ �ִϸ��̼ǵ��� ���� ���°� �ǰ��� ��ȿ�ϰ� �ٲ�����ϴ�*/
		_info_hero.atk_basic_status = EAttackBasicStatus::DETECT;
	}
	else
	{
		/*���ظ� �ְ� �ٽ� �⺻���ݴ����·� ���ư��ϴ�*/
		//���⸶�� �⺻���ݾ���� �ٸ��� ������ ����Ŭ�������� ������ �õ��մϴ�
		_info_hero.wp_equip->WPAttackBasic(_info_hero.target);
		_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}

bool AHD_Hero::HeroUpdateAS(const uint8 i_tick_1frame)
{
	return UnitUpdateAS(_info_hero.atk_basic_status, _info_hero.as_delay, _info_hero.GetASTotalDelay(), i_tick_1frame);
}

const FInfoHero& AHD_Hero::GetInfoHero() { return _info_hero; }