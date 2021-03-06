// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_PC.h"
#include "HD_GM.h"
#include "HD_FunctionLibrary.h"
#include "UI/HD_UI_Main.h"
#include "UI/World/FloatingDMGNumber/HD_UI_FloatingDMGNumber.h"

#include "Kismet/GameplayStatics.h"

void AHD_PC::PCPostInit()
{
	PCBPPostInit();
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_ui_main = PCBPCreateWidgetMain();
	_ui_main->UIMainPostInit();

	for (int32 i = 0; i < 30; ++i)
		_pool_floating_dmg_num.Add(PCBPCreateWidgetFloatingDMGNumber());
}
void AHD_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Tap", IE_Pressed, this, &AHD_PC::TapPressed);
	InputComponent->BindAction("Tap", IE_Released, this, &AHD_PC::TapReleased);
}
void AHD_PC::TapPressed() { _is_tap_pressed = true; }
void AHD_PC::TapReleased() { _is_tap_pressed = false; }
void AHD_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!_gm) return;
	if (_is_tap_pressed)
	{
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, _tap_hit);
		_gm->ChangeHeroPROJVelocity(_tap_hit.Location);
	}
}

void AHD_PC::PCWorldStart()
{
	//_gm->WorldStart();
	_ui_main->UIMainWorldStart();
}
void AHD_PC::PCWorldGameOver()
{
	_ui_main->UIMainWorldGameOver();
}
void AHD_PC::PCUIReturnToHome()
{
	_ui_main->UIMainReturnToHome();
}
void AHD_PC::PCWorldClear()
{
	_ui_main->UIMainWorldClear();
}
void AHD_PC::PCUIWorldClearToHome()
{
	_ui_main->UIMainClearToHome();
}

void AHD_PC::PCWaveNextAndStart(const int32 i_round_stage, const int32 i_round_wave, const EWaveType e_wave_type)
{
	_ui_main->UIMainWaveNextAndStart(i_round_stage, i_round_wave, e_wave_type);
}
void AHD_PC::PCWaveClear()
{
	_ui_main->UIMainWaveClear();
}
void AHD_PC::PCWaveClearReward()
{
	_ui_main->UIMainWaveClearReward();
}

void AHD_PC::PCUIUpdateBossHPRate(const float f_boss_hp_rate)
{
	_ui_main->UIMainUpdateBossHPRate(f_boss_hp_rate);
}

void AHD_PC::PCUIRewardToSelect()
{
	_ui_main->UIMainRewardToSelect();
}

void AHD_PC::PCUIUpdateStat(const EUnitStatType e_unit_stat_type, const EUnitStatBy e_unit_stat_by, const int32 i_value, const float f_value)
{
	_ui_main->UIMainUpdateStat(e_unit_stat_type, e_unit_stat_by, i_value, f_value);
}

void AHD_PC::PCUIFloatingDMGNumber(const FVector& v_loc, const int32 i_dmg)
{
	UHD_UI_FloatingDMGNumber* slot = PoolGetFloatingDMGNum();
	if (!slot) return;

	FVector2D v_loc_floating;
	UGameplayStatics::ProjectWorldToScreen(this, v_loc, v_loc_floating);
	v_loc_floating += FVector2D(10.f, -50.f); // Offset

	slot->AddToViewport();
	slot->SetPositionInViewport(v_loc_floating);
	slot->PlaySlot(i_dmg);
}

UHD_UI_FloatingDMGNumber* AHD_PC::PoolGetFloatingDMGNum()
{
	if (_pool_floating_dmg_num.Num() <= 0)
	{
		return PCBPCreateWidgetFloatingDMGNumber();
	}
	else
	{
		return _pool_floating_dmg_num.Pop();
	}
}
void AHD_PC::PoolInFloatingDMGNum(UHD_UI_FloatingDMGNumber* w_slot)
{
	if (!w_slot) return;
	_pool_floating_dmg_num.Add(w_slot);
}