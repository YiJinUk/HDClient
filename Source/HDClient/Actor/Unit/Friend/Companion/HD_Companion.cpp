// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_GI.h"
#include "Logic/Manager/HD_Manager_Skill.h"

void AHD_Companion::CPANPostInit(FDataCPAN* s_data_cpan)
{
	_info_cpan.code = s_data_cpan->GetCode();
	_info_cpan.anim_attack_basic = s_data_cpan->GetAnimAttackBasic();
	_info_cpan.anim_attack_sk = s_data_cpan->GetAnimAttackSK();
	_info_cpan.code_proj_basic = s_data_cpan->GetCodePROJBasic();
	_info_cpan.code_proj_sk = s_data_cpan->GetCodePROJSK();
	_info_cpan.str_base = s_data_cpan->GetSTR();
	_info_cpan.as_base = s_data_cpan->GetAS();

	_info_cpan.sk_data = _gi->FindDataSKByCode(s_data_cpan->GetCodeSK());
	_info_cpan.sk_ap_base = 100;
	_info_cpan.sk_cooldown_tick_max = _info_cpan.sk_data->GetCooldown();
	_info_cpan.sk_cooldown_tick = 0;

	_info_cpan.anim_rate_base = _info_cpan.as_base / 60.f;
}
void AHD_Companion::CPANInit(const FVector& v_loc_spawn)
{
	UnitSetActiveTick(true);
	SetActorLocation(v_loc_spawn);

	_info_cpan.atk_basic_status = EAttackBasicStatus::DELAY;
	_info_cpan.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	_info_cpan.as_delay = 0;

	UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, -99999);
}
void AHD_Companion::CPANWaveEndInit()
{
	_info_cpan.atk_basic_status = EAttackBasicStatus::DELAY;
	_info_cpan.atk_sk_status = EAttackSkillStatus::COOLDOWN;

	_info_cpan.as_delay = 0;
	UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, -99999);
}

void AHD_Companion::CPANUpdateAS(const uint8 i_tick_1frame)
{
	switch (_info_cpan.atk_basic_status)
	{
	case EAttackBasicStatus::DETECT:
		break;
	case EAttackBasicStatus::TRY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackBasicStatus::DELAY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::AS_DEALY) >= _info_cpan.GetASTotalDelay())
		{
			_info_cpan.atk_basic_status = EAttackBasicStatus::DETECT;
		}
		break;
	default:
		break;
	}
}
void AHD_Companion::CPANAttackBasicStart(AHD_Monster* target)
{
	if (target)
	{
		//이미 기본공격시도중입니다
		if (_info_cpan.atk_basic_status == EAttackBasicStatus::TRY) return;

		_info_cpan.atk_basic_status = EAttackBasicStatus::TRY;
		_info_cpan.target = target;
		_info_cpan.as_delay = 0;
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_cpan.target->GetActorLocation()), 0.f));
		_anim_instance->Montage_Play(_info_cpan.anim_attack_basic, (_info_cpan.GetASTotal() / 60.f) / _info_cpan.anim_rate_base);
		//_anim_instance->Montage_Play(_info_cpan.anim_attack_basic);
	}
}
void AHD_Companion::CPANAttackBasicNotify()
{
	if (!_info_cpan.target || !_info_cpan.target->GetInfoUnit().is_hit_valid)
	{
		_info_cpan.atk_basic_status = EAttackBasicStatus::DETECT;
		_info_cpan.as_delay = _info_cpan.GetASTotalDelay();
	}
	else
	{
		CPANAttackBasic();
		_info_cpan.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}
void AHD_Companion::CPANAttackBasic()
{
	_gm->PROJSpawn(_info_cpan.code_proj_basic, GetActorLocation(), this, _info_cpan.target, _info_cpan.target->GetActorLocation2D());
}
void AHD_Companion::UnitDoAttackBasic(AHD_Unit* unit_target)
{
	_gm->BattleSend(this, unit_target, _info_cpan.GetAttackBasicDMG(), EAttackType::BASIC);
}

void AHD_Companion::CPANUpdateReduceCooldown(const uint8 i_tick_1frame)
{
	switch (_info_cpan.atk_sk_status)
	{
	case EAttackSkillStatus::DETECT:
		break;
	case EAttackSkillStatus::TRY:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackSkillStatus::COOLDOWN:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::SK_COOLDOWN_TICK) >= _info_cpan.sk_cooldown_tick_max)
		{
			_info_cpan.atk_sk_status = EAttackSkillStatus::DETECT;
		}
		break;
	default:
		break;
	}
}
void AHD_Companion::CPANAttackSkillStart()
{
	AHD_Monster* mob_target = _gm->FindMOBFirstByV2(GetActorLocation2D());
	if (mob_target)
	{
		//이미 기본공격시도중입니다
		if (_info_cpan.atk_sk_status == EAttackSkillStatus::TRY) return;

		_info_cpan.atk_sk_status = EAttackSkillStatus::TRY;
		_info_cpan.target = mob_target;
		_info_cpan.sk_cooldown_tick = 0;
		SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_cpan.target->GetActorLocation()), 0.f));
		_anim_instance->Montage_Play(_info_cpan.anim_attack_sk);
	}
}
void AHD_Companion::CPANAttackSKNotify()
{
	//override
	if (!_info_cpan.target || !_info_cpan.target->GetInfoUnit().is_hit_valid)
	{
		_info_cpan.atk_sk_status = EAttackSkillStatus::DETECT;
		_info_cpan.sk_cooldown_tick = _info_cpan.sk_cooldown_tick_max;
	}
	else
	{
		_gm->PROJSpawn(_info_cpan.code_proj_sk, GetActorLocation(), this, _info_cpan.target);
		_info_cpan.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	}
}
void AHD_Companion::UnitDoAttackSK(AHD_Unit* unit_target)
{
	_gm->GetManagerSK()->DoSkillCPAN(this, Cast<AHD_Monster>(unit_target), _info_cpan.sk_data);
}

void AHD_Companion::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value)
{
	switch (e_stat_type)
	{
	case EUnitStatType::DMG:
		switch (e_stat_by)
		{
		case EUnitStatBy::BUFF:
			UnitSetDMG(_info_cpan.dmg_base_by_bf, i_value);
			break;
		default:
			break;
		}
		break;
	case EUnitStatType::AS_DEALY:
		UnitSetAS(_info_cpan.as_delay, _info_cpan.GetASTotalDelay(), i_value);
		break;
	case EUnitStatType::SK_COOLDOWN_TICK:
		UnitSetCooldown(_info_cpan.sk_cooldown_tick, _info_cpan.sk_cooldown_tick_max, i_value);
		break;
	default:
		break;
	}
}
const int32 AHD_Companion::UnitGetStat(const EUnitStatType e_stat_type)
{
	switch (e_stat_type)
	{
	case EUnitStatType::DMG:
		return _info_cpan.dmg_base;
		break;
	case EUnitStatType::AS_DEALY:
		return _info_cpan.as_delay;
		break;
	case EUnitStatType::SK_COOLDOWN_TICK:
		return _info_cpan.sk_cooldown_tick;
		break;
	default:
		break;
	}

	return int32();
}

const FInfoCPAN& AHD_Companion::GetInfoCPAN() { return _info_cpan; }