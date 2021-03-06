// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Main.generated.h"

class UWidgetSwitcher;
class UHD_UI_Home;
class UHD_UI_World;
class UHD_UI_Info_Bottom;
class UHD_UI_Info_Top;
class UHD_UI_WaveClear;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Main : public UHD_UI_Master
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	//virtual void NativeConstruct() override;
public:
	void UIMainPostInit();

	void UIMainSetUIInfoBottom(UHD_UI_Info_Bottom* ui_info_bottom);
	void UIMainSetUIInfoTop(UHD_UI_Info_Top* ui_info_top);
	void UIMainSetUIWaveClear(UHD_UI_WaveClear* ui_wave_clear);
private:
	/*
	* index 0 : home
	* index 1 : world
	*/
	UPROPERTY(Meta = (BindWidget), Transient)
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget), Transient)
		UHD_UI_Home* _ui_home = nullptr;
	UPROPERTY(Meta = (BindWidget), Transient)
		UHD_UI_World* _ui_world = nullptr;

	UPROPERTY()
		UHD_UI_Info_Bottom* _ui_info_bottom = nullptr;
	UPROPERTY()
		UHD_UI_Info_Top* _ui_info_top = nullptr;
	UPROPERTY()
		UHD_UI_WaveClear* _ui_wave_clear = nullptr;
#pragma endregion

public:
	void UIMainWorldStart();
	void UIMainWorldGameOver();
	void UIMainReturnToHome();
	void UIMainWorldClear();
	void UIMainClearToHome();
	
	void UIMainWaveNextAndStart(const int32 i_round_stage, const int32 i_round_wave, const EWaveType e_wave_type);
	void UIMainWaveClear();
	void UIMainWaveClearReward();

	void UIMainUpdateBossHPRate(const float f_boss_hp_rate);

	void UIMainRewardToSelect();

	void UIMainUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value, const float f_value);
};
