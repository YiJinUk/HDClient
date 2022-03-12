// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Reward.h"
#include "HD_Manager_Pool.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GI.h"
#include "Logic/HD_GM.h"
#include "Actor/Object/HD_Reward.h"

#include "Kismet/KismetMathLibrary.h"

void AHD_Manager_Reward::RewardPostInit(UHD_GI* gi, AHD_GM* gm, AHD_Manager_Pool* manager_pool)
{
	_gi = gi;
	_gm = gm;
	_manager_pool = manager_pool;

	/*��� ������ ������ �̸� ĳ���մϴ�*/
	for (const TPair<ERewardType, FDataReward*>& pair : _gi->GetDataRewards())
	{
		//FDataReward* s_data_reward = _gi->FindDataRewardByType(e_reward_type);
		FInfoReward s_info_reward;
		s_info_reward.reward_type = pair.Value->GetRewardType();
		s_info_reward.value = pair.Value->GetValue();
		s_info_reward.icon = pair.Value->GetIcon();

		_info_reward_all.Add(pair.Value->GetRewardType(), s_info_reward);
	}

	/*���ú����� Ȯ���� �̸� ����ؼ� �迭�� �����մϴ�*/
	_rewards_select_rate.Reserve(100);
	for (const FDataRewardSelectActive& s_data_reward_select_active : gi->GetDataGame()->GetRewardsSelectActive())
	{
		for (int32 i = 0; i < s_data_reward_select_active.GetRewardRate(); ++i)
		{
			_rewards_select_rate.Add(s_data_reward_select_active.GetRewardSelectActive());
		}
	}
}

void AHD_Manager_Reward::RewardInit()
{
	const FInfoWave& s_info_wave = _gm->GetInfoWave();
	/*�⺻���� ������ �����ɴϴ�*/
	_info_rewards_base.Empty(2);
	for (const ERewardType e_reward_type : s_info_wave.rewards_base)
	{
		_info_rewards_base.Add(RewardFindByType(e_reward_type));
	}
	_count_reward_base = _info_rewards_base.Num();

	/*���ú��������� �����ɴϴ�. ���ú����� ���ٸ� ��带 �����ɴϴ�*/
	ERewardType e_reward_select = s_info_wave.reward_select;
	if (e_reward_select == ERewardType::NO)
	{
		/*������ ������ �����Ƿ� ��带 �����ɴϴ�*/
		e_reward_select = ERewardType::GOLD;
	}
	_info_reward_select = RewardFindByType(e_reward_select);
}
void AHD_Manager_Reward::RewardWaveEnd()
{
	/*���̺갡 ����Ǿ����ϴ�. ��ٷ� �⺻������ ȹ���մϴ�.*/
	for (const FInfoReward* s_info_reward_base : _info_rewards_base)
	{
		RewardGetSelect(s_info_reward_base->reward_type, ERewardBy::BASE);
	}

	/*���迡 ���ú��������Ʈ�� �����մϴ�*/
	_reward_select  = _manager_pool->PoolGetReward();
	_reward_select->RewardInit(_info_reward_select, FVector(0.f));
}




void AHD_Manager_Reward::RewardGetSelect(const ERewardType e_reward_type, const ERewardBy e_reward_by)
{
	FInfoReward* s_info_reward = nullptr;
	switch (e_reward_type)
	{
	case ERewardType::GOLD:
		s_info_reward = RewardFindByType(e_reward_type);
		_gm->PlayerSetStat(EPlayerStatType::GOLD, s_info_reward->value);
		break;
	default:
		break;
	}

	switch (e_reward_by)
	{
	case ERewardBy::SELECT:
		_manager_pool->PoolInReward(_reward_select);
		_reward_select = nullptr;
		break;
	default:
		break;
	}

	//if (e_reward_by == ERewardBy::SELECT)
	//{
	//	/*��Ż�� �����մϴ�*/
	//	_gm->WaveOpenPortal();
	//}
}

FInfoReward* AHD_Manager_Reward::RewardFindByType(const ERewardType e_reward_type) { return _info_reward_all.Find(e_reward_type); }
const TArray<FInfoReward*>& AHD_Manager_Reward::GetInfoRewardsBase() { return _info_rewards_base; }
const FInfoReward* AHD_Manager_Reward::GetInfoRewardSelect() { return _info_reward_select; }
ERewardType AHD_Manager_Reward::GetRandomRewardType() { return _rewards_select_rate[UKismetMathLibrary::RandomInteger(_rewards_select_rate.Num())]; }