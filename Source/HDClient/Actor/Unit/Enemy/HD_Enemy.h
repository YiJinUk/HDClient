// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/HD_Unit.h"
#include "HD_Enemy.generated.h"

class UHD_UI_Enemy_HeadUp;
class UHD_AM_Enemy;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Enemy : public AHD_Unit
{
	GENERATED_BODY()
	
#pragma region Init
public:
	AHD_Enemy(FObjectInitializer const& object_initializer);
	void EnemyPostInit(FDataEnemy* s_data_enemy);
	void EnemyInit(const int64 i_id, const FVector v_loc_spawn);
	void EnemyToHomeInit();

	const FInfoEnemy& GetInfoEnemy();
private:
	void UnitSetActiveTickChild(const bool b_is_active) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* _ui_headup = nullptr;
	UPROPERTY()
		UHD_UI_Enemy_HeadUp* _ui_enemy_headup = nullptr;
	UPROPERTY()
		UHD_AM_Enemy* _anim_instance_enemy = nullptr;

	UPROPERTY()
		FInfoEnemy _info_enemy;
#pragma endregion

#pragma region Move
public:
	void EnemyMove(const float f_delta_time, const FVector& v_loc_move, const FRotator& r_rot);
#pragma endregion

#pragma region Attack.Basic
public:
	bool EnemyUpdateAS(const uint8 i_tick_1frame);
	//기본공격을 시작합니다
	void EnemyAttackBasicStart(AHD_Hero* target);
	//기본공격애니메이션중 공격피해를 시도합니다
	void EnemyAttackBasicNotify();
	void UnitDoAttackBasic(AHD_Unit* unit_target) override;
	

protected:
	virtual void EnemyAttackBasic();
#pragma endregion

#pragma region Animation
public:
	void EnemyMontageEnd();
#pragma endregion

#pragma region Death
public:
	void UnitDeath() override;
	bool EnemyUpdateDeathToPool();
#pragma endregion

#pragma region Stat
private:
	void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) override;
	const int32 UnitGetStat(const EUnitStatType e_stat_type) override;
#pragma endregion

};
