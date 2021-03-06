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
class AHD_MagicStone;
class AHD_Reward;
class AHD_Portal;

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
	WAVE_CLEAR, //웨이브를 클리어했습니다

	WORLD_GAME_OVER,//세계에서 영웅이 죽었습니다
};
UENUM()
enum class EWaveType : uint8
{
	MONSTER,
	BOSS,
	LAST_CLEAR,
};

UENUM()
enum class EPlayerStatType : uint8
{
	GOLD,
	SOUL,
};

UENUM()
enum class EUnitClassType : uint8
{
	ENEMY,
	HERO,
	CPAN,
	MS,
};

UENUM()
enum class EPROJMoveType : uint8
{
	TO_TARGET,//타겟 따라서
	TO_STRAIGHT,//타겟없이 직진
};
UENUM()
enum class EPROJAttackType : uint8
{
	HERO_ATTACK_BASIC,
	HERO_ATTACK_SKILL,
	CPAN_ATTACK_BASIC,
	CPAN_ATTACK_SKILL,
	MS_ATTACK_SKILL,
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
	DETECT,//기본공격.대기
	TRY,//기본공격.시도(선딜)
	DELAY,//기본공격.딜레이(후딜)
};
UENUM()
enum class EAttackSkillStatus : uint8
{
	DETECT,//스킬공격.대기
	TRY,//스킬공격.시도(선딜)
	COOLDOWN,//스킬공격.쿨다운
};

UENUM()
enum class EUnitStatType : uint8
{
	HP,
	ARMOR,
	ARMOR_HEAL_TICK,
	ARMOR_RECOVERY_TICK,
	DMG,
	AS_DEALY,
	SK_COOLDOWN_TICK,
};
UENUM()
enum class EUnitStatBy : uint8
{
	NO,
	ENEMY,
	HERO,
	BUFF,
};

UENUM()
enum class EArmorStatus : uint8
{
	NO,//회복하지 않음
	HEAL,//회복
	RECOVERY,//복구
};

UENUM()
enum class EVFXType : uint8
{
	NO,
	PROJECTILE,
	HIT,
};

UENUM()
enum class EBuffPhase : uint8
{
	IMMEDIATELY,
};
UENUM()
enum class EBuffTimer : uint8
{
	TIMER,
};
UENUM()
enum class EBuffOverlap : uint8
{
	NEW,
	VALUE,
	TIME,
	VALUE_TIME,
};

UENUM()
enum class ERewardType : uint8
{
	NO,
	GOLD,
	HP_MAX,
	SOUL_MONSTER_WAVE,
	SPEC01,
	SPEC02,
	SPEC03,
};
UENUM()
enum class ERewardBy : uint8
{
	BASE,
	SELECT,
};


UENUM()
enum class EPowerType : uint8
{
	SPEC01,
	SPEC02,
	SPEC03,
};
UENUM()
enum class ESPECAttackType : uint8
{
	NO,
	BASIC_A,
	BASIC_B,
	BASIC_C,
	BASIC_D,
};
UENUM()
enum class ESPECTier : uint8
{
	TIER_0 = 0,
	TIER_1 = 1,
	TIER_2 = 2,
	TIER_3 = 3,
	TIER_4 = 4,//아직 사용중이지 않습니다. 사용하지 마세요
	TIER_5 = 5,

	TIER_MAX = 6,//듀오티어인 5티어를 제외한 모든 티어의 특성을 획득했습니다
};



#pragma region Data
USTRUCT(BlueprintType)
struct FDataRewardSelectActive : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		ERewardType _reward_select_active = ERewardType::NO;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _reward_rate = 0;
public:
	FORCEINLINE const ERewardType GetRewardSelectActive() const { return _reward_select_active; }
	FORCEINLINE const int32 GetRewardRate() const { return _reward_rate; }
};
USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()

protected:
	//웨이브중 적이 생성되는 시간의 간격입니다
	UPROPERTY(EditAnywhere, Category = "Wave")
		uint8 _wave_enemy_spawn_interval = 0;

	UPROPERTY(EditAnywhere, Category = "Companion")
		FVector _cpan_spawn_location = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "MagicStone")
		FVector _ms_spawn_location = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Monster")
		FVector _enemy_spawn_location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_speed = 2500;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		int32 _proj_detect_range = 150;

	UPROPERTY(EditAnywhere, Category = "Reward")
		TSubclassOf<AHD_Reward> reward_class;
	//웨이브클리어시 등장하는 랜덤보상의 개수입니다
	UPROPERTY(EditAnywhere, Category = "Reward")
		uint8 _reward_random_count = 2;
	/*선택보상확률에 대한 배열입니다*/
	UPROPERTY(EditAnywhere, Category = "Reward")
		TArray<FDataRewardSelectActive> rewards_select_active;

	UPROPERTY(EditAnywhere, Category = "SPEC")
		TArray<EPowerType> specs_active;

	UPROPERTY(EditAnywhere, Category = "Portal")
		TSubclassOf<AHD_Portal> portal_class;
public:
	FORCEINLINE const uint8 GetWaveEnemySpawnInterval() { return _wave_enemy_spawn_interval; }
	FORCEINLINE const FVector& GetCPANSpawnLocation() { return _cpan_spawn_location; }
	FORCEINLINE const FVector& GetMSSpawnLocation() { return _ms_spawn_location; }
	FORCEINLINE const FVector& GetEnemySpawnLocation() { return _enemy_spawn_location; }
	FORCEINLINE const int32 GetPROJSpeed() { return _proj_speed; }
	FORCEINLINE const int32 GetPROJDetectRange() { return _proj_detect_range; }
	FORCEINLINE const TSubclassOf<AHD_Reward>& GetRewardClass() { return reward_class; }
	FORCEINLINE const uint8 GetRewardRandomCount() { return _reward_random_count; }
	FORCEINLINE const TArray<FDataRewardSelectActive>& GetRewardsSelectActive() { return rewards_select_active; }
	FORCEINLINE const TArray<EPowerType>& GetSPECsActive() { return specs_active; }
	FORCEINLINE const TSubclassOf<AHD_Portal>& GetPortalClass() { return portal_class; }
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
	//해당 웨이브의 보상을 미리 제한합니다
	//스테이지 보스방 등 에서 적용됩니다
	UPROPERTY(EditAnywhere, Category = "Reward")
		ERewardType _wave_reward_type = ERewardType::NO;

public:
	FORCEINLINE const uint8 GetStageRound() const { return _stage_round; }
	FORCEINLINE const uint8 GetWaveRound() const { return _wave_round; }
	FORCEINLINE const EWaveType GetWaveType() const { return _wave_type; }
	FORCEINLINE const TArray<FDataWaveSpawnEnemy>& GetSpawnEnemies() const { return _spawn_enemies; }
	FORCEINLINE const ERewardType GetWareRewardType() const { return _wave_reward_type; }
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
struct FDataMS : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		TSubclassOf<AHD_MagicStone> _class_ms;
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";

	UPROPERTY(EditAnywhere, Category = "Projectile")
		FString _code_proj = "0";

	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _int = 0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int32 _mp = 0;//magic power

	UPROPERTY(EditAnywhere, Category = "Stat.Skill")
		FString _sk_code = "0";

	//UPROPERTY(EditAnywhere, Category = "Animation")
	//	UAnimMontage* _anim_attack_basic = nullptr;
	//UPROPERTY(EditAnywhere, Category = "Animation")
	//	UAnimMontage* _anim_attack_sk = nullptr;
public:
	FORCEINLINE const TSubclassOf<AHD_MagicStone>& GetClassMS() { return _class_ms; }
	FORCEINLINE const FString& GetCode() { return _code; }
	FORCEINLINE const FString& GetCodePROJ() { return _code_proj; }
	FORCEINLINE const int32 GetINT() { return _int; }
	FORCEINLINE const int32 GetMP() { return _mp; }
	FORCEINLINE const FString& GetCodeSK() { return _sk_code; }
	//FORCEINLINE UAnimMontage* GetAnimAttackBasic() { return _anim_attack_basic; }
	//FORCEINLINE UAnimMontage* GetAnimAttackSK() { return _anim_attack_sk; }
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

USTRUCT(BlueprintType)
struct FDataBuff : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _id = 0;

	UPROPERTY(EditAnywhere, Category = "Description")
		FString _desc = "0";
public:
	FORCEINLINE const int32 GetID() const { return _id; }
};

USTRUCT(BlueprintType)
struct FDataReward : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		ERewardType _reward_type = ERewardType::GOLD;
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _value = 0;

	UPROPERTY(EditAnywhere, Category = "UI")
		UTexture2D* _icon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Description")
		FString _desc = "0";
public:
	FORCEINLINE const ERewardType GetRewardType() const { return _reward_type; }
	FORCEINLINE const int32 GetValue() const { return _value; }
	FORCEINLINE UTexture2D* GetIcon() { return _icon; }
};

USTRUCT(BlueprintType)
struct FDataSPEC : public FTableRowBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, Category = "General")
		EPowerType _power_type = EPowerType::SPEC01;
	UPROPERTY(EditAnywhere, Category = "General")
		ESPECAttackType _spec_attack_type = ESPECAttackType::NO;
	UPROPERTY(EditAnywhere, Category = "General")
		ESPECTier _spec_tier = ESPECTier::TIER_1;

	UPROPERTY(EditAnywhere, Category = "Only_Tier5")
		EPowerType _power_type_sub = EPowerType::SPEC01;
	//5티어 특성을 찍기위한 하위특성의 코드입니다. 5티어만 작성합니다
	UPROPERTY(EditAnywhere, Category = "Only_Tier5")
		FString _code_spec_need_1 = "Only_Tier5";
	UPROPERTY(EditAnywhere, Category = "Only_Tier5")
		FString _code_spec_need_2 = "Only_Tier5";

	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_1 = 0;
	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_2 = 0;
	UPROPERTY(EditAnywhere, Category = "Value")
		int32 _value_3 = 0;

	UPROPERTY(EditAnywhere, Category = "Description")
		FString _desc = "0";
public:
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE const EPowerType GetPowerType() const { return _power_type; }
	FORCEINLINE const ESPECAttackType GetSPECAttackType() const { return _spec_attack_type; }
	FORCEINLINE const ESPECTier GetSPECTier() const { return _spec_tier; }
	FORCEINLINE const EPowerType GetPowerTypeSub() const { return _power_type_sub; }
	FORCEINLINE const FString& GetCodeSPECNeed1() const { return _code_spec_need_1; }
	FORCEINLINE const FString& GetCodeSPECNeed2() const { return _code_spec_need_2; }
	FORCEINLINE const int32 GetValue1() const { return _value_1; }
	FORCEINLINE const int32 GetValue2() const { return _value_2; }
	FORCEINLINE const int32 GetValue3() const { return _value_3; }
};
#pragma endregion

USTRUCT()
struct FInfoReward
{
	GENERATED_BODY()

public:
	UPROPERTY()
		ERewardType reward_type = ERewardType::GOLD;
	UPROPERTY()
		int32 value = 0;
	UPROPERTY()
		FString value_str = "0";

	UPROPERTY()
		UTexture2D* icon = nullptr;

public:
	//보상매니저에서 해당객체가 풀인 할때 호출
	void InitInfoReward()
	{

	}
};

USTRUCT()
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

public:
	void InitInfoWave()
	{
		//reward_select = ERewardType::NO;
	}
};

USTRUCT()
struct FInfoPlayer
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 gold = 0;//소지금
	UPROPERTY()
		TSet<FString> code_obtain_spec;//세계에서 얻은 특성코드들

	//웨이브클리어시 등장하는 랜덤보상의 개수
	UPROPERTY()
		uint8 reward_random_count = 0;

public:
	//세계에 진입할 때 호출
	void InitInfoPlayer()
	{
		gold = 0;
		code_obtain_spec.Empty(10);

		reward_random_count = 0;
	}
};

USTRUCT()
struct FInfoUnit
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EUnitClassType unit_type = EUnitClassType::HERO;
	//T : 피격을 받을 수 있는 상태입니다
	UPROPERTY()
		bool is_hit_valid = true;

	UPROPERTY()
		TArray<int64> gid_bfs;
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
		int32 dmg_base_by_bf = 0;

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
		FVector look_loc = FVector::ZeroVector;

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
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base + dmg_base_by_bf; }
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
struct FInfoCPAN
{
	GENERATED_BODY()

public:
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
		int32 dmg_base_by_bf = 0;

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
		int32 sk_cooldown_tick_max_base = 0;

	UPROPERTY()
		float anim_rate_base = 0.f;

	UPROPERTY()
		UAnimMontage* anim_attack_basic = nullptr;
	UPROPERTY()
		UAnimMontage* anim_attack_sk = nullptr;
public:
	FORCEINLINE const int32 GetSTRTotal() const { return str_base; }
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base + dmg_base_by_bf; }
	FORCEINLINE const int32 GetASTotal() const { return as_base; }
	FORCEINLINE const int32 GetSKAPTotal() const { return sk_ap_base; }
	FORCEINLINE const int32 GetCDTickMaxTotal() const { return sk_cooldown_tick_max_base; }

	FORCEINLINE const int32 GetAttackBasicDMG() const { return (float)GetSTRTotal() * (GetDMGTotal() * 0.01f); }
	FORCEINLINE const int32 GetASTotalDelay() const { return (60.f / float(GetASTotal())) * 60.f; }

	FORCEINLINE const float GetCDRate() const { return (float)sk_cooldown_tick / (float)GetCDTickMaxTotal(); }
};

USTRUCT()
struct FInfoMS
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		EAttackSkillStatus atk_sk_status = EAttackSkillStatus::COOLDOWN;
	UPROPERTY()
		AHD_Monster* target = nullptr;

	UPROPERTY()
		FString code_proj = "0";

	UPROPERTY()
		int32 int_base = 0;
	UPROPERTY()
		int32 mp_base = 100;

	FDataSkill* sk_data = nullptr;
	UPROPERTY()
		int32 sk_cooldown_tick = 0;
	UPROPERTY()
		int32 sk_cooldown_tick_max_base = 0;

public:
	FORCEINLINE const int32 GetINTTotal() const { return int_base; }
	FORCEINLINE const int32 GetMPTotal() const { return mp_base; }
	FORCEINLINE const int32 GetCDTickMaxTotal() const { return sk_cooldown_tick_max_base; }

	FORCEINLINE const float GetCDRate() const { return (float)sk_cooldown_tick / (float)GetCDTickMaxTotal(); }
};


USTRUCT()
struct FInfoMonster
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 gid = 0;
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
		int32 dmg_base_by_bf = 0;

	UPROPERTY()
		int32 as_base = 0;
	UPROPERTY()
		int32 as_delay = 0;
	UPROPERTY()
		int32 move_speed = 0;

	//0미만으로 떨어지면 이동이 불가능합니다
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
	FORCEINLINE const int32 GetDMGTotal() const { return dmg_base + dmg_base_by_bf; }
	FORCEINLINE const int32 GetASTotal() const { return as_base; }

	FORCEINLINE const float GetHPRate() const { return (float)hp / (float)hp_max; }
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
		int64 gid = 0;
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
struct FInfoBuff
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 gid = 0;
	UPROPERTY()
		int32 id = 0;

	UPROPERTY()
		EBuffPhase bf_phase = EBuffPhase::IMMEDIATELY;
	UPROPERTY()
		EBuffTimer bf_timer = EBuffTimer::TIMER;
	UPROPERTY()
		EBuffOverlap bf_overlap = EBuffOverlap::NEW;
	UPROPERTY()
		FString unique = "0";

	UPROPERTY()
		AHD_Unit* caster = nullptr;
	UPROPERTY()
		AHD_Unit* casted = nullptr;

	UPROPERTY()
		int32 value_1 = 0;
	UPROPERTY()
		int32 value_2 = 0;
	UPROPERTY()
		int32 value_3 = 0;

	//버프타이머가 무엇인지에 따라 역할이 달라집니다
	//버프타이머가 타이머라면 남은틱, 카운트라면 남은횟수 등 달라집니다 한번에 여기서 관리합니다
	UPROPERTY()
		int32 life = 0;
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