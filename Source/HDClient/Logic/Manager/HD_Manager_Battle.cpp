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

	BattleInitDMGInfo(s_dmg_info, atk, def, i_dmg, e_atk_type);
	BattleInitDMGResult(s_dmg_rlt, s_dmg_info);

	/*S. 피해량을 계산하기 위해 모든 정보를 수집합니다*/

	BattleCalcDamage(s_dmg_info, s_dmg_rlt);

	/*E. 피해량을 계산하기 위해 모든 정보를 수집합니다*/

	BattleAppleDamage(s_dmg_rlt);

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

void AHD_Manager_Battle::BattleCalcDamage(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt)
{
	s_dmg_rlt->dmg_rlt = s_dmg_info->dmg_origin;

	//버그방지를 위해 최소 피해량은 1입니다
	if (s_dmg_rlt->dmg_rlt <= 0)
		s_dmg_rlt->dmg_rlt = 1;
}

void AHD_Manager_Battle::BattleAppleDamage(FDamageResult* s_dmg_rlt)
{
	/*계산된 피해값으로 실제 피해를 줍니다*/
	s_dmg_rlt->def->UnitSetStat(EUnitStatType::HP, EUnitStatBy::NO, -s_dmg_rlt->dmg_rlt);

	if (s_dmg_rlt->def->UnitGetStat(EUnitStatType::HP) <= 0)
	{
		/*방어자가 죽었습니다*/
		s_dmg_rlt->def->UnitDeath();
	}
}