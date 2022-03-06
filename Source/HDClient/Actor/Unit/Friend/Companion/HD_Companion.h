// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/HD_Friend.h"
#include "HD_Companion.generated.h"

class AHD_Monster;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Companion : public AHD_Friend
{
	GENERATED_BODY()

#pragma region Init
public:
	void CPANPostInit(FDataCPAN* s_data_cpan);
	void CPANInit(const FVector& v_loc_spawn);
	void CPANWaveEndInit();
	const FInfoCPAN& GetInfoCPAN();
private:
	UPROPERTY()
		FInfoCPAN _info_cpan;
#pragma endregion

#pragma region Attack.Basic
public:
	void CPANUpdateAS(const uint8 i_tick_1frame);

	//기본공격을 시작합니다
	void CPANAttackBasicStart(AHD_Monster* target);
	//기본공격애니메이션중 공격피해를 시도합니다
	void CPANAttackBasicNotify();
	void UnitDoAttackBasic(AHD_Unit* unit_target) override;
protected:
	void CPANAttackBasic();
#pragma endregion

#pragma region Attack.Skill
public:
	void CPANUpdateReduceCooldown(const uint8 i_tick_1frame);
	void CPANAttackSkillStart();
	void CPANAttackSKNotify();
	void UnitDoAttackSK(AHD_Unit* unit_target) override;
#pragma endregion

#pragma region Stat
private:
	void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) override;
	const int32 UnitGetStat(const EUnitStatType e_stat_type) override;
#pragma endregion
};
