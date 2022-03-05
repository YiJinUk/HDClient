// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GI.h"

UHD_GI::UHD_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Game.HDDT_Game"));
	if (DT_GAME.Succeeded()) { _dt_game = DT_GAME.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVE(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Wave.HDDT_Wave"));
	if (DT_WAVE.Succeeded()) { _dt_wave = DT_WAVE.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HERO(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Hero.HDDT_Hero"));
	if (DT_HERO.Succeeded()) { _dt_hero = DT_HERO.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MOB(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Monster.HDDT_Monster"));
	if (DT_MOB.Succeeded()) { _dt_mob = DT_MOB.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPON(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Weapon.HDDT_Weapon"));
	if (DT_WEAPON.Succeeded()) { _dt_weapon = DT_WEAPON.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PROJ(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Projectile.HDDT_Projectile"));
	if (DT_PROJ.Succeeded()) { _dt_proj = DT_PROJ.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_VFX(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_VFX.HDDT_VFX"));
	if (DT_VFX.Succeeded()) { _dt_vfx = DT_VFX.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SK(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Skill.HDDT_Skill"));
	if (DT_SK.Succeeded()) { _dt_sk = DT_SK.Object; }
}
void UHD_GI::GIPostInit()
{
	_dt_weapon->GetAllRows("0", _data_wps);
	_dt_wave->GetAllRows("0", _data_waves);
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
	_data_hero = _dt_hero->FindRow<FDataHero>("HERO00001", "0");
}

FDataMonster* UHD_GI::FindDataMOBByCode(const FString& str_code_mob) { return _dt_mob->FindRow<FDataMonster>(*str_code_mob, "0"); }
FDataProjectile* UHD_GI::FindDataPROJByCode(const FString& str_code_proj) { return _dt_proj->FindRow<FDataProjectile>(*str_code_proj, "0"); }
FDataVFX* UHD_GI::FindDataVFXByCode(const FString& str_code_vfx) { return _dt_vfx->FindRow<FDataVFX>(*str_code_vfx, "0"); }
FDataSkill* UHD_GI::FindDataSKByCode(const FString& str_code_sk) { return _dt_sk->FindRow<FDataSkill>(*str_code_sk, "0"); }

const TArray<FDataWeapon*>& UHD_GI::GetDataWeapons() { return _data_wps; }
const TArray<FDataWave*>& UHD_GI::GetDataWaves() { return _data_waves; }
FDataGame* UHD_GI::GetDataGame() { return _data_game; }
FDataHero* UHD_GI::GetDataHero() { return _data_hero; }