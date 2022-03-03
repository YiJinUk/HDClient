// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GM.h"
#include "HD_GI.h"
#include "HD_PC.h"
#include "Actor/Unit/Friend/Hero/HD_Hero.h"
#include "Actor/Unit/Friend/MagicStone/HD_MagicStone.h"
#include "Actor/Unit/Friend/Companion/HD_Companion.h"
#include "Actor/Unit/Enemy/HD_Enemy.h"
#include "Actor/Object/Weapon/HD_Weapon.h"

#include "Manager/HD_Manager_Pool.h"
#include "Manager/HD_Manager_Weapon.h"

#include "Kismet/GameplayStatics.h"

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
	_hdgi = wld->GetGameInstance<UHD_GI>();
	_hdgi->GIPostInit();
	
	/*월드에 존재하는 영웅, 동료, 마법석액터 가져오기*/
	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Hero::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _hero = Cast<AHD_Hero>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_MagicStone::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _ms = Cast<AHD_MagicStone>(arr_found_actor[0]); }
	UGameplayStatics::GetAllActorsOfClass(wld, AHD_Companion::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1) { _cpan = Cast<AHD_Companion>(arr_found_actor[0]); }

	/*매니지클래스 생성후 초기화*/
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<AHD_Manager_Pool>(s_param);
	_manager_wp = wld->SpawnActor<AHD_Manager_Weapon>(s_param);

	_manager_pool->PoolPostInit(_hdgi);

	/*플레이어 초기화*/
	_info_player.wp_equip = _manager_pool->PoolOutWeaponByCode(_info_player.code_wp_equip);
	_info_player.wp_equip->WPInit(_hero->GetSkeletalMesh());

	_pc->PCPostInit();
}
void AHD_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		TickEnemyMove();
		break;
	default:
		break;
	}
}
void AHD_GM::TickCheckSpawnEnemy()
{
	/*인터벌을 체크합니다*/
	if (_info_wave.spawn_enemy_interval_current >= _info_wave.spawn_enemy_interval_max)
	{
		/*적 생성*/
		_info_wave.spawn_enemy_interval_current -= _info_wave.spawn_enemy_interval_max;
		EnemySpawn("ENEMY01001");
	}
}
void AHD_GM::TickEnemyMove()
{
	if (_spawned_enemies.Num() <= 0) return;
	for (AHD_Enemy* enemy : _spawned_enemies)
	{
		enemy->AddActorWorldOffset(FVector(-1, -1, 0));
	}
}

void AHD_GM::WorldStart()
{
	/*집에서 세계로 처음 진입했습니다. 초기화를 진행합니다*/
	/*세계,웨이브정보구조체를 초기화합니다*/
	_info_wld.InitInfoWorld();
	_info_wave.InitInfoWave();

	/*웨이브에 등장할 적데이터 복제하기*/
	_info_wld.round_total = 1;
	const TArray<FDataWave*>& arr_data_waves = _hdgi->GetDataWaves();
	const FDataWave* s_wave = arr_data_waves[_info_wld.round_total - 1];
	_wave_spawn_enemies = s_wave->GetSpawnEnemies();
	_info_wld.round_stage = s_wave->GetStageRound();
	_info_wld.round_wave = s_wave->GetWaveRound();

	/*웨이브정보 초기화*/
	_info_wave.spawn_enemy_interval_max =_hdgi->GetDataGame()->GetWaveEnemySpawnInterval();

	/*모든 과정을 거쳤으면 world_status를 변경합니다*/
	_info_wld.wld_status = EWorldStatus::WAVE_STANDBY;
}
void AHD_GM::WaveStart()
{
	/*모든 과정을 거쳤으면 world_status를 변경합니다*/
	_info_wld.wld_status = EWorldStatus::WAVE_PLAY;
}

void AHD_GM::EnemySpawn(const FString& str_code_enemy)
{
	AHD_Enemy* enemy_spawn = _manager_pool->PoolGetEnemy(str_code_enemy);
	if (!enemy_spawn) return;

	enemy_spawn->EnemyInit(_hdgi->GetDataGame()->GetEnemySpawnLocation());

	_spawned_enemies.Add(enemy_spawn);
}

void AHD_GM::ChangeWeaponStartByCode(const FString& str_code_wp)
{
	//@변경 가능한지 검증단계 필요
	
	/*장착중인 무기 풀인*/
	_manager_pool->PoolInWeapon(_info_player.wp_equip);

	/*새로운 무기 장착*/
	AHD_Weapon* wp = _manager_pool->PoolOutWeaponByCode(str_code_wp);
	if (!wp) return;
	
	wp->WPInit(_hero->GetSkeletalMesh());

	_info_player.code_wp_equip = str_code_wp;
	_info_player.wp_equip = wp;
}