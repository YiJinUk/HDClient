// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Power.generated.h"

class UHD_GI;
class AHD_GM;

/**
 * 특성매니저 입니다
 * 상위특성이 나오기 위한 룰은 여기서 정의합니다
 * 1~3 티어 : 하위특성을 1개이상 찍었으면 해당티어의 특성이 열립니다
 * 5 티어(듀오) : 힘이 다른 2개의 특성을 필요로합니다. 필요로하는 특성은 3티어와 1티어를 필요로하며 이것은 5티어의 특성마다 다릅니다
 */

USTRUCT()
struct FInfoSPECCode
{
	GENERATED_BODY()

public:
	UPROPERTY()
		ESPECTier tier = ESPECTier::TIER_0;

	UPROPERTY()
		FString code = "0";

	UPROPERTY()
		FString code_spec_need_1 = "0";
	UPROPERTY()
		FString code_spec_need_2 = "0";
	UPROPERTY()
		bool can_active = false;
public:
	void InitSPECTier5()
	{
		can_active = false;
	}
};

/*
* 5티어 전용 구조체입니다
* 5티어는 각 특성끼리 얽혀있기 때문에 유지보수를 위해 따로 관리합니다
*/
USTRUCT()
struct FInfoSPECTier5
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		FString code_spec_need_1 = "0";
	UPROPERTY()
		FString code_spec_need_2 = "0";
public:
	FORCEINLINE bool operator==(const FString& other_code) const
	{
		return code == other_code;
	}
	FORCEINLINE bool operator==(const FInfoSPECTier5& other) const
	{
		return code == other.code;
	}
};

USTRUCT()
struct FInfoPower
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EPowerType power_type = EPowerType::SPEC01;

	

	/*보상으로 받을 수 있는 특성 코드입니다*/
	UPROPERTY()
		TArray<FString> tier_1_reward_code;
	UPROPERTY()
		TArray<FString> tier_2_reward_code;
	UPROPERTY()
		TArray<FString> tier_3_reward_code;

	/*보상으로 받을 수 있는 특성 코드의 최대갯수 입니다*/
	UPROPERTY()
		uint8 tier_1_count_max = 0;
	UPROPERTY()
		uint8 tier_2_count_max = 0;
	UPROPERTY()
		uint8 tier_3_count_max = 0;
	UPROPERTY()
		uint8 tier_5_count_max = 0;

	/*5티어는 다른 특성과 겹치는 특성이 있기 때문에 따로 관리합니다*/
	//TArray<FInfoSPECTier5*> tier_5_info;






	/*보상으로 나올 3가지 특성코드 입니다*/
	UPROPERTY()
		TArray<FString> code_reward_spec;

	//특성을 획득할 때 해당티어까지 특성을 획득할 수 있습니다. 티어0,티어5로 설정될 수 없습니다.
	UPROPERTY()
		ESPECTier spec_tier_reward = ESPECTier::TIER_1;

	/*
	* 플레이중 획득한 특성의 코드입니다
	* key : 특성들의 티어
	* value : 해당 티어의 특성코드들
	*/
	TMap<ESPECTier, TArray<FString>> codes_spec_own;

	/*
	* 아직 획득하지 못한 특성의 코드입니다
	* key : 특성들의 티어
	* value : 해당 티어의 특성코드들
	*/
	TMap<ESPECTier, TArray<FString>> codes_spec_not_own;

public:
	void InitPower()
	{
		tier_1_reward_code.Empty();
		tier_2_reward_code.Empty();
		tier_3_reward_code.Empty();
		//tier_5_reward_code.Empty();
		tier_1_count_max = 0;
		tier_2_count_max = 0;
		tier_3_count_max = 0;
		//tier_5_count_max = 0;
	}
};

USTRUCT()
struct FInfoPower01 : public FInfoPower
{
	GENERATED_BODY()

public:
	int i_a = 0;
	/*UPROPERTY()
		FInfoSPECGeneral _spec_general;*/
public:
	void InitSPEC01()
	{

	}
};

USTRUCT()
struct FInfoPower02 : public FInfoPower
{
	GENERATED_BODY()

public:
	/*UPROPERTY()
		FInfoSPECGeneral _spec_general;*/
public:
	void InitSPEC02()
	{

	}
};

USTRUCT()
struct FInfoPower03 : public FInfoPower
{
	GENERATED_BODY()

public:
	/*UPROPERTY()
		FInfoSPECGeneral _spec_general;*/
public:
	void InitSPEC03()
	{

	}
};

UCLASS()
class HDCLIENT_API AHD_Manager_Power : public AHD_Manager_Master
{
	GENERATED_BODY()

		uint32 GetTypeHash(const FInfoSPECTier5& myStruct);
#pragma region Init
public:
	void PowerPostInit(UHD_GI* gi, AHD_GM* gm);
	//세계에 진입했을 때 호출
	void PowerInit();
	//보상 특성을 계산해야할 때 호출
	void PowerCalcRewardSPECInit(const ERewardType e_reward_spec_type);

	void SPECAdd(const FString& str_code_spec, FInfoPlayer& s_info_player);
	void SPECRemove(const FString& str_code_spec, FInfoPlayer& s_info_player);
private:
	//PowerInit()에서 호출합니다
	void PowerInitInfoSPEC(FInfoPower& s_info_spec);

	//보상으로 등장할 특성을 계산합니다
	void PowerCalcRewardSPEC(FInfoPower& s_info_power);

	/*
	* 해당특성의 획득티어를 계산합니다
	* 각 티어별 코드와 코드최대갯수가 미리 계산되어있어야 합니다
	* 1티어부터 순차적으로 계산하고 5티어는 따로 계산합니다
	*/
	void PowerCalcInfoSPECTierReward(FInfoPower* s_info_spec, FInfoPlayer& s_info_player);

	FInfoPower* FindInfoSPEC(const EPowerType e_spec_type);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	/*각 특성정보를 모아놓았습니다*/
	UPROPERTY()
		TArray<FInfoPower> _info_specs;

	/*각 특성에 빠르게 접근할 수 있습니다. _info_specs와 같은 구조체입니다*/
	FInfoPower01* _info_spec_01 = nullptr;
	FInfoPower02* _info_spec_02 = nullptr;
	FInfoPower03* _info_spec_03 = nullptr;

	/*5티어 특성정보는 따로 관리합니다*/
	TArray<FInfoSPECTier5*> _info_specs_tier_5_disable;
	TArray<FInfoSPECTier5*> _info_specs_tier_5_enable;
	TArray<FInfoSPECTier5*> _info_specs_tier_5_own;
	UPROPERTY()
		TArray<FInfoSPECTier5> _info_specs_tier_5_origin;

	/*보상으로 획득할 수 있는 보상코드 입니다*/
	UPROPERTY()
		TArray<FString> _code_spec_reward;
#pragma endregion
};
