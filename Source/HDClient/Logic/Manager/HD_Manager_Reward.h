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
	const TArray<FInfoReward*>& GetInfoRewardsBase();
	const FInfoReward* GetInfoRewardSelect();
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		AHD_Manager_Pool* _manager_pool = nullptr;

	TMap<ERewardType, FInfoReward> _info_reward_all;

	TArray<FInfoReward*> _info_rewards_base;
	//�־��� �⺻������ ����. �ش� ��������ŭ �⺻�����ư�� ������ ������ ���ú����� �޴� UI�� �Ѿ�ϴ�
	int8 _count_reward_base = 0;

	FInfoReward* _info_reward_select = nullptr;
	AHD_Reward* _reward_select = nullptr;
#pragma endregion

public:
	void RewardInit();
	void RewardWaveEnd();


	void RewardSelectStart(const ERewardType e_reward_type, const ERewardBy e_reward_by);
};
