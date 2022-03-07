// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_HeadUp_Monster.generated.h"

class UProgressBar;
class AHD_Monster;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_HeadUp_Monster : public UHD_UI_Master
{
	GENERATED_BODY()

#pragma region Init
public:
	void UIEnemyHeadUpInit(AHD_Monster* mob_owner);
private:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _hp_bar;
#pragma endregion

public:
	void UIEnemyHeadUpSetHPBar(const float f_hp_rate);


};
