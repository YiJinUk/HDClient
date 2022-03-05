// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Bottom.generated.h"

class UProgressBar;
class UTextBlock;
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
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _armor_bar = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* _sk_cooldown_bar = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _armor = nullptr;
#pragma endregion

public:
	void InfoBottomSetHPBar(const float f_hp_rate);
	void InfoBottomSetArmorBar(const float f_armor_rate);
	void InfoBottomSetArmorText(const int32 i_armor);
	void InfoBottomSetSKCooldownBar(const float f_sk_cooldown_rate);
};
