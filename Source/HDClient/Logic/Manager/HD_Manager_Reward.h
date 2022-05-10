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

	//��� �������� ĳ��
	TMap<ERewardType, FInfoReward> _info_reward_all;

	//���ú����� Ȯ���� �̸� ������ �迭�Դϴ�
	UPROPERTY()
		TArray<ERewardType> _rewards_select_rate;

	UPROPERTY()
		TArray<FInfoReward> _reward_pool_origin;
	TArray<FInfoReward*> _reward_pool_pointer;
#pragma endregion

public:
	//���迡 �����ϸ� ȣ���մϴ�
	void RewardInit();
	//���� ���̺�� ������ �� ȣ��˴ϴ�
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
