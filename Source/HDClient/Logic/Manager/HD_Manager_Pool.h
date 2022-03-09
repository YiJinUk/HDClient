// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Pool.generated.h"

class UHD_GI;
class AHD_GM;
class AHD_PC;
class AHD_Weapon;
class AHD_Monster;
class AHD_Companion;
class AHD_Projectile;
class AHD_Reward;
class AHD_Portal;

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
	void PoolPostInit(UHD_GI* gi, AHD_GM* gm, AHD_PC* pc);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_PC* _pc = nullptr;
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

#pragma region Companion
public:
	AHD_Companion* PoolGetCPAN(const FString& str_code_cpan);
	void PoolInCPAN(AHD_Companion* cpan);
private:
	UPROPERTY()
		TSet<AHD_Companion*> _pool_cpan;
#pragma endregion

#pragma region Monster
public:
	AHD_Monster* PoolGetMOB(const FString& str_code_mob);
	void PoolMOBDeath(AHD_Monster* mob);
private:
	void PoolInMOB(AHD_Monster* mob);
private:
	TMap<FString, TArray<AHD_Monster*>> _pool_mob;
	UPROPERTY()
		TArray<AHD_Monster*> _q_death_mob;
#pragma endregion

#pragma region Projectile
public:
	AHD_Projectile* PoolGetPROJ(FDataProjectile* s_data_proj);
	void PoolInPROJ(AHD_Projectile* proj);
private:
	TArray<AHD_Projectile*, TInlineAllocator<50>> _pool_proj;
#pragma endregion

#pragma region Reward
public:
	AHD_Reward* PoolGetReward();
	void PoolInReward(AHD_Reward* reward);
private:
	TArray<AHD_Reward*, TInlineAllocator<6>> _pool_reward;
#pragma endregion

#pragma region Portal
public:
	AHD_Portal* PoolGetPortal();
	void PoolInPortal(AHD_Portal* portal);
private:
	TArray<AHD_Portal*, TInlineAllocator<6>> _pool_portal;
#pragma endregion

};
