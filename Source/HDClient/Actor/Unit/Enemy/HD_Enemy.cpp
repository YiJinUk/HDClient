// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Enemy/HD_Enemy.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/Animation/HD_AM_Enemy.h"
#include "Logic/HD_GM.h"
#include "UI/World/Enemy/HD_UI_Enemy_HeadUp.h"

#include "Components/WidgetComponent.h"

AHD_Enemy::AHD_Enemy(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = false;

	_ui_headup = object_initializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("_ui_headup"));
	if (_ui_headup)
	{
		_ui_headup->SetupAttachment(GetRootComponent());
		_ui_headup->SetGenerateOverlapEvents(false);
		_ui_headup->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_ui_headup->CanCharacterStepUpOn = ECB_No;
		_ui_headup->SetWidgetSpace(EWidgetSpace::Screen);
		_ui_headup->SetDrawAtDesiredSize(true);

		static ConstructorHelpers::FClassFinder<UUserWidget> W_HEAD_NOTIFY_BP(TEXT("/Game/_HDClient/UI/World/Enemy/HDWB_UI_Enemy_HeadUp"));
		if (W_HEAD_NOTIFY_BP.Succeeded())
		{
			if (_ui_headup)
			{
				_ui_headup->SetWidgetClass(W_HEAD_NOTIFY_BP.Class);
			}
		}
	}
}
void AHD_Enemy::EnemyPostInit(FDataEnemy* s_data_enemy)
{
	if (!s_data_enemy) return;

	_ui_enemy_headup = Cast<UHD_UI_Enemy_HeadUp>(_ui_headup->GetUserWidgetObject());
	_anim_instance_enemy = Cast<UHD_AM_Enemy>(_skeletal_mesh->GetAnimInstance());

	_info_enemy.code_proj = s_data_enemy->GetCodePROJ();
	_info_enemy.hp_max = s_data_enemy->GetHP();
	_info_enemy.str_base = s_data_enemy->GetSTR();
	_info_enemy.as_base = s_data_enemy->GetAS();
	_info_enemy.move_speed = s_data_enemy->GetMoveSpeed();
	_info_enemy.death_to_pool_tick_max = 240;
	_info_enemy.anim_attack_basic = s_data_enemy->GetAnimAttackBasic();
}
void AHD_Enemy::EnemyInit(const int64 i_id, const FVector v_loc_spawn)
{
	UnitSetActiveTick(true);
	_info_enemy.id = i_id;
	_info_enemy.hp = _info_enemy.hp_max;
	_info_enemy.death_to_pool_tick = 0;
	_info_enemy.is_death = false;
	_info_unit.is_hit_valid = true;

	SetActorLocation(v_loc_spawn);

	_anim_instance_enemy->AMSetIsDeath(false);

	_ui_enemy_headup->SetVisibility(ESlateVisibility::Visible);
	_ui_enemy_headup->UIEnemyHeadUpInit(this);
}
void AHD_Enemy::EnemyToHomeInit()
{
	_anim_instance_enemy->StopAllMontages(-1.f);
}
void AHD_Enemy::UnitSetActiveTickChild(const bool b_is_active)
{

}

void AHD_Enemy::EnemyMove(const float f_delta_time, const FVector& v_loc_move, const FRotator& r_rot)
{
	_info_enemy.lane_dist = _info_enemy.lane_dist + ((float)_info_enemy.move_speed * f_delta_time);
	SetActorLocation(v_loc_move);
	SetActorRotation(r_rot);
}

bool AHD_Enemy::EnemyUpdateAS(const uint8 i_tick_1frame)
{
	return UnitUpdateAS(_info_enemy.atk_basic_status, _info_enemy.as_delay, _info_enemy.GetASTotalDelay(), i_tick_1frame);
}

void AHD_Enemy::EnemyAttackBasicStart(AHD_Hero* target)
{
	//이미 기본공격시도중입니다
	if (_info_enemy.atk_basic_status == EAttackBasicStatus::TRY) return;

	_info_enemy.atk_basic_status = EAttackBasicStatus::TRY;
	_info_enemy.target = target;
	_info_enemy.as_delay = 0;
	SetActorRotation(FRotator(0.f, UHD_FunctionLibrary::GetFindLookRotatorYawByV3(GetActorLocation(), _info_enemy.target->GetActorLocation()), 0.f));
	--_info_enemy.is_can_move;
	_anim_instance_enemy->Montage_Play(_info_enemy.anim_attack_basic);
}
void AHD_Enemy::EnemyAttackBasicNotify()
{
	if (!_info_enemy.target || !_info_enemy.target->GetInfoUnit().is_hit_valid)
	{
		_info_enemy.atk_basic_status = EAttackBasicStatus::DETECT;
	}
	else
	{
		EnemyAttackBasic();
		_info_enemy.atk_basic_status = EAttackBasicStatus::DELAY;
	}
}
void AHD_Enemy::EnemyAttackBasic()
{
	//override
}
void AHD_Enemy::UnitDoAttackBasic(AHD_Unit* unit_target)
{
	_gm->BattleSend(this, unit_target, _info_enemy.GetAttackBasicDMG(), EAttackType::BASIC);
}

void AHD_Enemy::EnemyMontageEnd()
{
	++_info_enemy.is_can_move;
}

void AHD_Enemy::UnitDeath()
{
	_ui_enemy_headup->SetVisibility(ESlateVisibility::Hidden);
	_info_enemy.is_death = true;
	_info_unit.is_hit_valid = false;

	_anim_instance_enemy->StopAllMontages(-1.f);
	_anim_instance_enemy->AMSetIsDeath(true);

	_gm->EnemyDeath(this);
}
bool AHD_Enemy::EnemyUpdateDeathToPool()
{
	++_info_enemy.death_to_pool_tick;
	if (_info_enemy.death_to_pool_tick >= _info_enemy.death_to_pool_tick_max)
	{
		return true;
	}
	else
		return false;
}

void AHD_Enemy::UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		_info_enemy.hp += i_value;
		if (_info_enemy.hp <= 0)
		{
			_info_enemy.hp = 0;
		}
		else if(_info_enemy.hp > _info_enemy.hp_max)
		{
			_info_enemy.hp = _info_enemy.hp_max;
		}

		_ui_enemy_headup->UIEnemyHeadUpSetHPBar(_info_enemy.GetHPRate());
		break;
	default:
		break;
	}
}
const int32 AHD_Enemy::UnitGetStat(const EUnitStatType e_stat_type)
{
	switch (e_stat_type)
	{
	case EUnitStatType::HP:
		return _info_enemy.hp;
		break;
	default:
		break;
	}

	return int32();
}

const FInfoEnemy& AHD_Enemy::GetInfoEnemy() { return _info_enemy; }