// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_WaveClear.generated.h"

class AHD_GM;
class UHD_UI_Main;
//class UHD_UI_WaveClear_Reward_Base;
//class UHD_UI_WaveClear_Reward_Select;
//class UHD_UI_WaveClear_Reward_Next;
//class UHD_UI_WaveClear_Reward_Slot;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_WaveClear : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void UIWaveClearPostInit(UHD_UI_Main* ui_main);

//	UHD_UI_WaveClear_Reward_Slot* UIWaveClearGetSlot();
//	void UIWaveClearAddSlot(UHD_UI_WaveClear_Reward_Slot* w_slot);
//protected:
//	UFUNCTION(BlueprintImplementableEvent)
//		UHD_UI_WaveClear_Reward_Slot* UIWaveClearCreateWidgetSlot();
private:
	/*
	* index 0 : empty
	* index 1 : reward_base
	* index 2 : reward_select
	* index 3 : reward_next
	*/
	//UPROPERTY(Meta = (BindWidget))
	//	UWidgetSwitcher* _switcher = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UHD_UI_WaveClear_Reward_Base* _ui_reward_base = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UHD_UI_WaveClear_Reward_Select* _ui_reward_select = nullptr;
	//UPROPERTY(Meta = (BindWidget))
	//	UHD_UI_WaveClear_Reward_Next* _ui_reward_next = nullptr;

	//UPROPERTY()
	//	TArray<UHD_UI_WaveClear_Reward_Slot*> _slots;

	//UPROPERTY()
	//	AHD_GM* _gm = nullptr;
	//UPROPERTY()
	//	UHD_UI_Main* _ui_main = nullptr;
#pragma endregion

public:
	//void UIWaveClearInit();
	//void UIWaveClearRewardToSelect();

	//void UIWaveClearSelectReward(const ERewardType e_reward_type, const ERewardBy e_reward_by);
};
