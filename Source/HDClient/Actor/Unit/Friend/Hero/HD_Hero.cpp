// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/HD_Unit.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/Manager/HD_Manager_Skill.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_PC.h"
#include "Logic/HD_GI.h"

void AHD_Hero::HeroPostInit(FDataHero* s_data_hero)
{
	_info_hero.hp_base = s_data_hero->GetHP();
	_info_hero.hp_max_base = s_data_hero->GetHP();

	_info_hero.armor_max = s_data_hero->GetArmorMax();
	_info_hero.armor_heal_base = s_data_hero->GetArmorHeal();
	_info_hero.armor_recovery_base = s_data_hero->GetArmorRecovery();
	_info_hero.armor_heal_tick_max = s_data_hero->GetArmorHealTickMax();
	_info_hero.armor_recovery_tick_max = s_data_hero->GetArmorRecoveryTickMax();

	_info_hero.anim_attack_sk = s_data_hero->GetAnimAttackSK();
}
void AHD_Hero::HeroInit(FDataHero* s_data_hero)
{
	_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	_info_hero.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	_info_hero.armor_status = EArmorStatus::RECOVERY;

	_info_hero.hp_base = _info_hero.hp_max_base;
	_info_hero.as_delay = 0;

	_info_hero.dmg_base = 100;

	_info_hero.sk_data = _gi->FindDataSKByCode(s_data_hero->GetSKCode());
	_info_hero.sk_ap_base = 100;
	_info_hero.sk_cooldown_tick_max = _info_hero.sk_data->GetCooldown();
	_info_hero.sk_cooldown_tick = 0;

	UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_HEAL_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, -99999);

	//_info_hero.proj_velocity_2d = FVector2D(1.f);
}
void AHD_Hero::HeroWaveEndInit()
{
	_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	_info_hero.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	_info_hero.armor_status = EArmorStatus::RECOVERY;

	_info_hero.as_delay = 0;
	UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_HEAL_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, -99999);
	UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, -99999);
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
			/*??????????*/
			_info_hero.armor_heal_tick = 0;
			UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, _info_hero.GetArmorHeadTotal());
		}
		break;
	case EArmorStatus::RECOVERY:
		UnitSetStat(EUnitStatType::ARMOR_RECOVERY_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::ARMOR_RECOVERY_TICK) >= _info_hero.armor_recovery_tick_max)
		{
			/*??????????*/
			_info_hero.armor_recovery_tick = 0;
			UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, _info_hero.GetArmorRecoveryTotal());

			/*?????????? ???????? ?????????????? ??????????*/
			_info_hero.armor_status = EArmorStatus::HEAL;
			_info_hero.armor_heal_tick = 0;
		}
		break;
	default:
		break;
	}
}

void AHD_Hero::HeroUpdateAS(const uint8 i_tick_1frame)
{
	switch (_info_hero.atk_basic_status)
	{
	case EAttackBasicStatus::DETECT:
		break;
	case EAttackBasicStatus::TRY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackBasicStatus::DELAY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::AS_DEALY) >= _info_hero.GetASTotalDelay())
		{
			_info_hero.atk_basic_status = EAttackBasicStatus::DETECT;
		}
		break;
	default:
		break;
	}
}
void AHD_Hero::HeroAttackBasicStart()
{
	//???? ????????????????????
	if (_info_hero.atk_basic_status == EAttackBasicStatus::TRY) return;

	_info_hero.atk_basic_status = EAttackBasicStatus::TRY;
	_info_hero.as_delay = 0;
	_anim_instance->Montage_Play(_info_hero.wp_equip->GetInfoWP().anim_attack_basic, (_info_hero.GetASTotal() / 60.f) / _info_hero.anim_rate_base);
}
void AHD_Hero::HeroAttackBasicNotify()
{
	//if (!_info_hero.target || !_info_hero.target->GetInfoUnit().is_hit_valid)
	//{
	//	//UHD_FunctionLibrary::GSaveLog("HeroAttackBasicNotify.Target InValid", "Hero Attack.txt");
	//	/*?????? ?????? ?????? ?????????????? ???? ?????? ?????? ???????? ????????????*/
	//	_info_hero.atk_basic_status = EAttackBasicStatus::DETECT;
	//	_info_hero.as_delay = _info_hero.GetASTotalDelay();
	//}
	//else
	//{
	//	//UHD_FunctionLibrary::GSaveLog("HeroAttackBasicNotify.Target Valid Attack", "Hero Attack.txt");
	//	/*?????? ???? ???? ?????????????????? ??????????*/
	//	//???????? ?????????????? ?????? ?????? ?????????????? ?????? ??????????
	//	_info_hero.wp_equip->WPAttackBasic(_info_hero.target);
	//	_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
	//}
	_info_hero.wp_equip->WPAttackBasic(_info_hero.target, FVector2D(_info_hero.look_loc.X, _info_hero.look_loc.Y));
	_info_hero.atk_basic_status = EAttackBasicStatus::DELAY;
}
void AHD_Hero::UnitDoAttackBasic(AHD_Unit* unit_target)
{
	_gm->BattleSend(this, unit_target, _info_hero.GetAttackBasicDMG(), EAttackType::BASIC);
}

void AHD_Hero::HeroUpdateReduceCooldown(const uint8 i_tick_1frame)
{
	switch (_info_hero.atk_sk_status)
	{
	case EAttackSkillStatus::DETECT:
		break;
	case EAttackSkillStatus::TRY:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackSkillStatus::COOLDOWN:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::SK_COOLDOWN_TICK) >= _info_hero.sk_cooldown_tick_max)
		{
			_info_hero.atk_sk_status = EAttackSkillStatus::DETECT;
		}
		break;
	default:
		break;
	}
}
void AHD_Hero::HeroAttackSkillStart()
{
	AHD_Monster* mob_target = _gm->FindMOBFirstByV2(GetActorLocation2D());
	if (mob_target)
	{
		//???? ????????????????????
		if (_info_hero.atk_sk_status == EAttackSkillStatus::TRY) return;

		_info_hero.atk_sk_status = EAttackSkillStatus::TRY;
		_info_hero.target = mob_target;
		_info_hero.sk_cooldown_tick = 0;
		_anim_instance->Montage_Play(_info_hero.anim_attack_sk);
	}
}
void AHD_Hero::HeroAttackSKNotify()
{
	if (!_info_hero.target || !_info_hero.target->GetInfoUnit().is_hit_valid)
	{
		/*?????? ?????? ?????? ?????????????? ???? ?????? ?????? ???????? ????????????*/
		_info_hero.atk_sk_status = EAttackSkillStatus::DETECT;
		_info_hero.sk_cooldown_tick = _info_hero.sk_cooldown_tick_max;
	}
	else
	{
		/*?????? ???? ???? ?????????????????? ??????????*/
		//???????? ?????????????? ?????? ?????? ?????????????? ?????? ??????????
		_gm->PROJSpawn("PROJ10003", GetActorLocation(), this, _info_hero.target);
		_info_hero.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	}
}
void AHD_Hero::UnitDoAttackSK(AHD_Unit* unit_target)
{
	//_gm->BattleSend(this,unit_target,)
	_gm->GetManagerSK()->DoSkillHero(this, Cast<AHD_Monster>(unit_target), _info_hero.sk_data);
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
		UnitSetHP(_info_hero.hp_base, _info_hero.hp_max_base, i_value);
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
	case EUnitStatType::DMG:
		switch (e_stat_by)
		{
		case EUnitStatBy::BUFF:
			UnitSetDMG(_info_hero.dmg_base_by_bf, i_value);
			break;
		default:
			break;
		}
		break;
	case EUnitStatType::AS_DEALY:
		UnitSetAS(_info_hero.as_delay, _info_hero.GetASTotalDelay(), i_value);
		break;
	case EUnitStatType::SK_COOLDOWN_TICK:
		UnitSetCooldown(_info_hero.sk_cooldown_tick, _info_hero.sk_cooldown_tick_max, i_value);
		_pc->PCUIUpdateStat(e_stat_type, e_stat_by, 0, _info_hero.GetSKCooldownRate());
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
	case EUnitStatType::DMG:
		return _info_hero.dmg_base;
		break;
	case EUnitStatType::AS_DEALY:
		return _info_hero.as_delay;
		break;
	case EUnitStatType::SK_COOLDOWN_TICK:
		return _info_hero.sk_cooldown_tick;
		break;
	default:
		break;
	}

	return int32();
}

void AHD_Hero::HeroSetPROJVelocity(const FVector& v_look_loc)
{ 
	_info_hero.look_loc = v_look_loc;
	SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), v_look_loc), 0.f));
}
const FInfoHero& AHD_Hero::GetInfoHero() { return _info_hero; }