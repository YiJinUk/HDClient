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
		FInfoReward s_info_reward;
		s_info_reward.reward_type = pair.Value->GetRewardType();
		s_info_reward.value = pair.Value->GetValue();
		s_info_reward.icon = pair.Value->GetIcon();

		_info_reward_all.Add(pair.Value->GetRewardType(), s_info_reward);
	}

	/*���ú����� Ȯ���� �̸� ����ؼ� �迭�� �����մϴ�*/
	for (const FDataRewardSelectActive& s_data_reward_select_active : gi->GetDataGame()->GetRewardsSelectActive())
	{
		_rewards_select_rate.Add(s_data_reward_select_active.GetRewardSelectActive());
	}

	/*����������ü�� Ǯ�� �ʱ�ȭ�մϴ�*/
	int32 i_index = 0;
	for (int32 i = 0; i < 10; ++i)
	{
		FInfoReward s_info_reward_new;
		i_index = _reward_pool_origin.Add(s_info_reward_new);
		_reward_pool_pointer.Add(&_reward_pool_origin[i_index]);
	}
}
void AHD_Manager_Reward::RewardInit()
{
	/*�⺻������ �ʱ�ȭ�մϴ�*/
	_rewards_base.Empty(3);
	FInfoReward* s_info_reward = nullptr;
	//�⺻������ ���ʷ� ��庸���� ������ �����մϴ�
	s_info_reward = PoolOutInfoReward();
	s_info_reward->reward_type = ERewardType::GOLD;
	s_info_reward->value = 50;
	_rewards_base.Add(s_info_reward);

	/*���������� �ʱ�ȭ�մϴ�*/
	if (_rewards_random.Num() > 0)
	{
		for (FInfoReward* s_info_reward_rnd : _rewards_random)
		{
			PoolInInfoReward(s_info_reward_rnd);
		}
	}
	_rewards_random.Empty(3);
	
	for (int32 i = 0; i < _gm->GetInfoPlayer().reward_random_count; ++i)
	{
		s_info_reward = PoolOutInfoReward();

		_rewards_random.Add(s_info_reward);
	}
}
void AHD_Manager_Reward::RewardWaveNext()
{
	//���������� ������ �̸� ����صӴϴ�
	_rewards_random.Empty(3);
	RewardCalcTypes(_rewards_random);
}
void AHD_Manager_Reward::RewardWaveEnd()
{
	///*���̺갡 ����Ǿ����ϴ�. ��ٷ� �⺻������ ȹ���մϴ�.*/
	//for (const FInfoReward* s_info_reward_base : _info_rewards_base)
	//{
	//	RewardGetSelect(s_info_reward_base->reward_type, ERewardBy::BASE);
	//}

	///*���迡 ���ú��������Ʈ�� �����մϴ�*/
	//_reward_select  = _manager_pool->PoolGetReward();
	//_reward_select->RewardInit(_info_reward_select, FVector(0.f));
}
void AHD_Manager_Reward::RewardCalcTypes(TSet<FInfoReward*>& arr_reward)
{
	uint8 i_index = 0;
	for (FInfoReward* s_info_reward : arr_reward)
	{
		i_index = UKismetMathLibrary::RandomInteger(_rewards_select_rate.Num());
		s_info_reward->reward_type = _rewards_select_rate[i_index];
		s_info_reward->value = 50;
		_rewards_select_rate.RemoveAt(i_index);
	}

	for (FInfoReward* s_info_reward : arr_reward)
	{
		_rewards_select_rate.Add(s_info_reward->reward_type);
	}
}



void AHD_Manager_Reward::RewardGetSelect(const ERewardType e_reward_type, const ERewardBy e_reward_by)
{
	//FInfoReward* s_info_reward = nullptr;
	//switch (e_reward_type)
	//{
	//case ERewardType::GOLD:
	//	s_info_reward = RewardFindByType(e_reward_type);
	//	_gm->PlayerSetStat(EPlayerStatType::GOLD, s_info_reward->value);
	//	break;
	//default:
	//	break;
	//}

	//switch (e_reward_by)
	//{
	//case ERewardBy::SELECT:
	//	_manager_pool->PoolInReward(_reward_select);
	//	_reward_select = nullptr;
	//	break;
	//default:
	//	break;
	//}

	//if (e_reward_by == ERewardBy::SELECT)
	//{
	//	/*��Ż�� �����մϴ�*/
	//	_gm->WaveOpenPortal();
	//}
}

FInfoReward* AHD_Manager_Reward::PoolOutInfoReward()
{
	if (_reward_pool_pointer.Num() <= 0)
	{
		FInfoReward s_info_reward_new;
		int32 i_index = _reward_pool_origin.Add(s_info_reward_new);
		return &_reward_pool_origin[i_index];
	}
	else
	{
		return _reward_pool_pointer.Pop();
	}
}
void AHD_Manager_Reward::PoolInInfoReward(FInfoReward* s_info_reward)
{
	if (!s_info_reward) return;
	s_info_reward->InitInfoReward();
	_reward_pool_pointer.Add(s_info_reward);
}

FInfoReward* AHD_Manager_Reward::RewardFindByType(const ERewardType e_reward_type) { return _info_reward_all.Find(e_reward_type); }
const TSet<FInfoReward*>& AHD_Manager_Reward::GetRewardsRandom() { return _rewards_random; }
const TArray<FInfoReward*>& AHD_Manager_Reward::GetRewardsBase() { return _rewards_base; }