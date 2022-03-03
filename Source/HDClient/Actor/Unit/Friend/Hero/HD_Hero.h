// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Unit/Friend/HD_Friend.h"
#include "HD_Hero.generated.h"

class AHD_Weapon;
class AHD_Enemy;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Hero : public AHD_Friend
{
	GENERATED_BODY()

#pragma region Init
public:
	const FInfoHero& GetInfoHero();
private:
	UPROPERTY()
		FInfoHero _info_hero;
#pragma endregion

#pragma region Weapon
public:
	void HeroChangeWeapon(AHD_Weapon* wp_change);
#pragma endregion

#pragma region Attack.Basic
public:
	//�⺻������ �����մϴ�
	void AttackBasicStart(AHD_Enemy* target);
	//�⺻���ݾִϸ��̼��� �������ظ� �õ��մϴ�
	void AttackBasicNotify();

	bool HeroUpdateAS(const uint8 i_tick);
#pragma endregion

};
