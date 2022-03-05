// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/Weapon/HD_Weapon.h"
#include "HD_WP00101.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_WP00101 : public AHD_Weapon
{
	GENERATED_BODY()
	
private:
	void WPAttackBasic(AHD_Monster* target) override;
};
