// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_HeadUp_MS.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_HeadUp_MS : public UHD_UI_Master
{
	GENERATED_BODY()

#pragma region Init
private:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _cooldown = nullptr;
#pragma endregion

public:
	void UISetCooldown(const float f_cd_rate);
};
