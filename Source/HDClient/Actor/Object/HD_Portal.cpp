// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/HD_Portal.h"
#include "Logic/HD_GM.h"

void AHD_Portal::PortalPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
}
void AHD_Portal::PortalInit(const ERewardType e_reward_type, const FVector& v_loc_spawn)
{
	_reward_type = e_reward_type;
	SetActorLocation(v_loc_spawn);
}

void AHD_Portal::ClickedPortal()
{
	_gm->WaveNextAndStart(_reward_type);
}