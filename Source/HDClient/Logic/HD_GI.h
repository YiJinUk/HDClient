// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Engine/GameInstance.h"
#include "HD_GI.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_GI : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	UHD_GI();
public:
	void GIPostInit();
#pragma endregion

#pragma region Data
public:
	FDataMonster* FindDataMOBByCode(const FString& str_code_mob);
	FDataProjectile* FindDataPROJByCode(const FString& str_code_proj);
	FDataVFX* FindDataVFXByCode(const FString& str_code_vfx);

	const TArray<FDataWeapon*>& GetDataWeapons();
	const TArray<FDataWave*>& GetDataWaves();
	FDataGame* GetDataGame();
	FDataHero* GetDataHero();
private:
	UDataTable* _dt_game = nullptr;
	UDataTable* _dt_wave = nullptr;
	UDataTable* _dt_hero = nullptr;
	UDataTable* _dt_mob = nullptr;
	UDataTable* _dt_weapon = nullptr;
	UDataTable* _dt_proj = nullptr;
	UDataTable* _dt_vfx = nullptr;

	TArray<FDataWeapon*> _data_wps;
	TArray<FDataWave*> _data_waves;
	FDataGame* _data_game = nullptr;
	FDataHero* _data_hero = nullptr;
#pragma endregion
};
