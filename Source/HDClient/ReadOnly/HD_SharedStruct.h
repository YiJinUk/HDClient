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
class AHD_Monster;
class AHD_Projectile;
class AHD_Unit;
class AHD_Hero;
class AHD_Companion;

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
	WAVE_END, //���̺긦 Ŭ�����߽��ϴ�

	WORLD_GAME_OVER,//���迡�� ������ �׾����ϴ�
};
UENUM()
enum class EWaveType : uint8
{
	MONSTER,
	BOSS,
};
UENUM()
enum class EUnitClassType : uint8
{
	ENEMY,
	HERO,
	CPAN,
};

UENUM()
enum class EPROJMoveType : uint8
{
	TO_TARGET,//Ÿ�� ����
	TO_STRAIGHT,//Ÿ�پ��� ����
};
UENUM()
enum class EPROJAttackType : uint8
{
	HERO_ATTACK_BASIC,
	HERO_ATTACK_SKILL,
	CPAN_ATTACK_BASIC,
	CPAN_ATTACK_SKILL,
	MONSTER_ATTACK_BASIC,
	MONSTER_ATTACK_SKILL,
};

UENUM()
enum class EAttackType : uint8
{
	BASIC,
	SKILL,
};

UENUM()
enum class EAttackBasicStatus : uint8
{
	DETECT,//�⺻����.���
	TRY,//�⺻����.�õ�(����)
	DELAY,//�⺻����.������(�ĵ�)
};
UENUM()
enum class EAttackSkillStatus : uint8
{
	DETECT,//��ų����.���
	TRY,//��ų����.�õ�(����)
	COOLDOWN,//��ų����.��ٿ�
};



UENUM()
enum class EUnitStatType : uint8
{
	HP,
	ARMOR,
	ARMOR_HEAL_TICK,
	ARMOR_RECOVERY_TICK,
	AS_DEALY,
	SK_COOLDOWN_TICK,
};
UENUM()
enum class EUnitStatBy : uint8
{
	NO,
	ENEMY,
	HERO,
};

UENUM()
enum class EArmorStatus : uint8
{
	NO,//ȸ������ ����
	HEAL,//ȸ��
	RECOVERY,//����
};

UENUM()
enum class EVFXType : uint8
{
	NO,
	PROJECTILE,
	HIT,
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

	UPROPERTY(EditAnywhere, Category = "Monster")
		FVector _enemy_spawn_location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Companion")
		FVector _cpan_spawn_location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_speed = 2500;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_detect_range = 150;
public:
	FORCEINLINE const uint8 GetWaveEnemySpawnInterval() { return _wave_enemy_spawn_interval; }
	FORCEINLINE const FVector& GetEnemySpawnLocation() { return _enemy_spawn_location; }
	FORCEINLINE const FVector& GetCPANSpawnLocation() { return _cpan_spawn_location; }
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
		EWaveType _wave_type = EWaveType::MONSTER;
	UPROPERTY(EditAnywhere, Category = "General")
		TArray<FDataWaveSpawnEnemy> _spawn_enemies;

public:
	FORCEINLINE const uint8 GetStageRound() const { return _stage_round; }
	FORCEINLINE const uint8 GetWaveRound() const { return _wave_round; }
	FORCEINLINE const EWaveType GetWaveType() const { return _wave_type; }
	FORCEINLINE const TArray<FDataWaveSpawnEnemy>& GetSpawnEnemies() const { return _spawn_enemies; }
};
USTRUCT(BlueprintType)
struct FDataHero : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _hp = 0;

	UPROPERTY(EditAnywhere, Category = "Stat.Armor")
		int32 _armor_max = 0;
	UPROPERTY(EditAnywhere, Category = "Stat.Armor")
		int32 _armor_recorver = 0;
	UPROPERTY(EditAnywhere, Category = "Stat.Armor")
		int32 _armor_recovery_tick_max = 0;
	UPROPERTY(EditAnywhere, Category = "Stat.Armor")
		int32 _armor_heal = 0;
	UPROPERTY(EditAnywhere, Category = "Stat.Armor")
		int32 _armor_heal_tick_max = 0;

	UPROPERTY(EditAnywhere, Category = "Stat.Skill")
		FString _sk_code = "0";

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_sk = nullptr;
public:
	FORCEINLINE const int32 GetHP() { return _hp; }
	FORCEINLINE const int32 GetArmorMax() { return _armor_max; }
	FORCEINLINE const int32 GetArmorRecovery() { return _armor_recorver; }
	FORCEINLINE const int32 GetArmorRecoveryTickMax() { return _armor_recovery_tick_max; }
	FORCEINLINE const int32 GetArmorHeal() { return _armor_heal; }
	FORCEINLINE const int32 GetArmorHealTickMax() { return _armor_heal_tick_max; }
	FORCEINLINE const FString& GetSKCode() { return _sk_code; }
	FORCEINLINE UAnimMontage* GetAnimAttackSK() { return _anim_attack_sk; }
};
USTRUCT(BlueprintType)
struct FDataMonster : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_Monster> _class_monster;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

	UPROPERTY(EditAnywhere, Category = "Projectile")
		FString _code_proj = "0";

	UPROPERTY(EditAnywhere, Category = "Detail")
		bool _is_boss = false;

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _hp = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _str = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _as = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _move_speed = 0;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_basic = nullptr;
public:
	FORCEINLINE const TSubclassOf<AHD_Monster>& GetClassMOB() { return _class_monster; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const FString& GetCodePROJ() { return _code_proj; }
	FORCEINLINE const bool GetIsBoss() { return _is_boss; }
	FORCEINLINE const int32 GetHP() { return _hp; }
	FORCEINLINE const int32 GetSTR() { return _str; }
	FORCEINLINE const int32 GetAS() { return _as; }
	FORCEINLINE const int32 GetMoveSpeed() { return _move_speed; }
	FORCEINLINE UAnimMontage* GetAnimAttackBasic() { return _anim_attack_basic; }
};
USTRUCT(BlueprintType)
struct FDataCPAN : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_Companion> _class_cpan;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

	UPROPERTY(EditAnywhere, Category = "Projectile")
		FString _code_proj_basic = "0";
	UPROPERTY(EditAnywhere, Category = "Projectile")
		FString _code_proj_sk = "0";

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _str = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _as = 0;

	UPROPERTY(EditAnywhere, Category = "Stat.Skill")
		FString _sk_code = "0";

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_basic = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* _anim_attack_sk = nullptr;
public:
	FORCEINLINE const TSubclassOf<AHD_Companion>& GetClassCPAN() { return _class_cpan; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const FString& GetCodePROJBasic() { return _code_proj_basic; }
	FORCEINLINE const FString& GetCodePROJSK() { return _code_proj_sk; }
	FORCEINLINE const int32 GetSTR() { return _str; }
	FORCEINLINE const int32 GetAS() { return _as; }
	FORCEINLINE const FString& GetCodeSK() { return _sk_code; }
	FORCEINLINE UAnimMontage* GetAnimAttackBasic() { return _anim_attack_basic; }
	FORCEINLINE UAnimMontage* GetAnimAttackSK() { return _anim_attack_sk; }
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
		FString _code_proj = "0";

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
	FORCEINLINE const FString& GetCodePROJ() { return _code_proj; }
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
		EPROJMoveType _move_type = EPROJMoveType::TO_TARGET;
	UPROPERTY(EditAnywhere, Category = "General")
		EPROJAttackType _attack_type = EPROJAttackType::HERO_ATTACK_BASIC;

	UPROPERTY(EditAnywhere, Category = "VFX")
		FString _code_vfx_proj = "0";
	UPROPERTY(EditAnywhere, Category = "VFX")
		FString _code_vfx_hit = "0";
public:
	FORCEINLINE const TSubclassOf<AHD_Projectile>& GetClassPROJ() { return _class_proj; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const EPROJMoveType GetPROJMoveType() { return _move_type; }
	FORCEINLINE const EPROJAttackType GetPROJAttackType() { return _attack_type; }
	FORCEINLINE const FString& GetCodeVFXPROJ() { return _code_vfx_proj; }
	FORCEINLINE const FString& GetCodeVFXHit() { return _code_vfx_hit; }
};

USTRUCT(BlueprintType)
struct FDataVFX : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		UParticleSystem* _vfx_cascade = nullptr;
	UPROPERTY(EditAnywhere, Category = "General")
		float _size = 1.f;

	UPROPERTY(EditAnywhere, Category = "Description")
		EVFXType _vfx_type = EVFXType::NO;
	UPROPERTY(EditAnywhere, Category = "Description")
		FString _desc = "0";
public:
	//FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE UParticleSystem* GetCascade() { return _vfx_cascade; }
	FORCEINLINE const float GetSize() { return _size; }
};

USTRUCT(BlueprintType)
struct FDataSkill : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _id = 0;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _cooldown = 0;

	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_1 = 0;
	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_2 = 0;
	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_3 = 0;

	UPROPERTY(EditAnywhere, Category = "Description")
		FString _desc = "0";
public:
	FORCEINLINE const int32 GetID() const { return _id; }
	FORCEINLINE const int32 GetCooldown() const { return _cooldown; }
	FORCEINLINE const int32 GetValue1() const { return _value_1; }
	FORCEINLINE const int32 GetValue2() const { return _value_2; }
	FORCEINLINE const int32 GetValue3() const { return _value_3; }
};
#pragma endregion

USTRUCT()
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
USTRUCT()
struct FInfoWave
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EWaveType wave_type = EWaveType::MONSTER;
	UPROPERTY()
		uint8 spawn_enemy_interval_current = 0;
	UPROPERTY()
		uint8 spawn_enemy_interval_max = 0;

	void InitInfoWave()
	{
		spawn_enemy_interval_current = 0;
		wave_type = EWaveType::MONSTER;
	}
};

USTRUCT()
struct FInfoPlayer
{
	GENERATED_BODY()

public:

};

USTRUCT()
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

USTRUCT()
struct FInfoHero
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code_wp_equip = "WP00101";
	UPROPERTY()
		AHD_Weapon* wp_equip = nullptr;

	UPROPERTY()
		EAttackBasicStatus atk_basic_status = EAttackBasicStatus::DELAY;
	UPROPERTY()
		EAttackSkillStatus atk_sk_status = EAttackSkillStatus::COOLDOWN;
	UPROPERTY()
		EArmorStatus armor_status = EArmorStatus::HEAL;

	UPROPERTY()
		int32 hp_base = 0;
	UPROPERTY()
		int32 hp_max_base = 0;
	
	UPROPERTY()
		int32 armor = 0;
	UPROPERTY()
		int32 armor_max = 0;
	UPROPERTY()
		int32 armor_heal_base = 0;
	UPROPERTY()
		int32 armor_recovery_base = 0;
	UPROPERTY()
		int32 armor_heal_tick = 0;
	UPROPERTY()
		int32 armor_heal_tick_max = 0;
	UPROPERTY()
		int32 armor_recovery_tick = 0;
	UPROPERTY()
		int32 armor_recovery_tick_max = 0;

	UPROPERTY()
		int32 str_base = 0;
	UPROPERTY()
		int32 dmg_base = 100;

	UPROPERTY()
		int32 as_base = 0;
	UPROPERTY()
		int32 as_delay = 0;

	FDataSkill* sk_data = nullptr;
	UPROPERTY()
		int32 sk_ap_base = 100;
	UPROPERTY()
		int32 sk_cooldown_tick = 0;
	UPROPERTY()
		int32 sk_cooldown_tick_max = 0;


	UPROPERTY()
		float anim_rate_base = 0.f;

	UPROPERTY()
		AHD_Monster* target = nullptr;

	UPROPERTY()
		UAnimMontage* anim_attack_sk = nullptr;
public:
	FORCEINLINE const int32 GetHPTotal() const { return hp_base; }
	FORCEINLINE const int32 GetHPMaxTotal() const { return hp_max_base; }
	FORCEINLINE const int32 GetSTRTotal() const { return str_base; }
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base; }
	FORCEINLINE const int32 GetASTotal() const { return as_base; }
	FORCEINLINE const int32 GetArmorHeadTotal() const { return armor_heal_base; }
	FORCEINLINE const int32 GetArmorRecoveryTotal() const { return armor_recovery_base; }
	FORCEINLINE const int32 GetSKAPTotal() const { return sk_ap_base; }

	FORCEINLINE const float GetHPRate() const { return (float)GetHPTotal() / (float)GetHPMaxTotal(); }
	FORCEINLINE const float GetArmorHealRate() const { return (float)armor_heal_tick / (float)armor_heal_tick_max; }
	FORCEINLINE const float GetArmorRecoveryRate() const { return (float)armor_recovery_tick / (float)armor_recovery_tick_max; }

	FORCEINLINE const int32 GetAttackBasicDMG() const { return (float)GetSTRTotal() * (GetDMGTotal() * 0.01f); }
	FORCEINLINE const int32 GetASTotalDelay() const { return (60.f / float(GetASTotal())) * 60.f; }

	FORCEINLINE const float GetSKCooldownRate() const { return (float)sk_cooldown_tick / (float)sk_cooldown_tick_max; }

};

USTRUCT()
struct FInfoMonster
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
		bool is_death = false;

	UPROPERTY()
		EAttackBasicStatus atk_basic_status = EAttackBasicStatus::DELAY;
	UPROPERTY()
		AHD_Hero* target = nullptr;

	UPROPERTY()
		FString code_proj = "0";

	UPROPERTY()
		bool is_boss = false;

	UPROPERTY()
		int32 hp = 0;
	UPROPERTY()
		int32 hp_max = 0;

	UPROPERTY()
		int32 str_base = 0;
	UPROPERTY()
		int32 dmg_base = 100;
	UPROPERTY()
		int32 as_base = 0;
	UPROPERTY()
		int32 as_delay = 0;
	UPROPERTY()
		int32 move_speed = 0;

	//0�̸����� �������� �̵��� �Ұ����մϴ�
	UPROPERTY()
		int8 is_can_move = 0;

	UPROPERTY()
		int32 death_to_pool_tick = 0;
	UPROPERTY()
		int32 death_to_pool_tick_max = 0;

	UPROPERTY()
		UAnimMontage* anim_attack_basic = nullptr;
public:
	FORCEINLINE const int32 GetSTRTotal() const { return str_base; }
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base; }
	FORCEINLINE const int32 GetASTotal() const { return as_base; }

	FORCEINLINE const float GetHPRate() const { return (float)hp / (float)hp_max; }
	FORCEINLINE const int32 GetAttackBasicDMG() const { return (float)GetSTRTotal() * (GetDMGTotal() * 0.01f); }
	FORCEINLINE const int32 GetASTotalDelay() const { return (60.f / float(GetASTotal())) * 60.f; }
};

USTRUCT()
struct FInfoCPAN
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		EAttackBasicStatus atk_basic_status = EAttackBasicStatus::DELAY;
	UPROPERTY()
		EAttackSkillStatus atk_sk_status = EAttackSkillStatus::COOLDOWN;
	UPROPERTY()
		AHD_Monster* target = nullptr;

	UPROPERTY()
		FString code_proj_basic = "0";
	UPROPERTY()
		FString code_proj_sk = "0";

	UPROPERTY()
		int32 str_base = 0;
	UPROPERTY()
		int32 dmg_base = 100;
	UPROPERTY()
		int32 as_base = 0;
	UPROPERTY()
		int32 as_delay = 0;

	FDataSkill* sk_data = nullptr;
	UPROPERTY()
		int32 sk_ap_base = 100;
	UPROPERTY()
		int32 sk_cooldown_tick = 0;
	UPROPERTY()
		int32 sk_cooldown_tick_max = 0;

	UPROPERTY()
		float anim_rate_base = 0.f;

	UPROPERTY()
		UAnimMontage* anim_attack_basic = nullptr;
	UPROPERTY()
		UAnimMontage* anim_attack_sk = nullptr;
public:
	FORCEINLINE const int32 GetSTRTotal() const { return str_base; }
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base; }
	FORCEINLINE const int32 GetASTotal() const { return as_base; }
	FORCEINLINE const int32 GetSKAPTotal() const { return sk_ap_base; }

	FORCEINLINE const int32 GetAttackBasicDMG() const { return (float)GetSTRTotal() * (GetDMGTotal() * 0.01f); }
	FORCEINLINE const int32 GetASTotalDelay() const { return (60.f / float(GetASTotal())) * 60.f; }
};

USTRUCT()
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

USTRUCT()
struct FInfoProjectile
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		EPROJMoveType move_type = EPROJMoveType::TO_TARGET;
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

USTRUCT()
struct FBattleHitResult
{
	GENERATED_BODY()

public:
	UPROPERTY()
		bool is_broken_armor = false;

public:
	void InitBattleHitResult()
	{
		is_broken_armor = false;
	}
};

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
		AHD_Unit* atk = nullptr;
	UPROPERTY()
		AHD_Unit* def = nullptr;
	UPROPERTY()
		int32 dmg_origin = 0;
	UPROPERTY()
		EAttackType atk_type = EAttackType::BASIC;

public:
	void InitDamageInfo()
	{
		atk = nullptr;
		def = nullptr;
		dmg_origin = 0;
		atk_type = EAttackType::BASIC;
	}
};
USTRUCT()
struct FDamageResult
{
	GENERATED_BODY()

public:
	UPROPERTY()
		AHD_Unit* atk = nullptr;
	UPROPERTY()
		AHD_Unit* def = nullptr;

	UPROPERTY()
		int32 dmg_base = 0;
	UPROPERTY()
		int32 dmg_sum = 0;
	UPROPERTY()
		int32 dmg_hp_rlt = 0;
	UPROPERTY()
		int32 dmg_armor_rlt = 0;

	UPROPERTY()
		int32 atk_armor_base = 0;
	UPROPERTY()
		int32 atk_armor_rlt = 0;
	UPROPERTY()
		int32 def_armor_base = 0;
	UPROPERTY()
		int32 def_armor_rlt = 0;

public:
	void InitDamageResult()
	{
		atk = nullptr;
		def = nullptr;

		dmg_base = 0;
		dmg_sum = 0;
		dmg_hp_rlt = 0;
		dmg_armor_rlt = 0;

		atk_armor_base = 0;
		atk_armor_rlt = 0;

		def_armor_base = 0;
		def_armor_rlt = 0;
	}
};