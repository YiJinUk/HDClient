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

	/*����������ü �ʱ�ȭ*/
	BattleInitDMGInfo(s_dmg_info, atk, def, i_dmg, e_atk_type);
	BattleInitDMGResult(s_dmg_rlt, s_dmg_info);

	/*S. ���ط��� ����ϱ� ���� ��� ������ �����մϴ�*/

	//@���������� �����մϴ�

	//�������� �����մϴ�
	BattleGetDMG(s_dmg_info, s_dmg_rlt);
	//�������� �����մϴ�
	BattleGetArmor(s_dmg_info, s_dmg_rlt);

	/*E.*/

	/*S. ������������ ����մϴ�*/

	//@������������ ġ��ŸȮ���� ����մϴ�

	//������������ �������� ����մϴ�
	BattleCalcArmor(s_dmg_info, s_dmg_rlt);

	//������������ ������������ ����մϴ�
	BattleCalcDamage(s_dmg_info, s_dmg_rlt);

	/*E.*/


	/*���� ������������ ���� ���ظ� �ݴϴ�*/
	BattleAppleDamage(s_dmg_rlt);

	/*���� ������ ����ü Ǯ��*/
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

	//���׹����� ���� �ּ����ط��� 1
	if (s_dmg_rlt->dmg_sum <= 0)
		s_dmg_rlt->dmg_sum = 1;

	if (s_dmg_rlt->dmg_sum <= s_dmg_rlt->def_armor_rlt)
	{
		/*���ط����� ���� �� ���� ������ ���� ����մϴ�*/
		s_dmg_rlt->dmg_armor_rlt = s_dmg_rlt->dmg_sum;
		s_dmg_rlt->dmg_hp_rlt = 0;
	}
	else
	{
		/*���ط����� ���� ���� ������ ��,ü�� �Ѵ� ���ط��� ����մϴ�. ���� 0�� �� �ֽ��ϴ�*/
		s_dmg_rlt->dmg_armor_rlt = s_dmg_rlt->def_armor_rlt;
		s_dmg_rlt->dmg_hp_rlt = s_dmg_rlt->dmg_sum - s_dmg_rlt->def_armor_rlt;
	}
}

void AHD_Manager_Battle::BattleAppleDamage(FDamageResult* s_dmg_rlt)
{
	/*���� ü���� ����ϴ�*/
	if (s_dmg_rlt->dmg_armor_rlt >= 1)
	{
		s_dmg_rlt->def->UnitSetStat(EUnitStatType::ARMOR, EUnitStatBy::NO, -s_dmg_rlt->dmg_armor_rlt);
	}
	if (s_dmg_rlt->dmg_hp_rlt >= 1)
	{
		s_dmg_rlt->def->UnitSetStat(EUnitStatType::HP, EUnitStatBy::NO, -s_dmg_rlt->dmg_hp_rlt);
	}

	/*����ڿ��� �ǰݵǾ��ٰ� �˸��ϴ�*/
	_battle_hit_result.InitBattleHitResult();
	_battle_hit_result.is_broken_armor = (s_dmg_rlt->dmg_armor_rlt >= 1)&&(s_dmg_rlt->dmg_armor_rlt >= s_dmg_rlt->def_armor_rlt);
	s_dmg_rlt->def->UnitHit(_battle_hit_result);

	if (s_dmg_rlt->def->UnitGetStat(EUnitStatType::HP) <= 0)
	{
		/*����ڰ� �׾����ϴ�*/
		s_dmg_rlt->def->UnitDeath();
	}
}