// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Weapon/HD_Weapon.h"

void AHD_Weapon::WPPostInit(FDataWeapon* s_data_wp)
{
	if (!s_data_wp) return;

	_info_wp.code = s_data_wp->GetCode();
	_info_wp.str = s_data_wp->GetSTR();
	_info_wp.as = s_data_wp->GetAS();
	_info_wp.anim_attack_basic = s_data_wp->GetAnimAttackBasic();
}
void AHD_Weapon::WPInit(class USkeletalMeshComponent* skmc)
{
	SetActorLocation(FVector(0.f));
	AttachToComponent(skmc, FAttachmentTransformRules::KeepRelativeTransform, "Weapon");
}
void AHD_Weapon::WPSetActiveTick(const bool b_is_active)
{
	if (b_is_active)
	{

	}
	else
	{
		SetActorLocation(FVector(-1000, -1000, 0));
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	}
}

const FInfoWeapon& AHD_Weapon::GetInfoWP() { return _info_wp; }