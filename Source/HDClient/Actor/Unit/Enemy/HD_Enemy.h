// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/HD_Unit.h"
#include "HD_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Enemy : public AHD_Unit
{
	GENERATED_BODY()
	
#pragma region Init
public:
	AHD_Enemy();
	void EnemyPostInit(FDataEnemy* s_data_enemy);
	void EnemyInit(const FVector v_loc_spawn);
#pragma endregion
};
