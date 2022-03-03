// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Unit/Enemy/HD_Enemy.h"

AHD_Enemy::AHD_Enemy()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AHD_Enemy::EnemyPostInit(FDataEnemy* s_data_enemy)
{
	if (!s_data_enemy) return;

	_info_enemy.move_speed = s_data_enemy->GetMoveSpeed();
}
void AHD_Enemy::EnemyInit(const int64 i_id, const FVector v_loc_spawn)
{
	_info_enemy.id = i_id;
	SetActorLocation(v_loc_spawn);
}

void AHD_Enemy::EnemyMove(const float f_delta_time, const FVector& v_loc_move, const FRotator& r_rot)
{
	_info_enemy.lane_dist = _info_enemy.lane_dist + ((float)_info_enemy.move_speed * f_delta_time);
	SetActorLocation(v_loc_move);
	SetActorRotation(r_rot);
}

const FInfoEnemy& AHD_Enemy::GetInfoEnemy() { return _info_enemy; }