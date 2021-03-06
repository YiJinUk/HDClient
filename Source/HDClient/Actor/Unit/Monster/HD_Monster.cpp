// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Monster/HD_Monster.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/Animation/HD_AM_Monster.h"
#include "Logic/HD_GM.h"
#include "Logic/HD_PC.h"
#include "UI/World/HeadUp/HD_UI_HeadUp_Monster.h"

#include "Components/WidgetComponent.h"

AHD_Monster::AHD_Monster(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = false;

	//static ConstructorHelpers::FClassFinder<UUserWidget> W_HEAD_NOTIFY_BP(TEXT("/Game/_HDClient/UI/World/HeadUp/HDWB_UI_HeadUp_Monster"));
	//if (W_HEAD_NOTIFY_BP.Succeeded() && _ui_headup)
	//{
	//	_ui_headup->SetWidgetClass(W_HEAD_NOTIFY_BP.Class);
	//}
}
void AHD_Monster::MOBPostInit(FDataMonster* s_data_enemy)
{
	if (!s_data_enemy) return;

	_ui_monster_headup = Cast<UHD_UI_HeadUp_Monster>(_ui_headup->GetUserWidgetObject());
	_anim_instance_monster = Cast<UHD_AM_Monster>(_skeletal_mesh->GetAnimInstance());
	_info_monster.is_boss = s_data_enemy->GetIsBoss();

	_info_monster.code_proj = s_data_enemy->GetCodePROJ();
	_info_monster.hp_max = s_data_enemy->GetHP();
	_info_monster.str_base = s_data_enemy->GetSTR();
	_info_monster.as_base = s_data_enemy->GetAS();
	_info_monster.move_speed = s_data_enemy->GetMoveSpeed();
	_info_monster.death_to_pool_tick_max = 240;
	_info_monster.anim_attack_basic = s_data_enemy->GetAnimAttackBasic();
}
void AHD_Monster::MOBInit(const int64 i_id, const FVector v_loc_spawn)
{
	UnitSetActiveTick(true);
	_info_monster.gid = i_id;
	_info_monster.hp = _info_monster.hp_max;
	_info_monster.death_to_pool_tick = 0;
	_info_monster.is_death = false;
	_info_unit.is_hit_valid = true;

	SetActorLocation(v_loc_spawn);

	_anim_instance_monster->AMSetIsDeath(false);

	if (_info_monster.is_boss)
	{
		_ui_monster_headup->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		_ui_monster_headup->SetVisibility(ESlateVisibility::Visible);
		_ui_monster_headup->UIEnemyHeadUpInit(this);
	}
}
void AHD_Monster::MOBToHomeInit()
{
	_anim_instance_monster->StopAllMontages(-1.f);
}
void AHD_Monster::UnitSetActiveTickChild(const bool b_is_active)
{

}

void AHD_Monster::MOBMove(const float f_delta_time, const FVector& v_loc_move, const FRotator& r_rot)
{
	_info_monster.lane_dist = _info_monster.lane_dist + ((float)_info_monster.move_speed * f_delta_time);
	SetActorLocation(v_loc_move);
	SetActorRotation(r_rot);
}

void AHD_Monster::MOBUpdateAS(const uint8 i_tick_1frame)
{
	switch (_info_monster.atk_basic_status)
	{
	case EAttackBasicStatus::DETECT:
		break;
	case EAttackBasicStatus::TRY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		break;
	case EAttackBasicStatus::DELAY:
		UnitSetStat(EUnitStatType::AS_DEALY, EUnitStatBy::NO, i_tick_1frame);
		if (UnitGetStat(EUnitStatType::AS_DEALY) >= _info_monster.GetASTotalDelay())
		{
			_info_monster.atk_basic_status = EAttackBasicStatus::DETECT;
		}
		break;
	default:
		break;
	}
}

void AHD_Monster::MOBAttackBasicStart(AHD_Hero* target)
{
	//???? ????????????????????
	if (_info_monster.atk_basic_status == EAttackBasicStatus::TRY) return;

	_info_monster.atk_basic_status = EAttackBasicStatus::TRY;
	_info_monster.target = target;
	_info_monster.as_delay = 0;
	SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_monster.target->GetActorLocation()), 0.f));
	--_info_monster.is_can_move;
	_anim_instance_monster->Montage_Play(_info_monster.anim_attack_basic);
}
void AHD_Monster::MOBAttackBasicNotify()
{
	if (!_info_monster.target || !_info_monster.target->GetInfoUnit().is_hit_valid)
	{
		_info_monster.atk_basic_status = EAttackBasicStatus::DETECT;
	}
	else
	{
		MOBAttackBasic();
		_info_monster.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}
void AHD_Monster::MOBAttackBasic()
{
	//override
	_gm->PROJSpawn(_info_monster.code_proj, GetActorLocation(), this, _info_monster.target, _info_monster.target->GetActorLocation2D());
}
void AHD_Monster::UnitDoAttackBasic(AHD_Unit* unit_target)
{
	_gm->BattleSend(this, unit_target, _info_monster.GetAttackBasicDMG(), EAttackType::BASIC);
}

void AHD_Monster::MOBMontageEnded()
{
	++_info_monster.is_can_move;
}

void AHD_Monster::UnitDeath()
{
	_ui_monster_headup->SetVisibility(ESlateVisibility::Hidden);
	_info_monster.is_death = true;
	_info_unit.is_hit_valid = false;

	_anim_instance_monster->StopAllMontages(-1.f);
	_anim_instance_monster->AMSetIsDeath(true);

	_gm->MOBDeath(this);
}
bool AHD_Monster::MOBUpdateDeathToPool()
{
	++_info_monster.death_to_pool_tick;
	if (_info_monster.death_to_pool_tick >= _info_monster.death_to_pool_tick_max)
	{
		return true;
	}
	else
		return false;
}

void AHD_Monster::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		UnitSetHP(_info_monster.hp, _info_monster.hp_max, i_value);
		if (_info_monster.is_boss)
			_pc->PCUIUpdateBossHPRate(_info_monster.GetHPRate());
		else
			_ui_monster_headup->UIEnemyHeadUpSetHPBar(_info_monster.GetHPRate());
		break;
	case EUnitStatType::DMG:
		switch (e_stat_by)
		{
		case EUnitStatBy::BUFF:
			UnitSetDMG(_info_monster.dmg_base_by_bf, i_value);
			break;
		default:
			break;
		}
		break;
	case EUnitStatType::AS_DEALY:
		UnitSetAS(_info_monster.as_delay, _info_monster.GetASTotalDelay(), i_value);
		break;
	default:
		break;
	}
}
const int32 AHD_Monster::UnitGetStat(const EUnitStatType e_stat_type)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		return _info_monster.hp;
		break;
	case EUnitStatType::DMG:
		return _info_monster.dmg_base;
		break;
	case EUnitStatType::AS_DEALY:
		return _info_monster.as_delay;
		break;
	default:
		break;
	}

	return int32();
}

const FInfoMonster& AHD_Monster::GetInfoMOB() { return _info_monster; }
