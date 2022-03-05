// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Pool.h"
#include "Logic/HD_FunctionLibrary.h"
#include "Logic/HD_GI.h"
#include "Logic/HD_GM.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Actor/Object/Projectile/HD_Projectile.h"
#include "Actor/Unit/Monster/HD_Monster.h"

AHD_Manager_Pool::AHD_Manager_Pool()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AHD_Manager_Pool::PoolPostInit(UHD_GI* gi, AHD_GM* gm)
{
	_gi = gi;
	_spawn_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*무기 풀 초기화*/
	const TArray<FDataWeapon*>& arr_data_wp = _gi->GetDataWeapons();
	_pool_wp_only_equip.Reserve(arr_data_wp.Num());
	for (FDataWeapon* s_data_wp : arr_data_wp)
	{
		AHD_Weapon* wp_spawn = GetWorld()->SpawnActor<AHD_Weapon>(s_data_wp->GetClassWeapon(), _spawn_param); // 풀링 매니저
		wp_spawn->WPPostInit(s_data_wp, gm->GetHero());
		PoolInWeapon(wp_spawn);
	}
}

void AHD_Manager_Pool::PoolTick()
{
	AHD_Monster* mob = nullptr;
	for (int32 i = _q_death_mob.Num() - 1; i >= 0; --i)
	{
		mob = _q_death_mob[i];
		if (mob->MOBUpdateDeathToPool())
		{
			PoolInMOB(mob);
			_q_death_mob.RemoveAt(i);
		}
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

AHD_Monster* AHD_Manager_Pool::PoolGetMOB(const FString& str_code_mob)
{
	TArray<AHD_Monster*>* arr_pool_mob = _pool_mob.Find(str_code_mob);

	if (!arr_pool_mob || arr_pool_mob->Num() <= 0)
	{
		FDataMonster* s_data_mob = _gi->FindDataMOBByCode(str_code_mob);
		if (!s_data_mob)
		{
			UHD_FunctionLibrary::GPrintString(10000, 3, "AHD_Manager_Pool::PoolGetMOB Wrong MonsterCode");
			return;
		}
		AHD_Monster* mob_spawn = GetWorld()->SpawnActor<AHD_Monster>(s_data_mob->GetClassMOB(), _spawn_param); // 풀링 매니저
		mob_spawn->UnitPostInit(EUnitClassType::ENEMY);
		mob_spawn->MOBPostInit(s_data_mob);
		return mob_spawn;
	}
	else
	{
		return arr_pool_mob->Pop();
	}
}
void AHD_Manager_Pool::PoolMOBDeath(AHD_Monster* mob)
{
	_q_death_mob.Add(mob);
}
void AHD_Manager_Pool::PoolInMOB(AHD_Monster* mob)
{
	if (!mob) return;
	mob->UnitSetActiveTick(false);
	_pool_mob.FindOrAdd(mob->GetInfoMOB().code);
}

AHD_Projectile* AHD_Manager_Pool::PoolGetPROJ(FDataProjectile* s_data_proj)
{
	if (!s_data_proj) return nullptr;

	AHD_Projectile* proj_spawn = nullptr;
	if (_pool_proj.Num() <= 0)
	{
		proj_spawn = GetWorld()->SpawnActor<AHD_Projectile>(s_data_proj->GetClassPROJ(), _spawn_param); // 풀링 매니저
		proj_spawn->PROJPostInit(s_data_proj);
		return proj_spawn;
	}
	else
	{
		return _pool_proj.Pop();
	}
}
void AHD_Manager_Pool::PoolInPROJ(AHD_Projectile* proj)
{
	if (!proj) return;
	proj->PROJSetActiveTick(false);
	_pool_proj.Add(proj);
}