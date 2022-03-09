// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/WaveClear/HD_UI_WaveClear.h"
#include "../../HD_UI_Main.h"
//#include "HD_UI_WaveClear_Reward_Base.h"
//#include "HD_UI_WaveClear_Reward_Select.h"
//#include "HD_UI_WaveClear_Reward_Next.h"
//#include "HD_UI_WaveClear_Reward_Slot.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GM.h"
#include "Logic/Manager/HD_Manager_Reward.h"

//#include "Components/WidgetSwitcher.h"

void UHD_UI_WaveClear::UIWaveClearPostInit(UHD_UI_Main* ui_main)
{
	ui_main->UIMainSetUIWaveClear(this);
	//_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	//_switcher->SetActiveWidgetIndex(0);

	//_ui_reward_base->UIRewardBasePostInit(this);
}
//void UHD_UI_WaveClear::UIWaveClearInit()
//{
//	/*
//	* 게임모드에서 기본보상타입을 가져옵니다
//	* 보상매니저에서 기본보상팁에 해당하는 보상정보를 가져옵니다
//	* 가져온 보상정보를 RewardBaseUI에 넘겨줍니다
//	*/
//	
//	//_ui_reward_base->UIRewardBaseInit(_gm->GetManagerReward()->GetInfoRewardsBase());
//	//_switcher->SetActiveWidgetIndex(1);
//}
//void UHD_UI_WaveClear::UIWaveClearRewardToSelect()
//{
//	//_ui_reward_base->UIRewardSelectInit(_gm->GetManagerReward()->GetInfoRewardSelect());
//	//_switcher->SetActiveWidgetIndex(2);
//}
//void UHD_UI_WaveClear::UIWaveClearSelectReward(const ERewardType e_reward_type, const ERewardBy e_reward_by)
//{
//	_gm->RewardSelectSend(e_reward_type, e_reward_by);
//}
//
//UHD_UI_WaveClear_Reward_Slot* UHD_UI_WaveClear::UIWaveClearGetSlot()
//{
//	if (_slots.Num() <= 0)
//	{
//		UHD_UI_WaveClear_Reward_Slot* w_slot = UIWaveClearCreateWidgetSlot();
//		w_slot->UIRewardPostInit(this);
//		return w_slot;
//	}
//	else
//	{
//		return _slots.Pop();
//	}
//}
//void UHD_UI_WaveClear::UIWaveClearAddSlot(UHD_UI_WaveClear_Reward_Slot* w_slot)
//{
//	if (!w_slot) return;
//	_slots.Add(w_slot);
//}