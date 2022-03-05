// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/HD_Friend.h"
#include "HD_Hero.generated.h"

class AHD_Weapon;
class AHD_Monster;
class AHD_Unit;
class AHD_PC;
class UHD_GI;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Hero : public AHD_Friend
{
	GENERATED_BODY()

#pragma region Init
public:
	void HeroPostInit(AHD_PC* pc, FDataHero* s_data_hero);
	void HeroInit(FDataHero* s_data_hero);
	void HeroWaveEndInit();
	void HeroToHomeInit();

	const FInfoHero& GetInfoHero();
private:
	UPROPERTY()
		FInfoHero _info_hero;
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_PC* _pc = nullptr;
#pragma endregion

#pragma region Weapon
public:
	void HeroChangeWeapon(AHD_Weapon* wp_change);
#pragma endregion

#pragma region Armor
public:
	void HeroUpdateHealArmor(const uint8 i_tick_1frame);
#pragma endregion

#pragma region Attack.Basic
public:
	void HeroUpdateAS(const uint8 i_tick_1frame);

	//기본공격을 시작합니다
	void HeroAttackBasicStart(AHD_Monster* target);
	//기본공격애니메이션중 공격피해를 시도합니다
	void HeroAttackBasicNotify();
	void UnitDoAttackBasic(AHD_Unit* unit_target) override;
#pragma endregion

#pragma region Attack.Skill
public:
	void HeroUpdateReduceCooldown(const uint8 i_tick_1frame);
	void HeroAttackSkillStart();
	void HeroAttackSKNotify();
	void UnitDoAttackSK(AHD_Unit* unit_target) override;
#pragma endregion

#pragma region Death
private:
	void UnitHit(const FBattleHitResult& s_battle_hit_result) override;
	void UnitDeath() override;
#pragma endregion

#pragma region Stat
private:
	void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) override;
	const int32 UnitGetStat(const EUnitStatType e_stat_type) override;
#pragma endregion

};
