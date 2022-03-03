// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/HD_AM_Hero.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"

void UHD_AM_Hero::AMPostInitChild(AHD_Unit* unit_owner)
{
	_owner = Cast<AHD_Hero>(unit_owner);
}

void UHD_AM_Hero::AttackBasicNotify()
{
	if (!_owner) return;
	_owner->AttackBasicNotify();
}