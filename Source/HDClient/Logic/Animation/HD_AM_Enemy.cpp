// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/HD_AM_Enemy.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"

void UHD_AM_Enemy::AMPostInitChild(AHD_Unit* unit_owner)
{
	_owner = Cast<AHD_Enemy>(unit_owner);
	OnMontageEnded.AddDynamic(this, &UHD_AM_Enemy::OnAnimationFinished);
}
void UHD_AM_Enemy::OnAnimationFinished(UAnimMontage* Montage, bool bInterrupted)
{
	if (!_owner) return;
	_owner->EnemyMontageEnd();
}

void UHD_AM_Enemy::AttackBasicNotify()
{
	if (!_owner) return;
	_owner->EnemyAttackBasicNotify();
}