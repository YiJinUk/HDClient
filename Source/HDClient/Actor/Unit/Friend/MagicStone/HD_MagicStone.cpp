// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Friend/MagicStone/HD_MagicStone.h"
#include "Actor/Unit/HD_Unit.h"
#include "Actor/Unit/Monster/HD_Monster.h"
#include "Logic/Animation/HD_AM.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/Manager/HD_Manager_Skill.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_GI.h"
#include "UI/World/HeadUp/HD_UI_HeadUp_MS.h"

#include "Components/WidgetComponent.h"

AHD_MagicStone::AHD_MagicStone()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> W_HEAD_NOTIFY_BP(TEXT("/Game/_HDClient/UI/World/HeadUp/HDWB_UI_HeadUp_MS"));
	if (W_HEAD_NOTIFY_BP.Succeeded() && _ui_headup)
	{
		_ui_headup->SetWidgetClass(W_HEAD_NOTIFY_BP.Class);
	}
}
void AHD_MagicStone::MSPostInit(FDataMS* s_data_ms, const FVector& v_loc_spawn)
{
	_ui_headup_ms = Cast<UHD_UI_HeadUp_MS>(_ui_headup->GetUserWidgetObject());
	SetActorLocation(v_loc_spawn);

	_info_ms.code = s_data_ms->GetCode();
	_info_ms.int_base = s_data_ms->GetINT();
	_info_ms.mp_base = s_data_ms->GetMP();
}
void AHD_MagicStone::MSInit(FDataMS* s_data_ms)
{
	_info_ms.code_proj = s_data_ms->GetCodePROJ();
	_info_ms.atk_sk_status = EAttackSkillStatus::COOLDOWN;
	_info_ms.target = nullptr;

	_info_ms.sk_data = _gi->FindDataSKByCode(s_data_ms->GetCodeSK());
	_info_ms.sk_cooldown_tick_max_base = _info_ms.sk_data->GetCooldown();

	UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, -99999);
}

void AHD_MagicStone::MSUpdateReduceCooldown(const uint8 i_tick_1frame)
{
	switch (_info_ms.atk_sk_status)
	{
	case EAttackSkillStatus::DETECT:
		break;
	case EAttackSkillStatus::TRY:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackSkillStatus::COOLDOWN:
		UnitSetStat(EUnitStatType::SK_COOLDOWN_TICK, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::SK_COOLDOWN_TICK) >= _info_ms.GetCDTickMaxTotal())
		{
			_info_ms.atk_sk_status = EAttackSkillStatus::DETECT;
		}
		break;
	default:
		break;
	}
}
void AHD_MagicStone::MSAttackSkillStart()
{
	AHD_Monster* mob_target = _gm->FindMOBFirstByV2(GetActorLocation2D());
	if (mob_target)
	{
		_info_ms.atk_sk_status = EAttackSkillStatus::COOLDOWN;
		_info_ms.target = mob_target;
		_info_ms.sk_cooldown_tick = 0;

		_gm->PROJSpawn(_info_ms.code_proj, GetActorLocation(), this, _info_ms.target);
	}
}
void AHD_MagicStone::UnitDoAttackSK(AHD_Unit* unit_target)
{
	_gm->GetManagerSK()->DoSkillMS(this, Cast<AHD_Monster>(unit_target), _info_ms.sk_data);
}

void AHD_MagicStone::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value)
{
	switch (e_stat_type)
	{
	case EUnitStatType::SK_COOLDOWN_TICK:
		UnitSetCooldown(_info_ms.sk_cooldown_tick, _info_ms.GetCDTickMaxTotal(), i_value);
		_ui_headup_ms->UISetCooldown(_info_ms.GetCDRate());
		break;
	default:
		break;
	}
}
const int32 AHD_MagicStone::UnitGetStat(const EUnitStatType e_stat_type)
{
	switch (e_stat_type)
	{
	case EUnitStatType::SK_COOLDOWN_TICK:
		return _info_ms.sk_cooldown_tick;
		break;
	default:
		break;
	}

	return int32();
}


const FInfoMS& AHD_MagicStone::GetInfoMS() { return _info_ms; }