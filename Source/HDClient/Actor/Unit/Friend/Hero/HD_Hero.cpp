// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/HD_Unit.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_PC.h"

void AHD_Hero::HeroPostInit(AHD_PC* pc, FDataHero* s_data_hero)
{
	_pc = pc;
	_info_hero.hp_base = s_data_hero->GetHP();
	_info_hero.hp_max_base = s_data_hero->GetHP();

	_info_hero.armor_max = s_data_hero->GetArmorMax();
	_info_hero.armor_heal_base = s_data_hero->GetArmorHeal();
	_info_hero.armor_recovery_base = s_data_hero->GetArmorRecovery();
	_info_hero.armor_heal_tick_max = s_data_hero->GetArmorHealTickMax();
	_info_hero.armor_recovery_tick_max = s_data_hero->GetArmorRecoveryTickMax();
}
void AHD_Hero::HeroInit()
{
	_info_hero.hp_base = _info_hero.hp_max_base;
	_info_hero.as_delay = 0;
	_info_hero.armor_status = EArmorStatus::RECOVERY;
	UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_HEAL_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, -99999);
}
void AHD_Hero::HeroWaveEndInit()
{
	_info_hero.as_delay = 0;
	_info_hero.armor_status = EArmorStatus::RECOVERY;
	UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_HEAL_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, -99999);
}
void AHD_Hero::HeroToHomeInit()
{
	_anim_instance->StopAllMontages(-1.f);
}

void AHD_Hero::HeroChangeWeapon(AHD_Weapon* wp_change)
{
	if (!wp_change) return;
	_info_hero.str_base = wp_change->GetInfoWP().str;
	_info_hero.as_base = wp_change->GetInfoWP().as;
	_info_hero.code_wp_equip = wp_change->GetInfoWP().code;
	_info_hero.wp_equip = wp_change;
	_info_hero.anim_rate_base = _info_hero.as_base / 60.f;
}

void AHD_Hero::HeroUpdateHealArmor(const uint8 i_tick_1frame)
{
	switch (_info_hero.armor_status)
	{
	case EArmorStatus::NO:
		break;
	case EArmorStatus::HEAL:
		UnitSetStat(EUnitStatType::ARMOR_HEAL_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::ARMOR_HEAL_TICK) >= _info_hero.armor_heal_tick_max)
		{
			/*회복합니다*/
			_info_hero.armor_heal_tick = 0;
			UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, _info_hero.GetArmorHeadTotal());
		}
		break;
	case EArmorStatus::RECOVERY:
		UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::ARMOR_RECOVERY_TICK) >= _info_hero.armor_recovery_tick_max)
		{
			/*회복합니다*/
			_info_hero.armor_recovery_tick = 0;
			UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, _info_hero.GetArmorRecoveryTotal());

			/*방어복구에 성공해서 방어회복모드로 변경됩니다*/
			_info_hero.armor_status = EArmorStatus::HEAL;
			_info_hero.armor_heal_tick = 0;
		}
		break;
	default:
		break;
	}
}

bool AHD_Hero::HeroUpdateAS(const uint8 i_tick_1frame)
{
	return UnitUpdateAS(_info_hero.atk_basic_status, _info_hero.as_delay, _info_hero.GetASTotalDelay(), i_tick_1frame);
}
void AHD_Hero::HeroAttackBasicStart(AHD_Monster* target)
{
	if (target)
	{
		//이미 기본공격시도중입니다
		if (_info_hero.atk_basic_status == EAttackBasicStatus::TRY) return;

		_info_hero.atk_basic_status = EAttackBasicStatus::TRY;
		_info_hero.target = target;
		_info_hero.as_delay = 0;
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_hero.target->GetActorLocation()), 0.f));
		_anim_instance->Montage_Play(_info_hero.wp_equip->GetInfoWP().anim_attack_basic, (_info_hero.GetASTotal() / 60.f) / _info_hero.anim_rate_base);
	}
}
void AHD_Hero::HeroAttackBasicNotify()
{
	if (!_info_hero.target || !_info_hero.target->GetInfoUnit().is_hit_valid)
	{
		//UHD_FunctionLibrary::GSaveLog("HeroAttackBasicNotify.Target InValid", "Hero Attack.txt");
		/*피해를 주려고 했지만 애니메이션도중 적의 상태가 피격이 무효하게 바뀌었습니다*/
		_info_hero.atk_basic_status = EAttackBasicStatus::DETECT;
		_info_hero.as_delay = _info_hero.GetASTotalDelay();
	}
	else
	{
		//UHD_FunctionLibrary::GSaveLog("HeroAttackBasicNotify.Target Valid Attack", "Hero Attack.txt");
		/*피해를 주고 다시 기본공격대기상태로 돌아갑니다*/
		//무기마다 기본공격양상이 다르기 때문에 무기클래스에서 공격을 시도합니다
		_info_hero.wp_equip->WPAttackBasic(_info_hero.target);
		_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}
void AHD_Hero::UnitDoAttackBasic(AHD_Unit* unit_target)
{
	_gm->BattleSend(this, unit_target, _info_hero.GetAttackBasicDMG(), EAttackType::BASIC);
}

void AHD_Hero::UnitHit(const FBattleHitResult& s_battle_hit_result)
{
	if (s_battle_hit_result.is_broken_armor && _info_hero.armor_status != EArmorStatus::RECOVERY)
	{
		_info_hero.armor_status = EArmorStatus::RECOVERY;
		_info_hero.armor_recovery_tick = 0;
	}
}
void AHD_Hero::UnitDeath()
{
	_gm->WorldGameOver();
}

void AHD_Hero::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		_info_hero.hp_base += i_value;
		if (_info_hero.hp_base <= 0)
		{
			_info_hero.hp_base = 0;
		}
		else if (_info_hero.hp_base > _info_hero.hp_max_base)
		{
			_info_hero.hp_base = _info_hero.hp_max_base;
		}

		_pc->PCUIUpdateStat(e_stat_type, e_stat_by, 0, _info_hero.GetHPRate());
		break;
	case EUnitStatType::ARMOR:
		_info_hero.armor += i_value;
		if (_info_hero.armor <= 0)
			_info_hero.armor = 0;
		else if (_info_hero.armor > _info_hero.armor_max)
			_info_hero.armor = _info_hero.armor_max;

		_pc->PCUIUpdateStat(e_stat_type, e_stat_by, _info_hero.armor);
		break;
	case EUnitStatType::ARMOR_HEAL_TICK:
		_info_hero.armor_heal_tick += i_value;
		if (_info_hero.armor_heal_tick <= 0)
			_info_hero.armor_heal_tick = 0;
		else if (_info_hero.armor_heal_tick > _info_hero.armor_heal_tick_max)
			_info_hero.armor_heal_tick = _info_hero.armor_heal_tick_max;

		_pc->PCUIUpdateStat(e_stat_type, e_stat_by, 0, _info_hero.GetArmorHealRate());
		break;
	case EUnitStatType::ARMOR_RECOVERY_TICK:
		_info_hero.armor_recovery_tick += i_value;
		if (_info_hero.armor_recovery_tick <= 0)
			_info_hero.armor_recovery_tick = 0;
		else if (_info_hero.armor_recovery_tick > _info_hero.armor_recovery_tick_max)
			_info_hero.armor_recovery_tick = _info_hero.armor_recovery_tick_max;

		_pc->PCUIUpdateStat(e_stat_type, e_stat_by, 0, _info_hero.GetArmorRecoveryRate());
		break;
	default:
		break;
	}
}
const int32 AHD_Hero::UnitGetStat(const EUnitStatType e_stat_type)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		return _info_hero.GetHPTotal();
		break;
	case EUnitStatType::ARMOR:
		return _info_hero.armor;
		break;
	case EUnitStatType::ARMOR_HEAL_TICK:
		return _info_hero.armor_heal_tick;
		break;
	case EUnitStatType::ARMOR_RECOVERY_TICK:
		return _info_hero.armor_recovery_tick;
		break;
	default:
		break;
	}

	return int32();
}

const FInfoHero& AHD_Hero::GetInfoHero() { return _info_hero; }