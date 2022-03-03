// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "HD_SharedStruct.generated.h"

class UAnimMontage;
class UParticleSystem;
class AHD_Weapon;
class AHD_Enemy;
class AHD_Projectile;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_SharedStruct : public UObject
{
	GENERATED_BODY()
	
};

UENUM()
enum class EWorldStatus : uint8
{
	HOME, //타이틀
	WAVE_STANDBY, //웨이브의 모든 준비를 마치고 플레이어의 웨이브 시작을 기다리는 중
	WAVE_PLAY, //웨이브중 입니다
};

UENUM()
enum class EHeroAttackBasicStatus : uint8
{
	DETECT,//기본공격.대기
	TRY,//기본공격.시도(선딜)
	DELAY,//기본공격.딜레이(후딜)

};


#pragma region Data
USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()

protected:
	//웨이브중 적이 생성되는 시간의 간격입니다
	UPROPERTY(EditAnywhere, Category = "Wave")
		uint8 _wave_enemy_spawn_interval = 0;

	UPROPERTY(EditAnywhere, Category = "Enemy")
		FVector _enemy_spawn_location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_speed = 2500;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_detect_range = 150;
public:
	FORCEINLINE const uint8 GetWaveEnemySpawnInterval() { return _wave_enemy_spawn_interval; }
	FORCEINLINE const FVector GetEnemySpawnLocation() { return _enemy_spawn_location; }
	FORCEINLINE const int32 GetPROJSpeed() { return _proj_speed; }
	FORCEINLINE const int32 GetPROJDetectRange() { return _proj_detect_range; }
};
USTRUCT(BlueprintType)
struct FDataWaveSpawnEnemy : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FString code = "0";
	UPROPERTY(EditAnywhere)
		uint8 count = 0;
};
USTRUCT(BlueprintType)
struct FDataWave : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		uint8 _stage_round = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		uint8 _wave_round = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<FDataWaveSpawnEnemy> _spawn_enemies;

public:
	FORCEINLINE const uint8 GetStageRound() const { return _stage_round; }
	FORCEINLINE const uint8 GetWaveRound() const { return _wave_round; }
	FORCEINLINE const TArray<FDataWaveSpawnEnemy>& GetSpawnEnemies() const { return _spawn_enemies; }
};
USTRUCT(BlueprintType)
struct FDataEnemy : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_Enemy> _class_enemy;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _move_speed = 0;
public:
	FORCEINLINE const TSubclassOf<AHD_Enemy>& GetClassEnemy() { return _class_enemy; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const int32 GetMoveSpeed() { return _move_speed; }
};
USTRUCT(BlueprintType)
struct FDataWeapon : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_Weapon> _class_weapon;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

	UPROPERTY(EditAnywhere, Category = "General")
		int32 _str = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _as = 0;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_start = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_basic = nullptr;

public:
	FORCEINLINE const TSubclassOf<AHD_Weapon>& GetClassWeapon() { return _class_weapon; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const int32 GetSTR() { return _str; }
	FORCEINLINE const int32 GetAS() { return _as; }
	FORCEINLINE UAnimMontage* GetAnimAttackBasic() { return _anim_attack_basic; }
};
USTRUCT(BlueprintType)
struct FDataProjectile : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_Projectile> _class_proj;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

public:
	FORCEINLINE const TSubclassOf<AHD_Projectile>& GetClassPROJ() { return _class_proj; }
	FORCEINLINE const FString& GetCode() { return _code; }
};

USTRUCT(BlueprintType)
struct FDataVFX : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, Category = "General")
		UParticleSystem* _vfx = nullptr;

public:
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE UParticleSystem* GetVFX() { return _vfx; }
};
#pragma endregion

USTRUCT(BlueprintType)
struct FInfoWorld
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EWorldStatus wld_status = EWorldStatus::HOME;

	//1프레임마다 증가되는 틱단위 입니다
	UPROPERTY()
		uint8 tick_unit_by_1frame = 1;
	UPROPERTY()
		uint64 tick_total = 0;
	UPROPERTY()
		uint64 tick_round = 0;

	//다음 웨이브에 진입할 때 마다 1씩 증가합니다. 스테이지는 따지지 않습니다
	UPROPERTY()
		uint8 round_total = 1;
	UPROPERTY()
		uint8 round_stage = 0;
	UPROPERTY()
		uint8 round_wave = 0;

	void InitInfoWorld()
	{
		wld_status = EWorldStatus::HOME;

		tick_unit_by_1frame = 1;
		tick_total = 0;
		tick_round = 0;

		round_total = 1;
		round_stage = 0;
		round_wave = 0;
	}
};
USTRUCT(BlueprintType)
struct FInfoWave
{
	GENERATED_BODY()

public:
	UPROPERTY()
		uint8 spawn_enemy_interval_current = 0;
	UPROPERTY()
		uint8 spawn_enemy_interval_max = 0;

	void InitInfoWave()
	{
		spawn_enemy_interval_current = 0;
		spawn_enemy_interval_max = 0;
	}
};

USTRUCT(BlueprintType)
struct FInfoPlayer
{
	GENERATED_BODY()

public:

};

USTRUCT(BlueprintType)
struct FInfoHero
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code_wp_equip = "WP00101";
	UPROPERTY()
		AHD_Weapon* wp_equip = nullptr;

	UPROPERTY()
		EHeroAttackBasicStatus atk_basic_status = EHeroAttackBasicStatus::DELAY;

	UPROPERTY()
		int32 str_base = 0;
	UPROPERTY()
		int32 dmg_base = 100;

	UPROPERTY()
		int32 as_base = 0;
	UPROPERTY()
		int32 as_delay = 0;


	UPROPERTY()
		float anim_rate_base = 0.f;

	UPROPERTY()
		AHD_Enemy* target = nullptr;
public:
	FORCEINLINE int32 GetASTotal() const { return as_base; }
	FORCEINLINE int32 GetASTotalDelay() const { return (60.f / float(GetASTotal())) * 60.f; }
	//FORCEINLINE int32 GetASTotalDelay() const { return (360.f / float(GetASTotal())); }
};

USTRUCT(BlueprintType)
struct FInfoEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		float lane_dist = 0;

	UPROPERTY()
		int32 move_speed = 0;
	UPROPERTY()
		bool is_death = false;
};

USTRUCT(BlueprintType)
struct FInfoWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		int32 str = 0;
	UPROPERTY()
		int32 as = 0;
	

	//UPROPERTY(EditAnywhere, Category = "Animation")
	//	UAnimMontage* anim_start = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* anim_attack_basic = nullptr;

};

USTRUCT(BlueprintType)
struct FInfoProjectile
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code = "0";
};