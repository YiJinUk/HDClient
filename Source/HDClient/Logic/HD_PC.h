// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "GameFramework/PlayerController.h"
#include "HD_PC.generated.h"

class UHD_UI_Main;
class UHD_UI_FloatingDMGNumber;
class AHD_GM;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_PC : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void PCPostInit();
protected:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
		void PCBPPostInit();
	UFUNCTION(BlueprintImplementableEvent)
		UHD_UI_Main* PCBPCreateWidgetMain();
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;
#pragma endregion

#pragma region Input
protected:
	virtual void SetupInputComponent() override;
private:
	void TapPressed();
	void TapReleased();
private:
	UPROPERTY()
		bool _is_tap_pressed = false;
	UPROPERTY()
		FHitResult _tap_hit = FHitResult();
#pragma endregion

#pragma region Widget
private:
	UPROPERTY()
		UHD_UI_Main* _ui_main = nullptr;
#pragma endregion

#pragma region World
public:
	void PCWorldStart();
	void PCWorldGameOver();
	void PCUIReturnToHome();
	void PCWorldClear();
	void PCUIWorldClearToHome();
#pragma endregion

#pragma region Stage,Wave
public:
	void PCWaveNextAndStart(const int32 i_round_stage, const int32 i_round_wave, const EWaveType e_wave_type);
	void PCWaveClear();
	void PCWaveClearReward();
#pragma endregion

#pragma region Monster
public:
	void PCUIUpdateBossHPRate(const float f_boss_hp_rate);
#pragma endregion

#pragma region Reward
public:
	void PCUIRewardToSelect();
#pragma endregion

#pragma region UI
public:
	void PCUIUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value = 0, const float f_value = 0.f);

	void PCUIFloatingDMGNumber(const FVector& v_loc, const int32 i_dmg);
	void PoolInFloatingDMGNum(UHD_UI_FloatingDMGNumber* w_slot);
protected:
	UFUNCTION(BlueprintImplementableEvent)
		UHD_UI_FloatingDMGNumber* PCBPCreateWidgetFloatingDMGNumber();
private:
	UHD_UI_FloatingDMGNumber* PoolGetFloatingDMGNum();
private:
	UPROPERTY()
		TArray<UHD_UI_FloatingDMGNumber*> _pool_floating_dmg_num;
#pragma endregion


};
