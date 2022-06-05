// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Logic/Manager/HD_Manager_Master.h"
#include "HD_Manager_Power.generated.h"

class UHD_GI;
class AHD_GM;

/**
 * Ư���Ŵ��� �Դϴ�
 * ����Ư���� ������ ���� ���� ���⼭ �����մϴ�
 * 1~3 Ƽ�� : ����Ư���� 1���̻� ������� �ش�Ƽ���� Ư���� �����ϴ�
 * 5 Ƽ��(���) : ���� �ٸ� 2���� Ư���� �ʿ���մϴ�. �ʿ���ϴ� Ư���� 3Ƽ��� 1Ƽ� �ʿ���ϸ� �̰��� 5Ƽ���� Ư������ �ٸ��ϴ�
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
* 5Ƽ�� ���� ����ü�Դϴ�
* 5Ƽ��� �� Ư������ �����ֱ� ������ ���������� ���� ���� �����մϴ�
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

	

	/*�������� ���� �� �ִ� Ư�� �ڵ��Դϴ�*/
	UPROPERTY()
		TArray<FString> tier_1_reward_code;
	UPROPERTY()
		TArray<FString> tier_2_reward_code;
	UPROPERTY()
		TArray<FString> tier_3_reward_code;

	/*�������� ���� �� �ִ� Ư�� �ڵ��� �ִ밹�� �Դϴ�*/
	UPROPERTY()
		uint8 tier_1_count_max = 0;
	UPROPERTY()
		uint8 tier_2_count_max = 0;
	UPROPERTY()
		uint8 tier_3_count_max = 0;
	UPROPERTY()
		uint8 tier_5_count_max = 0;

	/*5Ƽ��� �ٸ� Ư���� ��ġ�� Ư���� �ֱ� ������ ���� �����մϴ�*/
	//TArray<FInfoSPECTier5*> tier_5_info;






	/*�������� ���� 3���� Ư���ڵ� �Դϴ�*/
	UPROPERTY()
		TArray<FString> code_reward_spec;

	//Ư���� ȹ���� �� �ش�Ƽ����� Ư���� ȹ���� �� �ֽ��ϴ�. Ƽ��0,Ƽ��5�� ������ �� �����ϴ�.
	UPROPERTY()
		ESPECTier spec_tier_reward = ESPECTier::TIER_1;

	/*
	* �÷����� ȹ���� Ư���� �ڵ��Դϴ�
	* key : Ư������ Ƽ��
	* value : �ش� Ƽ���� Ư���ڵ��
	*/
	TMap<ESPECTier, TArray<FString>> codes_spec_own;

	/*
	* ���� ȹ������ ���� Ư���� �ڵ��Դϴ�
	* key : Ư������ Ƽ��
	* value : �ش� Ƽ���� Ư���ڵ��
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
	//���迡 �������� �� ȣ��
	void PowerInit();
	//���� Ư���� ����ؾ��� �� ȣ��
	void PowerCalcRewardSPECInit(const ERewardType e_reward_spec_type);

	void SPECAdd(const FString& str_code_spec, FInfoPlayer& s_info_player);
	void SPECRemove(const FString& str_code_spec, FInfoPlayer& s_info_player);
private:
	//PowerInit()���� ȣ���մϴ�
	void PowerInitInfoSPEC(FInfoPower& s_info_spec);

	//�������� ������ Ư���� ����մϴ�
	void PowerCalcRewardSPEC(FInfoPower& s_info_power);

	/*
	* �ش�Ư���� ȹ��Ƽ� ����մϴ�
	* �� Ƽ� �ڵ�� �ڵ��ִ밹���� �̸� ���Ǿ��־�� �մϴ�
	* 1Ƽ����� ���������� ����ϰ� 5Ƽ��� ���� ����մϴ�
	*/
	void PowerCalcInfoSPECTierReward(FInfoPower* s_info_spec, FInfoPlayer& s_info_player);

	FInfoPower* FindInfoSPEC(const EPowerType e_spec_type);
private:
	UPROPERTY()
		UHD_GI* _gi = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	/*�� Ư�������� ��Ƴ��ҽ��ϴ�*/
	UPROPERTY()
		TArray<FInfoPower> _info_specs;

	/*�� Ư���� ������ ������ �� �ֽ��ϴ�. _info_specs�� ���� ����ü�Դϴ�*/
	FInfoPower01* _info_spec_01 = nullptr;
	FInfoPower02* _info_spec_02 = nullptr;
	FInfoPower03* _info_spec_03 = nullptr;

	/*5Ƽ�� Ư�������� ���� �����մϴ�*/
	TArray<FInfoSPECTier5*> _info_specs_tier_5_disable;
	TArray<FInfoSPECTier5*> _info_specs_tier_5_enable;
	TArray<FInfoSPECTier5*> _info_specs_tier_5_own;
	UPROPERTY()
		TArray<FInfoSPECTier5> _info_specs_tier_5_origin;

	/*�������� ȹ���� �� �ִ� �����ڵ� �Դϴ�*/
	UPROPERTY()
		TArray<FString> _code_spec_reward;
#pragma endregion
};
