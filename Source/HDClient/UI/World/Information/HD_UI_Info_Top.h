// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Top.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info_Top : public UHD_UI_Master
{
	GENERATED_BODY()
	
public:
	void InfoTopInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _stage = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _wave = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _boss_hp_bar = nullptr;

public:
	void InfoTopWaveStart(const EWaveType e_wave_type);
	void InfoTopSetRound(const int32 i_round_stage, const int32 i_round_wave);
	void InfoTopSetBossHPBar(const float f_boss_hp_rate);
};
