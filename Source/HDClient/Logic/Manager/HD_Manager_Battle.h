// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Battle.generated.h"

class AHD_Unit;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_Battle : public AHD_Manager_Master
{
	GENERATED_BODY()

#pragma region Init
public:
	void BattlePostInit();

	FDamageInfo* PoolOutDMGInfo();
	void PoolInDMGInfo(FDamageInfo* s_dmg_info);
	FDamageResult* PoolOutDMGResult();
	void PoolInDMGResult(FDamageResult* s_dmg_rlt);
	
private:
	//풀링 제대로 안하면 크래쉬남... 조심

	TArray<FDamageInfo, TInlineAllocator<5>> _pool_dmg_info_origin;
	TArray<FDamageInfo*, TInlineAllocator<5>> _pool_dmg_info_pointer;
	TArray<FDamageResult, TInlineAllocator<5>> _pool_dmg_rlt_origin;
	TArray<FDamageResult*, TInlineAllocator<5>> _pool_dmg_rlt_pointer;

	UPROPERTY()
		FBattleHitResult _battle_hit_result;
#pragma endregion

#pragma region Battle
public:
	void BattleRecv(AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type);
private:
	void BattleInitDMGInfo(FDamageInfo* s_dmg_info, AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type);
	void BattleInitDMGResult(FDamageResult* s_dmg_rlt, FDamageInfo* s_dmg_info);

	void BattleGetDMG(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt);
	void BattleGetArmor(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt);

	void BattleCalcArmor(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt);
	void BattleCalcDamage(FDamageInfo* s_dmg_info, FDamageResult* s_dmg_rlt);

	void BattleAppleDamage(FDamageResult* s_dmg_rlt);

#pragma endregion
};
