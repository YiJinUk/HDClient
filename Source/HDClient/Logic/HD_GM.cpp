// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GM.h"
#include "HD_GI.h"
#include "HD_PC.h"
#include "HD_FunctionLibrary.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Friend/MagicStone/HD_MagicStone.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "Actor/Unit/Monster/HD_Monster.h"

#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Actor/Object/Projectile/HD_Projectile.h"
#include "Actor/Object/HD_Spline.h"
#include "Actor/Object/HD_Portal.h"

#include "Manager/HD_Manager_Pool.h"
#include "Manager/HD_Manager_Battle.h"
#include "Manager/HD_Manager_Weapon.h"
#include "Manager/HD_Manager_FX.h"
#include "Manager/HD_Manager_Skill.h"
#include "Manager/HD_Manager_Buff.h"
#include "Manager/HD_Manager_Reward.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

DECLARE_STATS_GROUP(TEXT("HD_Tick"), STATGROUP_HD_Tick, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("HD_Tick_Cycle"), STAT_HD_Tick_Cycle, STATGROUP_HD_Tick);

AHD_GM::AHD_GM()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AHD_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	_pc = Cast<AHD_PC>(NewPlayer);
	_is_call_PostLogin = true;
	if (_is_call_BeginPlay && _is_call_PostLogin)
		GMPostInit();
}
void AHD_GM::BeginPlay()
{
	Super::BeginPlay();
	_is_call_BeginPlay = true;
	if (_is_call_BeginPlay && _is_call_PostLogin)
		GMPostInit();
}
void AHD_GM::GMPostInit()
{
	UWorld* wld = GetWorld();
	_gi = wld->GetGameInstance<UHD_GI>();
	_gi->GIPostInit();

	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*월드에 영웅 가져오기*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Hero::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _hero = Cast<AHD_Hero>(arr_found_actor[0]); }

	//마법석 생성
	_ms = GetWorld()->SpawnActor<AHD_MagicStone>(_gi->GetDataMS()->GetClassMS(), s_param); // 풀링 매니저
	_ms->UnitPostInit(_pc, EUnitClassType::MS);
	_ms->MSPostInit(_gi->GetDataMS(), _gi->GetDataGame()->GetMSSpawnLocation());

	/*월드에 존재하는 스플라인액터를 통해 스플라인컴포넌트 가져오기*/
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Spline::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) 
	{
		AHD_Spline* spline = Cast<AHD_Spline>(arr_found_actor[0]); 
		_spline_component = spline->GetSplineComponent();
	}

	/*매니지클래스 생성후 초기화*/
	_manager_pool = wld->SpawnActor<AHD_Manager_Pool>(s_param);
	_manager_battle = wld->SpawnActor<AHD_Manager_Battle>(s_param);
	_manager_wp = wld->SpawnActor<AHD_Manager_Weapon>(s_param);
	_manager_fx = wld->SpawnActor<AHD_Manager_FX>(s_param);
	_manager_sk = wld->SpawnActor<AHD_Manager_Skill>(s_param);
	_manager_bf = wld->SpawnActor<AHD_Manager_Buff>(s_param);
	_manager_reward = wld->SpawnActor<AHD_Manager_Reward>(s_param);

	_manager_pool->PoolPostInit(_gi, this, _pc);
	_manager_battle->BattlePostInit(_pc);
	_manager_fx->FXPostInit(_gi);
	_manager_sk->SKPostInit(this, _manager_bf);
	_manager_bf->BFPostInit(this, _gi);
	_manager_reward->RewardPostInit(_gi, this, _manager_pool);

	/*영웅 동료 마법석 초기화*/
	_hero->UnitPostInit(_pc, EUnitClassType::HERO);
	_hero->HeroPostInit(_gi->GetDataHero());

	/*웨이브정보 초기화*/
	_info_wave.rewards_base.Add(ERewardType::GOLD);

	ChangeCPANStartByCode("CPAN00001");

	/*플레이어 초기화*/
	ChangeWeaponStartByCode("WP00101");

	_pc->PCPostInit();
}
void AHD_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAttackBasicStatus"), true);
	//if (enumPtr)
	//{
	//	if (_spawned_monsters.Num() >= 1)
	//	{
	//		FString str_enum = enumPtr->GetNameStringByIndex((int32)_spawned_monsters[0]->GetInfoMOB().atk_basic_status);
	//		UHD_FunctionLibrary::GPrintString(10, 1, "MONSTER : " + str_enum, FColor::Red);
	//		UHD_FunctionLibrary::GPrintString(11, 1, "MONSTER : " + FString::FromInt(_spawned_monsters[0]->GetInfoMOB().as_delay), FColor::Red);
	//	}
	//	if (_hero)
	//	{

	//		FString str_enum = enumPtr->GetNameStringByIndex((int32)_hero->GetInfoHero().atk_basic_status);
	//		UHD_FunctionLibrary::GPrintString(1, 1, "HERO : " + str_enum);
	//		UHD_FunctionLibrary::GPrintString(2, 1, "HERO : " + FString::FromInt(_hero->GetInfoHero().as_delay));
	//		//UHD_FunctionLibrary::GSaveLog("Tick.Hero ASDelay : "+ FString::FromInt(_hero->GetInfoHero().as_delay)+ " // Hero Status : " + str_enum, "Hero Attack.txt");
	//		//UHD_FunctionLibrary::GSaveLog("Tick.Hero Status : " + str_enum, "Hero Attack.txt");
	//	}
	//	if (_cpan)
	//	{

	//		FString str_enum = enumPtr->GetNameStringByIndex((int32)_cpan->GetInfoCPAN().atk_basic_status);
	//		UHD_FunctionLibrary::GPrintString(21, 1, "COMPANION : " + str_enum, FColor::Turquoise);
	//		UHD_FunctionLibrary::GPrintString(22, 1, "COMPANION : " + FString::FromInt(_hero->GetInfoHero().as_delay),FColor::Turquoise);
	//		UHD_FunctionLibrary::GPrintString(220, 1, "Test Int : " + FString::FromInt(0x5f3759df));
	//		UHD_FunctionLibrary::GPrintString(221, 1, "Test Float : " + FString::SanitizeFloat(0x5f3759df));
	//	}
	//}

	UHD_FunctionLibrary::GPrintString(30, 1, "Gold : " + FString::FromInt(_info_player.gold));
	UHD_FunctionLibrary::GPrintString(40, 1, "WaveType : " + FString::FromInt((uint8)_info_wave.wave_type));

	if (_info_wld.wld_status != EWorldStatus::HOME)
		++_info_wld.tick_total;

	switch (_info_wld.wld_status)
	{
	case EWorldStatus::HOME:
		break;
	case EWorldStatus::WAVE_STANDBY:
		break;
	case EWorldStatus::WAVE_PLAY:
		_info_wld.tick_round += _info_wld.tick_unit_by_1frame;
		_info_wave.spawn_enemy_interval_current += _info_wld.tick_unit_by_1frame;

		TickCheckSpawnEnemy();
		TickMOBMoveAndAttack(DeltaTime);
		TickPROJMoveAndAttack(DeltaTime);

		TickHeroHealArmor();

		TickFriendReduceCooldown();
		TickFriendReduceAS();
		TickFriendAttack();

		TickCheckWaveEnd();

		_manager_bf->BFTick();
		break;
	default:
		break;
	}

	if(_manager_pool)
		_manager_pool->PoolTick();
}
void AHD_GM::TickCheckSpawnEnemy()
{
	/*인터벌을 체크합니다*/
	if (_info_wave.spawn_enemy_interval_current >= _info_wave.spawn_enemy_interval_max)
	{
		/*적 생성*/
		_info_wave.spawn_enemy_interval_current -= _info_wave.spawn_enemy_interval_max;
		for (FDataWaveSpawnEnemy& s_wave_spawn_enemy : _wave_spawn_enemies)
		{
			if (s_wave_spawn_enemy.count >= 1)
			{
				MOBSpawn(s_wave_spawn_enemy.code);
				--s_wave_spawn_enemy.count;
				break;
			}
		}
	}
}
void AHD_GM::TickMOBMoveAndAttack(const float f_delta_time)
{
	if (_spawned_monsters.Num() <= 0) return;
	AHD_Monster* mob = nullptr;
	for (int32 i = _spawned_monsters.Num() - 1; i >= 0; --i)
	{
		mob = _spawned_monsters[i];
		if (mob->GetInfoMOB().is_can_move >= 0)
		{
			mob->MOBMove(f_delta_time,
				_spline_component->GetLocationAtDistanceAlongSpline(mob->GetInfoMOB().lane_dist, ESplineCoordinateSpace::World),
				_spline_component->GetRotationAtDistanceAlongSpline(mob->GetInfoMOB().lane_dist, ESplineCoordinateSpace::World)
			);
		}
		


		mob->MOBUpdateAS(_info_wld.tick_unit_by_1frame);
		if (mob->GetInfoMOB().atk_basic_status == EAttackBasicStatus::DETECT)
		{
			mob->MOBAttackBasicStart(_hero);
		}
	}
}
void AHD_GM::TickPROJMoveAndAttack(const float f_delta_time)
{
	//SCOPE_CYCLE_COUNTER(STAT_HD_Tick_Cycle);
	if (_spawned_projs.Num() <= 0) return;
	for (auto proj = _spawned_projs.CreateConstIterator(); proj; ++proj)
	{
		(*proj)->PROJMoveAndAttack(f_delta_time);
	}
}
void AHD_GM::TickHeroHealArmor()
{
	_hero->HeroUpdateHealArmor(_info_wld.tick_unit_by_1frame);
}
void AHD_GM::TickFriendReduceCooldown()
{
	_hero->HeroUpdateReduceCooldown(_info_wld.tick_unit_by_1frame);
	_cpan->CPANUpdateReduceCooldown(_info_wld.tick_unit_by_1frame);
	_ms->MSUpdateReduceCooldown(_info_wld.tick_unit_by_1frame);
}
void AHD_GM::TickFriendReduceAS()
{
	_hero->HeroUpdateAS(_info_wld.tick_unit_by_1frame);
	_cpan->CPANUpdateAS(_info_wld.tick_unit_by_1frame);
}
void AHD_GM::TickFriendAttack()
{
	if (_hero->GetInfoHero().atk_sk_status == EAttackSkillStatus::DETECT && _hero->GetInfoHero().atk_basic_status != EAttackBasicStatus::TRY)
	{
		_hero->HeroAttackSkillStart();
	}
	else if (_hero->GetInfoHero().atk_sk_status == EAttackSkillStatus::COOLDOWN && _hero->GetInfoHero().atk_basic_status == EAttackBasicStatus::DETECT)
	{
		_hero->HeroAttackBasicStart();
	}

	if (_cpan->GetInfoCPAN().atk_sk_status == EAttackSkillStatus::DETECT && _cpan->GetInfoCPAN().atk_basic_status != EAttackBasicStatus::TRY)
	{
		_cpan->CPANAttackSkillStart();
	}
	else if (_cpan->GetInfoCPAN().atk_sk_status == EAttackSkillStatus::COOLDOWN && _cpan->GetInfoCPAN().atk_basic_status == EAttackBasicStatus::DETECT)
	{
		_cpan->CPANAttackBasicStart(FindMOBFirstByV2(_cpan->GetActorLocation2D()));
	}

	if (_ms->GetInfoMS().atk_sk_status == EAttackSkillStatus::DETECT)
	{
		_ms->MSAttackSkillStart();
	}
}
void AHD_GM::TickCheckWaveEnd()
{
	if (_spawned_monsters.Num() >= 1) return;
	for (FDataWaveSpawnEnemy& s_wave_spawn_enemy : _wave_spawn_enemies)
	{
		if (s_wave_spawn_enemy.count >= 1)
		{
			return;
		}
	}

	WaveEnd();
}

void AHD_GM::WorldStart()
{
	/*집에서 세계로 처음 진입했습니다. 초기화를 진행합니다*/
	/*세계,웨이브정보구조체를 초기화합니다*/
	_info_wld.InitInfoWorld();

	/*웨이브에 등장할 적데이터 복제하기*/
	_info_wld.round_total = 0;
	WaveReadNextWave();

	/*웨이브정보 초기화*/
	_info_wave.spawn_enemy_interval_max =_gi->GetDataGame()->GetWaveEnemySpawnInterval();

	/*영웅 마법석 초기화*/
	_hero->HeroInit(_gi->GetDataHero());
	_ms->MSInit(_gi->GetDataMS());

	/*모든 과정을 거쳤으면 world_status를 변경합니다*/
	//_info_wld.wld_status = EWorldStatus::WAVE_STANDBY;
	/*Debug*/
	if (_spline_component)
	{
		for (int32 i = 1, i_len = _spline_component->GetSplineLength(); i < i_len; ++i)
		{
			DrawDebugLine(GetWorld(), 
				_spline_component->GetLocationAtDistanceAlongSpline(i, ESplineCoordinateSpace::World),
				_spline_component->GetLocationAtDistanceAlongSpline(i + 1, ESplineCoordinateSpace::World),
				FColor::Red, false, 10000.f, 0, 3.f);
		}
	}

	_pc->PCWorldStart();
	WaveNextAndStart(_info_wave.reward_select);
}
void AHD_GM::WorldGameOver()
{
	_info_wld.wld_status = EWorldStatus::WORLD_GAME_OVER;
	_pc->PCWorldGameOver();
}
void AHD_GM::WorldReturnToHome()
{
	if (_spawned_monsters.Num() >= 1)
	{
		AHD_Monster* mob = nullptr;
		for (int32 i = _spawned_monsters.Num() - 1; i >= 0; --i)
		{
			mob = _spawned_monsters[i];
			mob->MOBToHomeInit();
			mob->UnitDeath();
		}
		//_spawned_monsters.Empty(50);
	}
	PROJAllPoolIn();
	_hero->HeroToHomeInit();

	_info_wld.wld_status = EWorldStatus::HOME;
	_info_wld.round_total = 1;
	_info_wld.round_stage = 0;
	_info_wld.round_wave = 0;
	_info_wld.tick_round = 0;
	_info_wld.tick_total = 0;

	_pc->PCUIReturnToHome();
}
void AHD_GM::WorldClear()
{
	_pc->PCWorldClear();
}
void AHD_GM::WorldClearToHome()
{
	_pc->PCUIWorldClearToHome();
}

void AHD_GM::WaveNextAndStart(const ERewardType e_reward_type_select)
{
	_info_wave.spawn_enemy_interval_current = 0;
	_info_wave.reward_select = e_reward_type_select;

	/*포탈 초기화*/
	for (AHD_Portal* portal_open : _open_portals)
	{
		_manager_pool->PoolInPortal(portal_open);
	}
	_open_portals.Empty(6);

	_manager_reward->RewardInit();

	_info_wld.wld_status = EWorldStatus::WAVE_PLAY;
	_pc->PCWaveNextAndStart(_info_wld.round_stage, _info_wld.round_wave, _info_wave.wave_type);
}
void AHD_GM::WaveEnd()
{
	_hero->HeroWaveEndInit();
	_cpan->CPANWaveEndInit();
	PROJAllPoolIn();

	_info_wld.wld_status = EWorldStatus::WAVE_END;

	//웨이브가 종료되면 바로 다음웨이브데이터를 가져옵니다
	WaveReadNextWave();

	/*현재 클리어한 웨이브가 마지막웨이브라면 클리어UI를 띄우고 아니라면 다음 웨이브를 위한 준비를 합니다*/
	if (_info_wave.wave_type == EWaveType::LAST_CLEAR)
	{
		WorldClear();
	}
	else
	{
		_manager_reward->RewardWaveEnd();

		_pc->PCWaveEnd();
	}
}
void AHD_GM::WaveOpenPortal()
{
	AHD_Portal* portal_open = _manager_pool->PoolGetPortal();
	portal_open->PortalInit(ERewardType::GOLD, FVector(0.f));
	_open_portals.Add(portal_open);
}
void AHD_GM::WaveReadNextWave()
{
	++_info_wld.round_total;
	const TArray<FDataWave*>& arr_data_waves = _gi->GetDataWaves();
	if (arr_data_waves.Num() < _info_wld.round_total)
	{
		/*마지막웨이브*/
		_info_wave.wave_type = EWaveType::LAST_CLEAR;
	}
	else
	{
		const FDataWave* s_wave = arr_data_waves[_info_wld.round_total - 1];
		_wave_spawn_enemies = s_wave->GetSpawnEnemies();
		_info_wld.round_stage = s_wave->GetStageRound();
		_info_wld.round_wave = s_wave->GetWaveRound();
		_info_wave.wave_type = s_wave->GetWaveType();
	}

}

void AHD_GM::ChangeHeroPROJVelocity(const FVector& v_loc)
{
	_hero->HeroSetPROJVelocity(v_loc);
}

void AHD_GM::MOBSpawn(const FString& str_code_mob)
{
	AHD_Monster* mob_spawn = _manager_pool->PoolGetMOB(str_code_mob);
	if (!mob_spawn) return;

	mob_spawn->MOBInit(GidGenerate(), _gi->GetDataGame()->GetEnemySpawnLocation());

	_spawned_monsters.Add(mob_spawn);
}
void AHD_GM::MOBDeath(AHD_Monster* mob_death)
{
	MOBRemoveSpawnedById(mob_death->GetInfoMOB().gid);
	_manager_pool->PoolMOBDeath(mob_death);
}
void AHD_GM::MOBRemoveSpawnedById(const int64 i_id_mob)
{
	if (_spawned_monsters.Num() <= 0) return;
	AHD_Monster* mob = nullptr;
	for (int32 i = 0, i_len = _spawned_monsters.Num(); i < i_len; ++i)
	{
		mob = _spawned_monsters[i];
		if (mob && mob->GetInfoMOB().gid == i_id_mob)
		{
			_spawned_monsters.RemoveAtSwap(i);
			return;
		}
	}
}
AHD_Monster* AHD_GM::FindMOBFirstByV2(const FVector2D& v2_loc_center, const int64 i_id_mob_except)
{
	AHD_Monster* mob_target_candidate = nullptr;
	//개미의 이동거리. 가장 많이 이동한 개미가 후보입니다
	int16 i_travel_dist_candidate = 0;
	int16 i_travel_dist_total_tmp = 0;

	for (AHD_Monster* mob_spawned : _spawned_monsters)
	{
		/*개미가 유효한지*/
		if (mob_spawned && mob_spawned->GetInfoUnit().is_hit_valid && mob_spawned->GetInfoMOB().gid != i_id_mob_except)
		{
			/*개미의 이동거리가 타겟후보보다 더 이동했는지*/
			i_travel_dist_total_tmp = mob_spawned->GetInfoMOB().lane_dist;
			if (i_travel_dist_total_tmp > i_travel_dist_candidate)
			{
				i_travel_dist_candidate = i_travel_dist_total_tmp;
				mob_target_candidate = mob_spawned;
			}
		}
	}

	return mob_target_candidate;
}
AHD_Monster* AHD_GM::FindMOBNearByV2(const FVector2D& v2_loc_center, const int64 i_id_mob_except)
{
	AHD_Monster* mob_target_candidate = nullptr;
	//나비와 개미의 거리. 거리간격이 좁을수록 후보입니다
	int16 i_dist_candidate = 30000;
	int16 i_dist_candidate_tmp = 0;

	for (AHD_Monster* mob_spawned : _spawned_monsters)
	{
		/*개미가 유효한지*/
		if (mob_spawned && mob_spawned->GetInfoUnit().is_hit_valid && mob_spawned->GetInfoMOB().gid != i_id_mob_except)
		{
			/*가장 가까운 개미인지*/
			i_dist_candidate_tmp = UHD_FunctionLibrary::GetDistance2DByVector(v2_loc_center, mob_spawned->GetActorLocation2D());

			if (i_dist_candidate_tmp < i_dist_candidate)
			{
				i_dist_candidate = i_dist_candidate_tmp;
				mob_target_candidate = mob_spawned;
			}
		}
	}

	return mob_target_candidate;
}

void AHD_GM::ChangeCPANStartByCode(const FString& str_code_cpan)
{
	//@변경 가능한지 검증단계 필요

	/*장착중인 무기 풀인*/
	_manager_pool->PoolInCPAN(_cpan);

	/*새로운 무기 장착*/
	_cpan = _manager_pool->PoolGetCPAN(str_code_cpan);
	if (!_cpan) return;

	_cpan->CPANInit(_gi->GetDataGame()->GetCPANSpawnLocation());
}

void AHD_GM::ChangeWeaponStartByCode(const FString& str_code_wp)
{
	//@변경 가능한지 검증단계 필요
	
	/*장착중인 무기 풀인*/
	_manager_pool->PoolInWeapon(_hero->GetInfoHero().wp_equip);

	/*새로운 무기 장착*/
	AHD_Weapon* wp = _manager_pool->PoolOutWeaponByCode(str_code_wp);
	if (!wp) return;
	
	wp->WPInit(_hero->GetSkeletalMesh());

	/*영웅의 스탯을 변경합니다*/
	_hero->HeroChangeWeapon(wp);
}

void AHD_GM::PROJSpawn(const FString& str_code_proj, const FVector& v_loc_spawn, AHD_Unit* unit_owner, AHD_Unit* unit_target, const FVector2D& v2_dest)
{
	if (_info_wld.wld_status != EWorldStatus::WAVE_PLAY) return;

	FDataProjectile* s_data_proj = _gi->FindDataPROJByCode(str_code_proj);
	AHD_Projectile* proj = _manager_pool->PoolGetPROJ(s_data_proj);

	proj->PROJInit(GidGenerate(), s_data_proj, v_loc_spawn, unit_owner, unit_target, v2_dest);

	_spawned_projs.Add(proj);
}
void AHD_GM::PROJFinish(AHD_Projectile* proj)
{
	if (!proj) return;
	_manager_fx->VFXStart(proj->GetInfoPROJ().vfx, proj->GetActorLocation());
	_manager_pool->PoolInPROJ(proj);
	_spawned_projs.Remove(proj);
}
void AHD_GM::PROJAllPoolIn()
{
	if (_spawned_projs.Num() >= 1)
	{
		for (auto proj = _spawned_projs.CreateConstIterator(); proj; ++proj)
		{
			//(*proj)->PROJGameOverInit();
			_manager_pool->PoolInPROJ(*proj);
		}
		_spawned_projs.Empty(50);
	}
}

void AHD_GM::PlayerSetStat(const EPlayerStatType e_player_stat_type, const int32 i_value)
{
	switch (e_player_stat_type)
	{
	case EPlayerStatType::GOLD:
		_info_player.gold += i_value;
		break;
	default:
		break;
	}
}

void AHD_GM::RewardSelectSend(const ERewardType e_reward_type, const ERewardBy e_reward_by) { _manager_reward->RewardSelectStart(e_reward_type, e_reward_by); }

void AHD_GM::BattleSend(AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type) { _manager_battle->BattleRecv(atk, def, i_dmg, e_atk_type); }

const int64 AHD_GM::GidGenerate() { return ++_gid_generator; }
AHD_Hero* AHD_GM::GetHero() { return _hero; }
AHD_Manager_Skill* AHD_GM::GetManagerSK() { return _manager_sk; }
AHD_Manager_Reward* AHD_GM::GetManagerReward() { return _manager_reward; }
const FInfoWave& AHD_GM::GetInfoWave() { return _info_wave; }