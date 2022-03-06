// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/HD_AM_Companion.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"

void UHD_AM_Companion::AMPostInitChild(AHD_Unit* unit_owner)
{
	_owner = Cast<AHD_Companion>(unit_owner);
}

void UHD_AM_Companion::AttackBasicNotify()
{
	if (!_owner) return;
	_owner->CPANAttackBasicNotify();
}
void UHD_AM_Companion::AttackSKNotify()
{
	if (!_owner) return;
	_owner->CPANAttackSKNotify();
}
