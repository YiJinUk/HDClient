// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GI.h"

UHD_GI::UHD_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Game.HDDT_Game"));
	if (DT_GAME.Succeeded()) { _dt_game = DT_GAME.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVE(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Wave.HDDT_Wave"));
	if (DT_WAVE.Succeeded()) { _dt_wave = DT_WAVE.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Enemy.HDDT_Enemy"));
	if (DT_ENEMY.Succeeded()) { _dt_enemy = DT_ENEMY.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPON(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Weapon.HDDT_Weapon"));
	if (DT_WEAPON.Succeeded()) { _dt_weapon = DT_WEAPON.Object; }
}
void UHD_GI::GIPostInit()
{
	_dt_weapon->GetAllRows("0", _data_wps);
	_dt_wave->GetAllRows("0", _data_waves);
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
}

FDataEnemy* UHD_GI::FindDataEnemyByCode(const FString& str_code_enemy)
{
	if (!_dt_enemy) return nullptr;
	return _dt_enemy->FindRow<FDataEnemy>(*str_code_enemy, "0");
}

const TArray<FDataWeapon*>& UHD_GI::GetDataWeapons() { return _data_wps; }
const TArray<FDataWave*>& UHD_GI::GetDataWaves() { return _data_waves; }
FDataGame* UHD_GI::GetDataGame() { return _data_game; }