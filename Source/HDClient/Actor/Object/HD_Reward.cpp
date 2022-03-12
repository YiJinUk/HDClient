// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/HD_Reward.h"
#include "Logic/HD_GM.h"

void AHD_Reward::RewardPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
}
void AHD_Reward::RewardInit(const FInfoReward* s_info_reward, const FVector& v_loc_spawn)
{
	if (!s_info_reward) return;
	_reward_type = s_info_reward->reward_type;
	SetActorLocation(v_loc_spawn);
}

void AHD_Reward::ClickedReward()
{
	_gm->RewardSelectClicked(_reward_type, ERewardBy::SELECT);
}