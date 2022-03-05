// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Battle.h"
#include "Actor/Unit/HD_Unit.h"

void AHD_Manager_Battle::BattlePostInit()
{
	int32 i_index = 0;
	for (int32 i = 0; i < 30; ++i)
	{
		FDamageInfo s_dmg_info;
		i_index = _pool_dmg_info_origin.Add(s_dmg_info);
		_pool_dmg_info_pointer.Add(&_pool_dmg_info_origin[i_index]);

		FDamageResult s_dmg_rlt;
		i_index = _pool_dmg_rlt_origin.Add(s_dmg_rlt);
		_pool_dmg_rlt_pointer.Add(&_pool_dmg_rlt_origin[i_index]);
	}
}
FDamageInfo* AHD_Manager_Battle::PoolOutDMGInfo()
{
	if (_pool_dmg_info_pointer.Num() <= 0)
	{
		FDamageInfo s_dmg_info;
		int32 i_index = _pool_dmg_info_origin.Add(s_dmg_info);
		return &_pool_dmg_info_origin[i_index];
	}
	else
	{
		return _pool_dmg_info_pointer.Pop();
	}
}
void AHD_Manager_Battle::PoolInDMGInfo(FDamageInfo* s_dmg_info)
{
	if (!s_dmg_info) return;
	s_dmg_info->InitDamageInfo();
	_pool_dmg_info_pointer.Add(s_dmg_info);
}
FDamageResult* AHD_Manager_Battle::PoolOutDMGResult()
{
	if (_pool_dmg_rlt_pointer.Num() <= 0)
	{
		FDamageResult s_dmg_rlt;
		int32 i_index = _pool_dmg_rlt_origin.Add(s_dmg_rlt);
		return &_pool_dmg_rlt_origin[i_index];
	}
	else
	{
		return _pool_dmg_rlt_pointer.Pop();
	}
}
void AHD_Manager_Battle::PoolInDMGResult(FDamageResult* s_dmg_rlt)
{
	if (!s_dmg_rlt) return;
	s_dmg_rlt->InitDamageResult();
	_pool_dmg_rlt_pointer.Add(s_dmg_rlt);
}

void AHD_Manager_Battle::BattleRecv(AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type)
{
	FDamageInfo* s_dmg_info = PoolOutDMGInfo();
	FDamageResult* s_dmg_rlt = PoolOutDMGResult();

	/*데미지구조체 초기화*/
	BattleInitDMGInfo(s_dmg_info, atk, def, i_dmg, e_atk_type);
	BattleInitDMGResult(s_dmg_rlt, s_dmg_info);

	/*S. 피해량을 계산하기 위해 모든 정보를 수집합니다*/

	//@버프정보를 수집합니다

	//데미지를 수집합니다
	BattleGetDMG(s_dmg_info, s_dmg_rlt);
	//방어도정보를 수집합니다
	BattleGetArmor(s_dmg_info, s_dmg_rlt);

	/*E.*/

	/*S. 수집된정보로 계산합니다*/

	//@수집된정보로 치명타확률을 계산합니다

	//수집된정보로 최종방어도를 계산합니다
	BattleCalcArmor(s_dmg_info, s_dmg_rlt);

	//수집된정보로 최종데미지를 계산합니다
	BattleCalcDamage(s_dmg_info, s_dmg_rlt);

	/*E.*/


	/*계산된 데미지값으로 실제 피해를 줍니다*/
	BattleAppleDamage(s_dmg_rlt);

	/*사용된 데미지 구조체 풀링*/
	PoolInDMGInfo(s_dmg_info);
	PoolInDMGResult(s_dmg_rlt);
}
void AHD_Manager_Battle::BattleInitDMGInfo(FDamageInfo* s_dmg_info, AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type)
{
	s_dmg_info->atk = atk;
	s_dmg_info->def = def;
	s_dmg_info->dmg_origin = i_dmg;
	s_dmg_info->atk_type = e_atk_type;
}
void AHD_Manager_Battle::BattleInitDMGResult(FDamageResult* s_dmg_rlt, FDamageInfo* s_dmg_info)
{
	s_dmg_rlt->atk = s_dmg_info->atk;
	s_dmg_rlt->def = s_dmg_info->def;
}

void AHD_Manager_Battle::BattleGetDMG(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt)
{
	s_dmg_rlt->dmg_base = s_dmg_info->dmg_origin;
}
void AHD_Manager_Battle::BattleGetArmor(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt)
{
	s_dmg_rlt->atk_armor_base = s_dmg_info->atk->UnitGetStat(EUnitStatType::ARMOR);
	s_dmg_rlt->def_armor_base = s_dmg_info->def->UnitGetStat(EUnitStatType::ARMOR);
}

void AHD_Manager_Battle::BattleCalcArmor(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt)
{
	s_dmg_rlt->atk_armor_rlt = s_dmg_rlt->atk_armor_base;
	s_dmg_rlt->def_armor_rlt = s_dmg_rlt->def_armor_base;
}
void AHD_Manager_Battle::BattleCalcDamage(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt)
{
	s_dmg_rlt->dmg_sum = s_dmg_rlt->dmg_base;

	//버그방지를 위해 최소피해량은 1
	if (s_dmg_rlt->dmg_sum <= 0)
		s_dmg_rlt->dmg_sum = 1;

	if (s_dmg_rlt->dmg_sum <= s_dmg_rlt->def_armor_rlt)
	{
		/*피해량보다 방어도가 더 높기 때문에 방어도만 계산합니다*/
		s_dmg_rlt->dmg_armor_rlt = s_dmg_rlt->dmg_sum;
		s_dmg_rlt->dmg_hp_rlt = 0;
	}
	else
	{
		/*피해량보다 방어도가 낮기 때문에 방어도,체력 둘다 피해량을 계산합니다. 방어도는 0일 수 있습니다*/
		s_dmg_rlt->dmg_armor_rlt = s_dmg_rlt->def_armor_rlt;
		s_dmg_rlt->dmg_hp_rlt = s_dmg_rlt->dmg_sum - s_dmg_rlt->def_armor_rlt;
	}
}

void AHD_Manager_Battle::BattleAppleDamage(FDamageResult* s_dmg_rlt)
{
	/*방어도와 체력을 깎습니다*/
	if (s_dmg_rlt->dmg_armor_rlt >= 1)
	{
		s_dmg_rlt->def->UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -s_dmg_rlt->dmg_armor_rlt);
	}
	if (s_dmg_rlt->dmg_hp_rlt >= 1)
	{
		s_dmg_rlt->def->UnitSetStat(EUnitStatType::HP, EUnitStatBy::NO, -s_dmg_rlt->dmg_hp_rlt);
	}

	/*방어자에게 피격되었다고 알립니다*/
	_battle_hit_result.InitBattleHitResult();
	_battle_hit_result.is_broken_armor = (s_dmg_rlt->dmg_armor_rlt >= 1)&&(s_dmg_rlt->dmg_armor_rlt >= s_dmg_rlt->def_armor_rlt);
	s_dmg_rlt->def->UnitHit(_battle_hit_result);

	if (s_dmg_rlt->def->UnitGetStat(EUnitStatType::HP) <= 0)
	{
		/*방어자가 죽었습니다*/
		s_dmg_rlt->def->UnitDeath();
	}
}