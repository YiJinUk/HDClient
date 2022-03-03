// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Enemy/HD_Enemy.h"

AHD_Enemy::AHD_Enemy()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AHD_Enemy::EnemyPostInit(FDataEnemy* s_data_enemy)
{
	if (!s_data_enemy) return;
}
void AHD_Enemy::EnemyInit(const FVector v_loc_spawn)
{
	SetActorLocation(v_loc_spawn);
}