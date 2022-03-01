// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Pool.generated.h"

class UHD_GI;
class AHD_Weapon;

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
	void PoolPostInit(UHD_GI* hdgi);
private:
	UPROPERTY()
		UHD_GI* _hdgi = nullptr;;
	FActorSpawnParameters _spawn_param = FActorSpawnParameters();
#pragma endregion

public:
	AHD_Weapon* PoolOutWeaponByCode(const FString& str_code_wp);
	void PoolInWeapon(AHD_Weapon* wp);

private:
	UPROPERTY()
		TSet<AHD_Weapon*> _pool_wp_only_equip;

};
