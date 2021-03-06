// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_World.generated.h"

class UWidgetSwitcher;
class UButton;
class AHD_GM;
class UHD_UI_Info;
class UHD_UI_Main;
class UHD_UI_GameOver;
class UHD_UI_WorldClear;
class UHD_UI_WaveClear;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_World : public UHD_UI_Master
{
	GENERATED_BODY()

#pragma region Init
public:
	void WorldPostInit(UHD_UI_Main* ui_main);
	void WorldInit();
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	/*
	* index 0 : ui_info
	* index 1 : game_over
	* index 2 : world_clear
	* index 3 : wave_clear
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Info* _ui_info = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_GameOver* _ui_game_over = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_WorldClear* _ui_world_clear = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_WaveClear* _ui_wave_clear = nullptr;
#pragma endregion

public:
	void UIWorldGameOver();
	void UIWorldReturnToHome();
	void UIWorldWorldClear();
	void UIWorldClearToHome();

	void UIWorldWaveStart();
	void UIWorldWaveClear();
	void UIWorldWaveNext();

};
