// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/HD_Unit.h"
#include "HD_Monster.generated.h"

class UHD_UI_HeadUp_Monster;
class UHD_AM_Monster;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Monster : public AHD_Unit
{
	GENERATED_BODY()
	
#pragma region Init
public:
	AHD_Monster(FObjectInitializer const& object_initializer);
	void MOBPostInit(FDataMonster* s_data_enemy);
	void MOBInit(const int64 i_id, const FVector v_loc_spawn);
	void MOBToHomeInit();

	const FInfoMonster& GetInfoMOB();
private:
	void UnitSetActiveTickChild(const bool b_is_active) override;
protected:
	UPROPERTY()
		UHD_UI_HeadUp_Monster* _ui_monster_headup = nullptr;
	UPROPERTY()
		UHD_AM_Monster* _anim_instance_monster = nullptr;

	UPROPERTY()
		FInfoMonster _info_monster;
#pragma endregion

#pragma region Move
public:
	void MOBMove(const float f_delta_time, const FVector& v_loc_move, const FRotator& r_rot);
#pragma endregion

#pragma region Attack.Basic
public:
	void MOBUpdateAS(const uint8 i_tick_1frame);
	//기본공격을 시작합니다
	void MOBAttackBasicStart(AHD_Hero* target);
	//기본공격애니메이션중 공격피해를 시도합니다
	void MOBAttackBasicNotify();
	void UnitDoAttackBasic(AHD_Unit* unit_target) override;
	

protected:
	virtual void MOBAttackBasic();
#pragma endregion

#pragma region Animation
public:
	void MOBMontageEnded();
#pragma endregion

#pragma region Death
public:
	void UnitDeath() override;
	bool MOBUpdateDeathToPool();
#pragma endregion

#pragma region Stat
private:
	void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) override;
	const int32 UnitGetStat(const EUnitStatType e_stat_type) override;
#pragma endregion

};
