// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/WaveClear/Reward/HD_UI_Wave_Clear_Reward.h"
#include "HD_UI_Wave_Clear_Reward_Slot.h"
#include "Logic/HD_GM.h"
#include "Logic/Manager/HD_Manager_Reward.h"

#include "Components/WrapBox.h"

void UHD_UI_Wave_Clear_Reward::UIRewardPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	for (int32 i = 0; i < 3; ++i)
	{
		UHD_UI_Wave_Clear_Reward_Slot* w_slot = CreateWidgetSlot();
		_slots.Add(w_slot);
	}
}

void UHD_UI_Wave_Clear_Reward::UIRewardInit()
{
	//���������� ������ �������̺�� ������ �� �����Ǳ� ������
	//�ٷ� �����ͼ� ����մϴ�

	UHD_UI_Wave_Clear_Reward_Slot* w_slot = nullptr;

	//���� �ʱ�ȭ
	for (UWidget* w_child : _reward_slot_box->GetAllChildren())
	{
		w_slot = Cast<UHD_UI_Wave_Clear_Reward_Slot>(w_child);
		PoolInSlot(w_slot);
	}
	_reward_slot_box->ClearChildren();

	//�������� ����
	for (FInfoReward* s_info_reward : _gm->GetManagerReward()->GetRewardsRandom())
	{
		w_slot = PoolOutSlot();
		w_slot->UIRewardSlotInit(s_info_reward);
		_reward_slot_box->AddChild(w_slot);
	}
}

UHD_UI_Wave_Clear_Reward_Slot* UHD_UI_Wave_Clear_Reward::PoolOutSlot()
{
	if (_slots.Num() <= 0)
	{
		return CreateWidgetSlot();
	}
	else
	{
		return _slots.Pop();
	}
}
void UHD_UI_Wave_Clear_Reward::PoolInSlot(UHD_UI_Wave_Clear_Reward_Slot* w_slot)
{
	if (!w_slot) return;
	_slots.Add(w_slot);
}