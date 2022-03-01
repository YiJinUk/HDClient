// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Weapon/HD_Weapon.h"

void AHD_Weapon::WPPostInit(const FDataWeapon* s_data_wp)
{
	if (!s_data_wp) return;

	_info_wp.code = s_data_wp->GetCode();
}
void AHD_Weapon::WPInit()
{
	SetActorLocation(FVector(0, 0, 100));
}

const FInfoWeapon& AHD_Weapon::GetInfoWP() { return _info_wp; }