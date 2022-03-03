// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GM.h"
#include "HD_GI.h"
#include "HD_PC.h"
#include "HD_FunctionLibrary.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Friend/MagicStone/HD_MagicStone.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"

#include "Actor/Object/Weapon/HD_Weapon.h"
#include "Actor/Object/HD_Spline.h"

#include "Manager/HD_Manager_Pool.h"
#include "Manager/HD_Manager_Weapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

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
	
	/*���忡 �����ϴ� ����, ����, ���������� ��������*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Hero::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _hero = Cast<AHD_Hero>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_MagicStone::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _ms = Cast<AHD_MagicStone>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Companion::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _cpan = Cast<AHD_Companion>(arr_found_actor[0]); }

	/*���忡 �����ϴ� ���ö��ξ��͸� ���� ���ö���������Ʈ ��������*/
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Spline::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) 
	{
		AHD_Spline* spline = Cast<AHD_Spline>(arr_found_actor[0]); 
		_spline_component = spline->GetSplineComponent();
	}

	/*�Ŵ���Ŭ���� ������ �ʱ�ȭ*/
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<AHD_Manager_Pool>(s_param);
	_manager_wp = wld->SpawnActor<AHD_Manager_Weapon>(s_param);

	_manager_pool->PoolPostInit(_gi);

	/*���� ���� ������ �ʱ�ȭ*/
	_hero->UnitPostInit();

	/*�÷��̾� �ʱ�ȭ*/
	ChangeWeaponStartByCode("WP00101");

	_pc->PCPostInit();
}
void AHD_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_hero)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EHeroAttackBasicStatus"), true);
		if (enumPtr)
		{
			FString str_enum = enumPtr->GetNameStringByIndex((int32)_hero->GetInfoHero().atk_basic_status);
			UHD_FunctionLibrary::GPrintString(1, 1, str_enum);
		}

		UHD_FunctionLibrary::GPrintString(2, 1, FString::FromInt(_hero->GetInfoHero().as_delay));
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
		TickEnemyMove(DeltaTime);
		TickHeroAttack();
		break;
	default:
		break;
	}
}
void AHD_GM::TickCheckSpawnEnemy()
{
	/*���͹��� üũ�մϴ�*/
	if (_info_wave.spawn_enemy_interval_current >= _info_wave.spawn_enemy_interval_max)
	{
		/*�� ����*/
		_info_wave.spawn_enemy_interval_current -= _info_wave.spawn_enemy_interval_max;
		for (FDataWaveSpawnEnemy& s_wave_spawn_enemy : _wave_spawn_enemies)
		{
			if (s_wave_spawn_enemy.count >= 1)
			{
				EnemySpawn(s_wave_spawn_enemy.code);
				--s_wave_spawn_enemy.count;
				break;
			}
		}
	}
}
void AHD_GM::TickEnemyMove(const float f_delta_time)
{
	if (_spawned_enemies.Num() <= 0) return;
	for (AHD_Enemy* enemy : _spawned_enemies)
	{
		enemy->EnemyMove(f_delta_time,
			_spline_component->GetLocationAtDistanceAlongSpline(enemy->GetInfoEnemy().lane_dist, ESplineCoordinateSpace::World),
			_spline_component->GetRotationAtDistanceAlongSpline(enemy->GetInfoEnemy().lane_dist, ESplineCoordinateSpace::World)
		);
	}
}
void AHD_GM::TickHeroAttack()
{
	/*���� ������Ʈ �� ���ݰ��ɿ���*/
	if (_hero->HeroUpdateAS(_info_wld.tick_unit_by_1frame))
	{
		/*Ÿ�� ã�� �õ�*/
		_hero->AttackBasicStart(FindEnemyFirstByV2(_hero->GetActorLocation2D()));
		
	}
}

void AHD_GM::WorldStart()
{
	/*������ ����� ó�� �����߽��ϴ�. �ʱ�ȭ�� �����մϴ�*/
	/*����,���̺���������ü�� �ʱ�ȭ�մϴ�*/
	_info_wld.InitInfoWorld();
	_info_wave.InitInfoWave();

	/*���̺꿡 ������ �������� �����ϱ�*/
	_info_wld.round_total = 1;
	const TArray<FDataWave*>& arr_data_waves = _gi->GetDataWaves();
	const FDataWave* s_wave = arr_data_waves[_info_wld.round_total - 1];
	_wave_spawn_enemies = s_wave->GetSpawnEnemies();
	_info_wld.round_stage = s_wave->GetStageRound();
	_info_wld.round_wave = s_wave->GetWaveRound();

	/*���̺����� �ʱ�ȭ*/
	_info_wave.spawn_enemy_interval_max =_gi->GetDataGame()->GetWaveEnemySpawnInterval();

	/*��� ������ �������� world_status�� �����մϴ�*/
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
void AHD_GM::WaveStart()
{
	/*��� ������ �������� world_status�� �����մϴ�*/
	_info_wld.wld_status = EWorldStatus::WAVE_PLAY;
}

void AHD_GM::EnemySpawn(const FString& str_code_enemy)
{
	AHD_Enemy* enemy_spawn = _manager_pool->PoolGetEnemy(str_code_enemy);
	if (!enemy_spawn) return;

	enemy_spawn->EnemyInit(IdGenerate(), _gi->GetDataGame()->GetEnemySpawnLocation());

	_spawned_enemies.Add(enemy_spawn);
}
AHD_Enemy* AHD_GM::FindEnemyFirstByV2(const FVector2D& v2_loc_center, const int64 i_id_enemy_except)
{
	AHD_Enemy* enemy_target_candidate = nullptr;
	//������ �̵��Ÿ�. ���� ���� �̵��� ���̰� �ĺ��Դϴ�
	int16 i_travel_dist_candidate = 0;
	int16 i_travel_dist_total_tmp = 0;

	for (AHD_Enemy* enemy_spawned : _spawned_enemies)
	{
		/*���̰� ��ȿ����*/
		if (enemy_spawned && enemy_spawned->GetInfoEnemy().id != i_id_enemy_except)
		{
			/*������ �̵��Ÿ��� Ÿ���ĺ����� �� �̵��ߴ���*/
			i_travel_dist_total_tmp = enemy_spawned->GetInfoEnemy().lane_dist;
			if (i_travel_dist_total_tmp > i_travel_dist_candidate)
			{
				i_travel_dist_candidate = i_travel_dist_total_tmp;
				enemy_target_candidate = enemy_spawned;
			}
		}
	}

	return enemy_target_candidate;
}

void AHD_GM::ChangeWeaponStartByCode(const FString& str_code_wp)
{
	//@���� �������� �����ܰ� �ʿ�
	
	/*�������� ���� Ǯ��*/
	_manager_pool->PoolInWeapon(_hero->GetInfoHero().wp_equip);

	/*���ο� ���� ����*/
	AHD_Weapon* wp = _manager_pool->PoolOutWeaponByCode(str_code_wp);
	if (!wp) return;
	
	wp->WPInit(_hero->GetSkeletalMesh());

	/*������ ������ �����մϴ�*/
	_hero->HeroChangeWeapon(wp);
}

const int64 AHD_GM::IdGenerate() { return ++_id_generator; }