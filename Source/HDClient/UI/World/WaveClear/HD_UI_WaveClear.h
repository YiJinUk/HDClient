// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_WaveClear.generated.h"

class AHD_GM;
class UHD_UI_Main;
class UHD_UI_Wave_Clear_Reward;
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

private:
	/*
	* index 0 : empty
	* index 1 : ui_reward
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Wave_Clear_Reward* _ui_reward = nullptr;

public:
	void UIWaveClearReward();

};
