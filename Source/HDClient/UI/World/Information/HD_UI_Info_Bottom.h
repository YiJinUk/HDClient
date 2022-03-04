// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Bottom.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info_Bottom : public UHD_UI_Master
{
	GENERATED_BODY()

#pragma region Init
public:
	void InfoBottomPostInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _hp_bar = nullptr;
#pragma endregion

public:
	void InfoBottomSetHPBar(const float f_hp_rate);
};
