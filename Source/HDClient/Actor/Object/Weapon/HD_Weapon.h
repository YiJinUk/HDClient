// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Weapon : public AHD_Object
{
	GENERATED_BODY()

#pragma region Init
public:
	void WPPostInit(const FDataWeapon* s_data_wp);
	void WPInit(class USkeletalMeshComponent* skmc);

	void WPSetActiveTick(const bool b_is_active);

	const FInfoWeapon& GetInfoWP();
private:
	UPROPERTY()
		FInfoWeapon _info_wp;
#pragma endregion
};
