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
	//���� ������ ù ȣ�������Դϴ�
	void GMPostInit();

	const int64 IdGenerate();
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;

	UPROPERTY()
		bool _is_call_PostLogin = false;
	UPROPERTY()
		bool _is_call_BeginPlay = false;
	UPROPERTY()
		int64 _id_generator = 0;
#pragma endregion

#pragma region Tick
private:
	void TickCheckSpawnEnemy();
	void TickEnemyMove(const float f_delta_time);
	void TickHeroAttack();
#pragma endregion

#pragma region Home
#pragma endregion

#pragma region World
public:
	void WorldStart();
private:
	UPROPERTY()
		FInfoWorld _info_wld;
	//�̹� ���̺꿡 ������ ������ �Դϴ�
	//���迡 ���� �Ǵ� ���̺긦 Ŭ������ �� ���� �����͸� "����"�ؼ� ����ϹǷ� ���� ���� �����ص� �������ϴ�
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

#pragma region Manager,Spline
private:
	UPROPERTY()
		AHD_Manager_Pool* _manager_pool = nullptr;
	UPROPERTY()
		AHD_Manager_Weapon* _manager_wp = nullptr;

	UPROPERTY()
		class USplineComponent* _spline_component = nullptr;
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

	AHD_Enemy* FindEnemyFirstByV2(const FVector2D& v2_loc_center, const int64 i_id_enemy_except = 0);
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
