// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Buff.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GI.h"
#include "Logic/HD_GM.h"
#include "Actor/Unit/HD_Unit.h"

void AHD_Manager_Buff::BFPostInit(AHD_GM* gm, UHD_GI* gi)
{
	_gm = gm;
	_gi = gi;

	int32 i_index = 0;
	for (int32 i = 0; i < 30; ++i)
	{
		FInfoBuff s_info_bf;
		i_index = _pool_bf_origin.Add(s_info_bf);
		_pool_bf.Add(&_pool_bf_origin[i_index]);
	}
}

void AHD_Manager_Buff::BFCastStart(const FString& str_code_bf, AHD_Unit* caster, AHD_Unit* casted,
	const EBuffPhase e_bf_phase, const EBuffTimer e_bf_timer, const int32 i_life, const EBuffOverlap e_bf_overlap, const FString& str_unique,
	const int32 i_value_1, const int32 i_value_2, const int32 i_value_3)
{
	FInfoBuff* s_info_bf_new = GetInfoBF();
	if (BFCanOverlap(casted, e_bf_overlap, str_unique))
	{
		BFInit(s_info_bf_new, str_code_bf, caster, casted, e_bf_phase, e_bf_timer, i_life, e_bf_overlap, str_unique, i_value_1, i_value_2, i_value_3);
		if(s_info_bf_new->bf_phase == EBuffPhase::IMMEDIATELY)
			BFCasting(s_info_bf_new);

		s_info_bf_new->caster->UnitAddBF(s_info_bf_new->gid);
		_active_bfs.Add(s_info_bf_new->gid, s_info_bf_new);
	}
	else
	{

	}
}
bool AHD_Manager_Buff::BFCanOverlap(AHD_Unit* casted, const EBuffOverlap e_bf_overlap, const FString& str_unique)
{
	return true;
}
void AHD_Manager_Buff::BFInit(FInfoBuff* s_info_bf_new, const FString& str_code_bf, AHD_Unit* caster, AHD_Unit* casted,
	const EBuffPhase e_bf_phase, const EBuffTimer e_bf_timer, const int32 i_life, const EBuffOverlap e_bf_overlap, const FString& str_unique,
	const int32 i_value_1, const int32 i_value_2, const int32 i_value_3)
{
	FDataBuff* s_data_bf = _gi->FindDataBFByCode(str_code_bf);
	s_info_bf_new->id = s_data_bf->GetID();

	s_info_bf_new->gid = _gm->GidGenerate();
	s_info_bf_new->caster = caster;
	s_info_bf_new->casted = casted;
	s_info_bf_new->bf_phase = e_bf_phase;
	s_info_bf_new->bf_timer = e_bf_timer;
	s_info_bf_new->life = i_life;
	s_info_bf_new->bf_overlap = e_bf_overlap;
	s_info_bf_new->unique = str_unique;
	s_info_bf_new->value_1 = i_value_1;
	s_info_bf_new->value_2 = i_value_2;
	s_info_bf_new->value_3 = i_value_3;
}

void AHD_Manager_Buff::BFEnd(FInfoBuff* s_info_bf)
{
	BFFinish(s_info_bf);
	s_info_bf->casted->UnitRemoveBF(s_info_bf->gid);
	_active_bfs.Remove(s_info_bf->gid);
	AddInfoBF(s_info_bf);
}

void AHD_Manager_Buff::BFTick()
{
	FInfoBuff* s_info_bf = nullptr;
	for (auto it = _active_bfs.CreateConstIterator(); it; ++it)
	{
		s_info_bf = it.Value();
		switch (s_info_bf->bf_timer)
		{
		case EBuffTimer::TIMER:
			--s_info_bf->life;
			break;
		default:
			break;
		}

		if (s_info_bf->life <= 0)
		{
			/*버프 종료*/
			BFEnd(s_info_bf);
		}
	}
}

void AHD_Manager_Buff::BFCasting(FInfoBuff* s_info_bf)
{
	switch (s_info_bf->id)
	{
	case 1:
	{
		/*
		* 공격력증가
		* EBuffPhase::IMMEDIATELY
		* value_1 : 증가되야할 공격력
		*/

		s_info_bf->casted->UnitSetStat(EUnitStatType::DMG, EUnitStatBy::BUFF, s_info_bf->value_1);

	}
	break;
	default:
		break;
	}
}
void AHD_Manager_Buff::BFFinish(FInfoBuff* s_info_bf)
{
	switch (s_info_bf->id)
	{
	case 1:
	{
		s_info_bf->casted->UnitSetStat(EUnitStatType::DMG, EUnitStatBy::BUFF, -s_info_bf->value_1);
	}
	break;
	default:
		break;
	}
}

FInfoBuff* AHD_Manager_Buff::GetInfoBF()
{
	if (_pool_bf.Num() <= 0)
	{
		FInfoBuff s_info_bf;
		int32 i_index = _pool_bf_origin.Add(s_info_bf);
		return &_pool_bf_origin[i_index];
	}
	else
	{
		return _pool_bf.Pop();
	}
}
void AHD_Manager_Buff::AddInfoBF(FInfoBuff* s_info_bf) { _pool_bf.Add(s_info_bf); }