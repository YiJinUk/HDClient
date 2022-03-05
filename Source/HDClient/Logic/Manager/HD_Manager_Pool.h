// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Pool.generated.h"

class UHD_GI;
class AHD_GM;
class AHD_Weapon;
class AHD_Enemy;
class AHD_Projectile;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Manager_Pool : public AHD_Manager_Master
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	AHD_Manager_Pool();
public:
	void PoolPostInit(UHD_GI* gi, AHD_GM* gm);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;;
	FActorSpawnParameters _spawn_param = FActorSpawnParameters();
#pragma endregion

#pragma region Tick
public:
	void PoolTick();
#pragma endregion

#pragma region Weapon
public:
	AHD_Weapon* PoolOutWeaponByCode(const FString& str_code_wp);
	void PoolInWeapon(AHD_Weapon* wp);
private:
	UPROPERTY()
		TSet<AHD_Weapon*> _pool_wp_only_equip;
#pragma endregion

#pragma region Enemy
public:
	AHD_Enemy* PoolGetEnemy(const FString& str_code_enemy);
	void PoolEnemyDeath(AHD_Enemy* enemy);
private:
	void PoolInEnemy(AHD_Enemy* enemy);
private:
	TMap<FString, TArray<AHD_Enemy*>> _pool_enemy;
	UPROPERTY()
		TArray<AHD_Enemy*> _q_death_enemy;
#pragma endregion

#pragma region Projectile
public:
	AHD_Projectile* PoolGetPROJ(FDataProjectile* s_data_proj);
	void PoolInPROJ(AHD_Projectile* proj);
private:
	TArray<AHD_Projectile*, TInlineAllocator<100>> _pool_proj;
#pragma endregion

};
