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
class AHD_Unit;
class AHD_Hero;

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
	HOME, //Ÿ��Ʋ
	WAVE_STANDBY, //���̺��� ��� �غ� ��ġ�� �÷��̾��� ���̺� ������ ��ٸ��� ��
	WAVE_PLAY, //���̺��� �Դϴ�
};
UENUM()
enum class EUnitClassType : uint8
{
	ENEMY,
	HERO,
};
UENUM()
enum class EHeroAttackBasicStatus : uint8
{
	DETECT,//�⺻����.���
	TRY,//�⺻����.�õ�(����)
	DELAY,//�⺻����.������(�ĵ�)
};

UENUM()
enum class EPROJTargetType : uint8
{
	TARGET,//Ÿ�� ����
	STRAIGHT,//Ÿ�پ��� ����
};
UENUM()
enum class EPROJAttackType : uint8
{
	HERO_ATTACK_BASIC,
};


#pragma region Data
USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()

protected:
	//���̺��� ���� �����Ǵ� �ð��� �����Դϴ�
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

	UPROPERTY(EditAnywhere, Category = "Projectile")
		FString _code_projectile = "0";

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _str = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _as = 0;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_start = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_basic = nullptr;

public:
	FORCEINLINE const TSubclassOf<AHD_Weapon>& GetClassWeapon() { return _class_weapon; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const FString& GetCodePROJ() { return _code_projectile; }
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

	UPROPERTY(EditAnywhere, Category = "General")
		EPROJTargetType _target_type = EPROJTargetType::TARGET;
	UPROPERTY(EditAnywhere, Category = "General")
		EPROJAttackType _attack_type = EPROJAttackType::HERO_ATTACK_BASIC;

	UPROPERTY(EditAnywhere, Category = "VFX")
		FString _code_vfx_hit = "0";
public:
	FORCEINLINE const TSubclassOf<AHD_Projectile>& GetClassPROJ() { return _class_proj; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const EPROJTargetType GetPROJTargetType() { return _target_type; }
	FORCEINLINE const EPROJAttackType GetPROJAttackType() { return _attack_type; }
	FORCEINLINE const FString& GetCodeVFXHit() { return _code_vfx_hit; }
};

USTRUCT(BlueprintType)
struct FDataVFX : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, Category = "General")
		UParticleSystem* _vfx_cascade = nullptr;
	UPROPERTY(EditAnywhere, Category = "General")
		float _size = 1.f;
public:
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE UParticleSystem* GetCascade() { return _vfx_cascade; }
	FORCEINLINE const float GetSize() { return _size; }
};
#pragma endregion

USTRUCT(BlueprintType)
struct FInfoWorld
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EWorldStatus wld_status = EWorldStatus::HOME;

	//1�����Ӹ��� �����Ǵ� ƽ���� �Դϴ�
	UPROPERTY()
		uint8 tick_unit_by_1frame = 1;
	UPROPERTY()
		uint64 tick_total = 0;
	UPROPERTY()
		uint64 tick_round = 0;

	//���� ���̺꿡 ������ �� ���� 1�� �����մϴ�. ���������� ������ �ʽ��ϴ�
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
struct FInfoUnit
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EUnitClassType unit_type = EUnitClassType::HERO;
	//T : �ǰ��� ���� �� �ִ� �����Դϴ�
	UPROPERTY()
		bool is_hit_valid = true;
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
		AHD_Hero* owner_hero = nullptr;

	UPROPERTY()
		FString code_proj = "0";

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
		int64 id = 0;
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		EPROJTargetType target_type = EPROJTargetType::TARGET;
	UPROPERTY()
		EPROJAttackType attack_type = EPROJAttackType::HERO_ATTACK_BASIC;
	UPROPERTY()
		AHD_Unit* owner = nullptr;

	UPROPERTY()
		int32 speed = 0;
	UPROPERTY()
		int32 detect_range = 0;

	UPROPERTY()
		AHD_Unit* target = nullptr;
	UPROPERTY()
		FVector2D velocity = FVector2D::ZeroVector;

	FDataVFX* vfx = nullptr;
};