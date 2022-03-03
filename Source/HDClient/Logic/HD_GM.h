// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "GameFramework/GameModeBase.h"
#include "HD_GM.generated.h"

class UHD_GI;
class AHD_PC;
class AHD_Hero;
class AHD_MagicStone;
class AHD_Companion;
class AHD_Enemy;
class AHD_Manager_Pool;
class AHD_Manager_Weapon;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_GM : public AGameModeBase
{
	GENERATED_BODY()
	

#pragma region Init
protected:
	AHD_GM();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	//어플 실행후 첫 호출지점입니다
	void GMPostInit();
private:
	UPROPERTY()
		UHD_GI* _hdgi = nullptr;

	UPROPERTY()
		bool _is_call_PostLogin = false;
	UPROPERTY()
		bool _is_call_BeginPlay = false;
#pragma endregion

#pragma region Tick
private:
	void TickCheckSpawnEnemy();
	void TickEnemyMove();
#pragma endregion

#pragma region Home
#pragma endregion

#pragma region World
public:
	void WorldStart();
private:
	UPROPERTY()
		FInfoWorld _info_wld;
	//이번 웨이브에 등장할 적정보 입니다
	//세계에 진입 또는 웨이브를 클리어할 때 마다 데이터를 "복제"해서 사용하므로 내부 값을 변경해도 괜찮습니다
	UPROPERTY()
		TArray<FDataWaveSpawnEnemy> _wave_spawn_enemies;
#pragma endregion

#pragma region Stage,Wave
public:
	UFUNCTION(BlueprintCallable)
		void WaveStart();
private:
	UPROPERTY()
		FInfoWave _info_wave;
#pragma endregion

#pragma region Manager
private:
	UPROPERTY()
		AHD_Manager_Pool* _manager_pool = nullptr;
	UPROPERTY()
		AHD_Manager_Weapon* _manager_wp = nullptr;
#pragma endregion

#pragma region Player
private:
	UPROPERTY()
		AHD_PC* _pc = nullptr;
	UPROPERTY()
		FInfoPlayer _info_player;
#pragma endregion

#pragma region Hero
private:
	UPROPERTY()
		AHD_Hero* _hero = nullptr;
#pragma endregion

#pragma region MagicStone
private:
	AHD_MagicStone* _ms = nullptr;
#pragma endregion

#pragma region Companion
private:
	AHD_Companion* _cpan = nullptr;
#pragma endregion

#pragma region Enemy
public:
	void EnemySpawn(const FString& str_code_enemy);
private:
	UPROPERTY()
		TArray<AHD_Enemy*> _spawned_enemies;
#pragma endregion

#pragma region Weapon
public:
	UFUNCTION(BlueprintCallable)
		void ChangeWeaponStartByCode(const FString& str_code_wp);
#pragma endregion
};
