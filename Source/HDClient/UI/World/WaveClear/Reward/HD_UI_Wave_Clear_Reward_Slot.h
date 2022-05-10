// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Wave_Clear_Reward_Slot.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Wave_Clear_Reward_Slot : public UHD_UI_Master
{
	GENERATED_BODY()
	
public:
	//box������ �߰��ɶ�, Ǯ���� ������ �� ȣ��
	void UIRewardSlotInit(const FInfoReward* s_info_reward);
private:
	UPROPERTY(Meta = (BindWidget))
		UImage* _icon = nullptr;
};
