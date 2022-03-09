// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Reward.generated.h"

class AHD_GM;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Reward : public AHD_Object
{
	GENERATED_BODY()

#pragma region Init
public:
	void RewardPostInit();
	void RewardInit(const FInfoReward* s_info_reward, const FVector& v_loc_spawn);
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	UPROPERTY()
		ERewardType _reward_type = ERewardType::NO;
#pragma endregion

public:
	UFUNCTION(BlueprintCallable)
		void ClickedReward();
};
