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

#include "Manager/HD_Manager_Pool.h"
#include "Manager/HD_Manager_Battle.h"
#include "Manager/HD_Manager_Weapon.h"
#include "Manager/HD_Manager_FX.h"

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
	
	/*월드에 존재하는 영웅, 동료, 마법석액터 가져오기*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Hero::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _hero = Cast<AHD_Hero>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_MagicStone::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _ms = Cast<AHD_MagicStone>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Companion::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _cpan = Cast<AHD_Companion>(arr_found_actor[0]); }

	/*월드에 존재하는 스플라인액터를 통해 스플라인컴포넌트 가져오기*/
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Spline::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) 
	{
		AHD_Spline* spline = Cast<AHD_Spline>(arr_found_actor[0]); 
		_spline_component = spline->GetSplineComponent();
	}

	/*매니지클래스 생성후 초기화*/
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<AHD_Manager_Pool>(s_param);
	_manager_battle = wld->SpawnActor<AHD_Manager_Battle>(s_param);
	_manager_wp = wld->SpawnActor<AHD_Manager_Weapon>(s_param);
	_manager_fx = wld->SpawnActor<AHD_Manager_FX>(s_param);

	_manager_pool->PoolPostInit(_gi, this);
	_manager_battle->BattlePostInit();
	_manager_fx->FXPostInit(_gi);

	/*영웅 동료 마법석 초기화*/
	_hero->UnitPostInit(EUnitClassType::HERO);
	_hero->HeroPostInit(_pc, _gi->GetDataHero());

	/*플레이어 초기화*/
	ChangeWeaponStartByCode("WP00101");

	_pc->PCPostInit();
}
void AHD_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAttackBasicStatus"), true);
	if (enumPtr)
	{
		if (_spawned_monsters.Num() >= 1)
		{
			FString str_enum = enumPtr->GetNameStringByIndex((int32)_spawned_monsters[0]->GetInfoMOB().atk_basic_status);
			UHD_FunctionLibrary::GPrintString(10, 1, str_enum, FColor::Red);
			UHD_FunctionLibrary::GPrintString(11, 1, FString::FromInt(_spawned_monsters[0]->GetInfoMOB().as_delay), FColor::Red);
		}
		if (_hero)
		{

			FString str_enum = enumPtr->GetNameStringByIndex((int32)_hero->GetInfoHero().atk_basic_status);
			UHD_FunctionLibrary::GPrintString(1, 1, str_enum);
			UHD_FunctionLibrary::GPrintString(2, 1, FString::FromInt(_hero->GetInfoHero().as_delay));
			//UHD_FunctionLibrary::GSaveLog("Tick.Hero ASDelay : "+ FString::FromInt(_hero->GetInfoHero().as_delay)+ " // Hero Status : " + str_enum, "Hero Attack.txt");
			//UHD_FunctionLibrary::GSaveLog("Tick.Hero Status : " + str_enum, "Hero Attack.txt");
		}
	}

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
		TickEnemyMoveAndAttack(DeltaTime);
		TickPROJMoveAndAttack(DeltaTime);
		TickHeroHealArmor();
		TickHeroAttack();
		TickCheckWaveEnd();
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
void AHD_GM::TickEnemyMoveAndAttack(const float f_delta_time)
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
		

		if (mob->MOBUpdateAS(_info_wld.tick_unit_by_1frame))
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
void AHD_GM::TickFriendMP()
{

}
void AHD_GM::TickHeroHealArmor()
{
	_hero->HeroUpdateHealArmor(_info_wld.tick_unit_by_1frame);
}
void AHD_GM::TickHeroAttack()
{
	/*공속 업데이트 및 공격가능여부*/
	if (_hero->HeroUpdateAS(_info_wld.tick_unit_by_1frame))
	{
		/*타겟을 찾고 영웅에게 넘겨줌*/
		_hero->HeroAttackBasicStart(FindMOBFirstByV2(_hero->GetActorLocation2D()));
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
	_info_wave.InitInfoWave();

	/*웨이브에 등장할 적데이터 복제하기*/
	_info_wld.round_total = 1;
	const TArray<FDataWave*>& arr_data_waves = _gi->GetDataWaves();
	const FDataWave* s_wave = arr_data_waves[_info_wld.round_total - 1];
	_wave_spawn_enemies = s_wave->GetSpawnEnemies();
	_info_wld.round_stage = s_wave->GetStageRound();
	_info_wld.round_wave = s_wave->GetWaveRound();

	/*웨이브정보 초기화*/
	_info_wave.spawn_enemy_interval_max =_gi->GetDataGame()->GetWaveEnemySpawnInterval();

	/*영웅 초기화*/
	_hero->HeroInit();

	/*모든 과정을 거쳤으면 world_status를 변경합니다*/
	_info_wld.wld_status = EWorldStatus::WAVE_STANDBY;

	/*Debug*/
	if (_spline_component)
	{
		for (int32 i = 1, i_len = _spline_component->GetSplineLength(); i < i_len; ++i)
		{
			DrawDebugLine(GetWorld(), 
				_spline_component->GetLocationAtDistanceAlongSpline(i, ESplineCoordinateSpace::World),
				_spline_component->GetLocationAtDistanceAlongSpline(i + 1, ESplineCoordinateSpace::World),
				FColor::Red, false, 10000.f, (uint8)'\000', 3.f);
		}
	}
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
	if (_spawned_projs.Num() >= 1)
	{
		for (auto proj = _spawned_projs.CreateConstIterator(); proj; ++proj)
		{
			(*proj)->PROJGameOverInit();
			_manager_pool->PoolInPROJ(*proj);
		}
		_spawned_projs.Empty(50);
	}
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

void AHD_GM::WaveStart()
{
	/*모든 과정을 거쳤으면 world_status를 변경합니다*/
	_info_wld.wld_status = EWorldStatus::WAVE_PLAY;

	_pc->PCWaveStart();
}
void AHD_GM::WaveEnd()
{
	_info_wld.wld_status = EWorldStatus::WAVE_END;
	_hero->HeroWaveEndInit();
	_pc->PCWaveEnd();
}
void AHD_GM::WaveNext()
{
	/*웨이브에 등장할 적데이터 복제하기*/
	++_info_wld.round_total;
	const TArray<FDataWave*>& arr_data_waves = _gi->GetDataWaves();
	_info_wld.wld_status = EWorldStatus::WAVE_STANDBY;

	/*현재 웨이브가 마지막 웨이브인지*/
	if (arr_data_waves.Num() < _info_wld.round_total)
	{
		/*모든 웨이브 클리어 게임승리*/
		WorldClear();
	}
	else
	{
		/*다음 웨이브정보 불러오기*/
		const FDataWave* s_wave = arr_data_waves[_info_wld.round_total - 1];
		_wave_spawn_enemies = s_wave->GetSpawnEnemies();
		_info_wld.round_stage = s_wave->GetStageRound();
		_info_wld.round_wave = s_wave->GetWaveRound();

		_pc->PCWaveNext(_info_wld.round_stage, _info_wld.round_wave);
	}
}

void AHD_GM::MOBSpawn(const FString& str_code_mob)
{
	AHD_Monster* mob_spawn = _manager_pool->PoolGetMOB(str_code_mob);
	if (!mob_spawn) return;

	mob_spawn->MOBInit(IdGenerate(), _gi->GetDataGame()->GetEnemySpawnLocation());

	_spawned_monsters.Add(mob_spawn);
}
void AHD_GM::MOBDeath(AHD_Monster* mob_death)
{
	MOBRemoveSpawnedById(mob_death->GetInfoMOB().id);
	_manager_pool->PoolMOBDeath(mob_death);
}
void AHD_GM::MOBRemoveSpawnedById(const int64 i_id_mob)
{
	if (_spawned_monsters.Num() <= 0) return;
	AHD_Monster* mob = nullptr;
	for (int32 i = 0, i_len = _spawned_monsters.Num(); i < i_len; ++i)
	{
		mob = _spawned_monsters[i];
		if (mob && mob->GetInfoMOB().id == i_id_mob)
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
		if (mob_spawned && mob_spawned->GetInfoUnit().is_hit_valid && mob_spawned->GetInfoMOB().id != i_id_mob_except)
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
		if (mob_spawned && mob_spawned->GetInfoUnit().is_hit_valid && mob_spawned->GetInfoMOB().id != i_id_mob_except)
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

	proj->PROJInit(IdGenerate(), s_data_proj, v_loc_spawn, unit_owner, unit_target, v2_dest);

	_spawned_projs.Add(proj);
}
void AHD_GM::PROJFinish(AHD_Projectile* proj)
{
	if (!proj) return;
	_manager_fx->VFXStart(proj->GetInfoPROJ().vfx, proj->GetActorLocation());
	_manager_pool->PoolInPROJ(proj);
	_spawned_projs.Remove(proj);
}
void AHD_GM::BattleSend(AHD_Unit* atk, AHD_Unit* def, const int32 i_dmg, const EAttackType e_atk_type) { _manager_battle->BattleRecv(atk, def, i_dmg, e_atk_type); }

const int64 AHD_GM::IdGenerate() { return ++_id_generator; }
AHD_Hero* AHD_GM::GetHero() { return _hero; }