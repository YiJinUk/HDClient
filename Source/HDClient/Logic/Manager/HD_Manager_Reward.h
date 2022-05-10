// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Reward.generated.h"

class UHD_GI;
class AHD_GM;
class AHD_Manager_Pool;
class AHD_Reward;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_Reward : public AHD_Manager_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void RewardPostInit(UHD_GI* gi, AHD_GM* gm, AHD_Manager_Pool* manager_pool);

	FInfoReward* RewardFindByType(const ERewardType e_reward_type);
private:
	FInfoReward* PoolOutInfoReward();
	void PoolInInfoReward(FInfoReward* s_info_reward);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		AHD_Manager_Pool* _manager_pool = nullptr;

	//모든 보상종류 캐싱
	TMap<ERewardType, FInfoReward> _info_reward_all;

	//선택보상의 확률을 미리 저장한 배열입니다
	UPROPERTY()
		TArray<ERewardType> _rewards_select_rate;

	UPROPERTY()
		TArray<FInfoReward> _reward_pool_origin;
	TArray<FInfoReward*> _reward_pool_pointer;
#pragma endregion

public:
	//세계에 진입하면 호출합니다
	void RewardInit();
	//다음 웨이브로 진입할 때 호출됩니다
	void RewardWaveNext();
	void RewardWaveEnd();

	void RewardGetSelect(const ERewardType e_reward_type, const ERewardBy e_reward_by);

	const TSet<FInfoReward*>& GetRewardsRandom();
	const TArray<FInfoReward*>& GetRewardsBase();
private:
	void RewardCalcTypes(TSet<FInfoReward*>& arr_reward);

private:
	TSet<FInfoReward*> _rewards_random;
	TArray<FInfoReward*> _rewards_base;
};
