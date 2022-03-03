// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"
#include "HD_ENEMY01001.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_ENEMY01001 : public AHD_Enemy
{
	GENERATED_BODY()
	
protected:
	void EnemyAttackBasic() override;
};
