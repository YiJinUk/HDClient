// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Weapon.generated.h"

class AHD_GM;
class AHD_Monster;
class AHD_Hero;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Weapon : public AHD_Object
{
	GENERATED_BODY()

#pragma region Init
public:
	void WPPostInit(FDataWeapon* s_data_wp, AHD_Hero* hero);
	void WPInit(class USkeletalMeshComponent* skmc);

	void WPSetActiveTick(const bool b_is_active);

	const FInfoWeapon& GetInfoWP();
protected:
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		FInfoWeapon _info_wp;
#pragma endregion

#pragma region Attack.Basic
public:
	virtual void WPAttackBasic(AHD_Monster* target, const FVector2D& v2_dest);
#pragma endregion
};
