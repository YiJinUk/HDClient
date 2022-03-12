// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GI.h"

#include "Kismet/KismetMathLibrary.h"

UHD_GI::UHD_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Game.HDDT_Game"));
	if (DT_GAME.Succeeded()) { _dt_game = DT_GAME.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVE(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Wave.HDDT_Wave"));
	if (DT_WAVE.Succeeded()) { _dt_wave = DT_WAVE.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HERO(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Hero.HDDT_Hero"));
	if (DT_HERO.Succeeded()) { _dt_hero = DT_HERO.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CPAN(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Companion.HDDT_Companion"));
	if (DT_CPAN.Succeeded()) { _dt_cpan = DT_CPAN.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MS(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_MagicStone.HDDT_MagicStone"));
	if (DT_MS.Succeeded()) { _dt_ms = DT_MS.Object; }
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
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BF(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Buff.HDDT_Buff"));
	if (DT_BF.Succeeded()) { _dt_bf = DT_BF.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_REWARD(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Reward.HDDT_Reward"));
	if (DT_REWARD.Succeeded()) { _dt_reward = DT_REWARD.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SPEC(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Spec.HDDT_Spec"));
	if (DT_SPEC.Succeeded()) { _dt_spec = DT_SPEC.Object; }
}
void UHD_GI::GIPostInit()
{
	_dt_weapon->GetAllRows("0", _data_wps);
	_dt_cpan->GetAllRows("0", _data_cpans);
	_dt_wave->GetAllRows("0", _data_waves);
	_dt_spec->GetAllRows("0", _data_specs);
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
	_data_hero = _dt_hero->FindRow<FDataHero>("HERO00001", "0");
	_data_ms = _dt_ms->FindRow<FDataMS>("MS00001", "0");

	TArray<FDataReward*> arr_data_reward;
	_dt_reward->GetAllRows("0", arr_data_reward);
	for (FDataReward* s_data_reward : arr_data_reward)
	{
		_data_rewards.Add(s_data_reward->GetRewardType(), s_data_reward);
	}
}

int32 UHD_GI::GetRandomByInt(const int32 i_min, const int32 i_max)
{
	return UKismetMathLibrary::RandomInteger(i_max - i_min + 1) + i_min;
}

FDataMonster* UHD_GI::FindDataMOBByCode(const FString& str_code_mob) { return _dt_mob->FindRow<FDataMonster>(*str_code_mob, "0"); }
FDataCPAN* UHD_GI::FindDataCPANByCode(const FString& str_code_cpan) { return _dt_cpan->FindRow<FDataCPAN>(*str_code_cpan, "0"); }
FDataProjectile* UHD_GI::FindDataPROJByCode(const FString& str_code_proj) { return _dt_proj->FindRow<FDataProjectile>(*str_code_proj, "0"); }
FDataVFX* UHD_GI::FindDataVFXByCode(const FString& str_code_vfx) { return _dt_vfx->FindRow<FDataVFX>(*str_code_vfx, "0"); }
FDataSkill* UHD_GI::FindDataSKByCode(const FString& str_code_sk) { return _dt_sk->FindRow<FDataSkill>(*str_code_sk, "0"); }
FDataBuff* UHD_GI::FindDataBFByCode(const FString& str_code_bf) { return _dt_bf->FindRow<FDataBuff>(*str_code_bf, "0"); }
FDataReward* UHD_GI::FindDataRewardByType(const ERewardType e_reward_type) { return *(_data_rewards.Find(e_reward_type)); }
FDataSPEC* UHD_GI::FindDataSPECByCode(const FString& str_code_power) { return _dt_spec->FindRow<FDataSPEC>(*str_code_power, "0"); }

const TArray<FDataWeapon*>& UHD_GI::GetDataWeapons() { return _data_wps; }
const TArray<FDataCPAN*>& UHD_GI::GetDataCPANs() { return _data_cpans; }
const TArray<FDataWave*>& UHD_GI::GetDataWaves() { return _data_waves; }
const TMap<ERewardType, FDataReward*>& UHD_GI::GetDataRewards() { return _data_rewards; }
const TArray<FDataSPEC*>& UHD_GI::GetDataSPECs() { return _data_specs; }
FDataGame* UHD_GI::GetDataGame() { return _data_game; }
FDataHero* UHD_GI::GetDataHero() { return _data_hero; }
FDataMS* UHD_GI::GetDataMS() { return _data_ms; }