// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Engine/GameInstance.h"
#include "HD_GI.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_GI : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	UHD_GI();
public:
	void GIPostInit();
#pragma endregion

#pragma region Data
public:
	FDataMonster* FindDataMOBByCode(const FString& str_code_mob);
	FDataCPAN* FindDataCPANByCode(const FString& str_code_cpan);
	FDataProjectile* FindDataPROJByCode(const FString& str_code_proj);
	FDataVFX* FindDataVFXByCode(const FString& str_code_vfx);
	FDataSkill* FindDataSKByCode(const FString& str_code_sk);
	FDataBuff* FindDataBFByCode(const FString& str_code_bf);
	FDataReward* FindDataRewardByType(const ERewardType e_reward_type);
	FDataSPEC* FindDataSPECByCode(const FString& str_code_spec);

	const TArray<FDataWeapon*>& GetDataWeapons();
	const TArray<FDataCPAN*>& GetDataCPANs();
	const TArray<FDataWave*>& GetDataWaves();
	const TMap<ERewardType, FDataReward*>& GetDataRewards();
	const TArray<FDataSPEC*>& GetDataSPECs();
	FDataGame* GetDataGame();
	FDataHero* GetDataHero();
	FDataMS* GetDataMS();
private:
	UDataTable* _dt_game = nullptr;
	UDataTable* _dt_wave = nullptr;
	UDataTable* _dt_hero = nullptr;
	UDataTable* _dt_cpan = nullptr;
	UDataTable* _dt_ms = nullptr;
	UDataTable* _dt_mob = nullptr;
	UDataTable* _dt_weapon = nullptr;
	UDataTable* _dt_proj = nullptr;
	UDataTable* _dt_vfx = nullptr;
	UDataTable* _dt_sk = nullptr;
	UDataTable* _dt_bf = nullptr;
	UDataTable* _dt_reward = nullptr;
	UDataTable* _dt_spec = nullptr;

	TArray<FDataWeapon*> _data_wps;
	TArray<FDataCPAN*> _data_cpans;
	TArray<FDataWave*> _data_waves;
	TArray<FDataSPEC*> _data_specs;
	TMap<ERewardType, FDataReward*> _data_rewards;
	FDataGame* _data_game = nullptr;
	FDataHero* _data_hero = nullptr;
	FDataMS* _data_ms = nullptr;
#pragma endregion

#pragma region General
public:
	//min~max사이의 난수를 구합니다
	int32 GetRandomByInt(const int32 i_min = 1, const int32 i_max = 100);
#pragma endregion
};