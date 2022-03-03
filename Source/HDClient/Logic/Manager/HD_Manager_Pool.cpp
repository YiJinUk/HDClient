// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Pool.h"
#include "Logic/HD_GI.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"

AHD_Manager_Pool::AHD_Manager_Pool()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AHD_Manager_Pool::PoolPostInit(UHD_GI* hdgi)
{
	_hdgi = hdgi;
	_spawn_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*무기 풀 초기화*/
	const TArray<FDataWeapon*>& arr_data_wp = _hdgi->GetDataWeapons();
	_pool_wp_only_equip.Reserve(arr_data_wp.Num());
	for (FDataWeapon* s_data_wp : arr_data_wp)
	{
		AHD_Weapon* wp_spawn = GetWorld()->SpawnActor<AHD_Weapon>(s_data_wp->GetClassWeapon(), _spawn_param); // 풀링 매니저
		wp_spawn->WPPostInit(s_data_wp);
		PoolInWeapon(wp_spawn);
	}
}

AHD_Weapon* AHD_Manager_Pool::PoolOutWeaponByCode(const FString& str_code_wp)
{
	AHD_Weapon* wp = nullptr;
	for (auto& it_wp : _pool_wp_only_equip)
	{
		wp = it_wp;
		if (wp->GetInfoWP().code != str_code_wp) continue;
		_pool_wp_only_equip.Remove(wp);
		return wp;
	}
	return nullptr;
}
void AHD_Manager_Pool::PoolInWeapon(AHD_Weapon* wp)
{
	if (!wp) return;
	wp->WPSetActiveTick(false);
	_pool_wp_only_equip.Add(wp);
}

AHD_Enemy* AHD_Manager_Pool::PoolGetEnemy(const FString& str_code_enemy)
{
	TArray<AHD_Enemy*>* arr_pool_enemy = _pool_enemy.Find(str_code_enemy);

	if (!arr_pool_enemy || arr_pool_enemy->Num() <= 0)
	{
		FDataEnemy* s_data_enemy = _hdgi->FindDataEnemyByCode(str_code_enemy);
		AHD_Enemy* enemy_spawn = GetWorld()->SpawnActor<AHD_Enemy>(s_data_enemy->GetClassEnemy(), _spawn_param); // 풀링 매니저
		enemy_spawn->EnemyPostInit(s_data_enemy);
		return enemy_spawn;
	}
	else
	{
		return arr_pool_enemy->Pop();
	}
}