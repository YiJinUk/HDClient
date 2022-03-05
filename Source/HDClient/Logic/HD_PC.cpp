// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_PC.h"
#include "HD_GM.h"
#include "UI/HD_UI_Main.h"
#include "UI/World/FloatingDMGNumber/HD_UI_FloatingDMGNumber.h"

#include "Kismet/GameplayStatics.h"

void AHD_PC::PCPostInit()
{
	PCBPPostInit();
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	_ui_main = PCBPCreateWidgetMain();
	_ui_main->UIMainPostInit();
}

void AHD_PC::PCWorldStart()
{
	_gm->WorldStart();
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

void AHD_PC::PCWaveStart()
{
	_ui_main->UIMainWaveStart();
}
void AHD_PC::PCWaveEnd()
{
	_ui_main->UIMainWaveEnd();
}
void AHD_PC::PCWaveNext(const int32 i_round_stage, const int32 i_round_wave)
{
	_ui_main->UIMainWaveNext(i_round_stage, i_round_wave);
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
	v_loc_floating += FVector2D(10.f, -50.f);

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