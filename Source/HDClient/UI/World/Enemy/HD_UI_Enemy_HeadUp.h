// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Enemy_HeadUp.generated.h"

class UProgressBar;
class AHD_Enemy;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Enemy_HeadUp : public UHD_UI_Master
{
	GENERATED_BODY()

#pragma region Init
public:
	void UIEnemyHeadUpInit(AHD_Enemy* enemy_owner);
private:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _hp_bar;
#pragma endregion

public:
	void UIEnemyHeadUpSetHPBar(const float f_hp_rate);


};
