// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/HD_AM_Monster.h"
#include "Actor/Unit/Monster/HD_Monster.h"

void UHD_AM_Monster::AMPostInitChild(AHD_Unit* unit_owner)
{
	_owner = Cast<AHD_Monster>(unit_owner);
	OnMontageEnded.AddDynamic(this, &UHD_AM_Monster::OnAnimationFinished);
}
void UHD_AM_Monster::OnAnimationFinished(UAnimMontage* Montage, bool bInterrupted)
{
	if (!_owner) return;
	_owner->MOBMontageEnded();
}

void UHD_AM_Monster::AttackBasicNotify()
{
	if (!_owner) return;
	_owner->MOBAttackBasicNotify();
}

void UHD_AM_Monster::AMSetIsDeath(const bool b_is_death) { _is_death = b_is_death; }
