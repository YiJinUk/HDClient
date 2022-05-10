// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Wave_Clear_Reward.generated.h"

class AHD_GM;
class UHD_UI_Wave_Clear_Reward_Slot;
class UWrapBox;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Wave_Clear_Reward : public UHD_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIRewardPostInit();

	//웨이브.클리어시 호출
	void UIRewardInit();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		UHD_UI_Wave_Clear_Reward_Slot* CreateWidgetSlot();
private:
	UHD_UI_Wave_Clear_Reward_Slot* PoolOutSlot();
	void PoolInSlot(UHD_UI_Wave_Clear_Reward_Slot* w_slot);
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	UPROPERTY()
		UWrapBox* _reward_slot_box = nullptr;

	UPROPERTY()
		TArray<UHD_UI_Wave_Clear_Reward_Slot*> _slots;
};
