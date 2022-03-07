// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/HD_Friend.h"
#include "HD_MagicStone.generated.h"

class UHD_UI_HeadUp_MS;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_MagicStone : public AHD_Friend
{
	GENERATED_BODY()
	
#pragma region Init
public:
	AHD_MagicStone();
	void MSPostInit(FDataMS* s_data_ms);
	void MSInit(FDataMS* s_data_ms);
	//void HeroWaveEndInit();
	//void HeroToHomeInit();

	const FInfoMS& GetInfoMS();
private:
	UPROPERTY()
		UHD_UI_HeadUp_MS* _ui_headup_ms = nullptr;
	UPROPERTY()
		FInfoMS _info_ms;
#pragma endregion

#pragma region Attack.Skill
public:
	void MSUpdateReduceCooldown(const uint8 i_tick_1frame);
	void MSAttackSkillStart();
	//void HeroAttackSKNotify();
	void UnitDoAttackSK(AHD_Unit* unit_target) override;
#pragma endregion

#pragma region Stat
private:
	void UnitSetStat(const EUnitStatType e_stat_type, const EUnitStatBy e_stat_by, const int32 i_value) override;
	const int32 UnitGetStat(const EUnitStatType e_stat_type) override;
#pragma endregion
};
