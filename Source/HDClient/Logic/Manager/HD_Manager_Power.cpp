// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Power.h"
#include "Logic/HD_GI.h"
#include "Logic/HD_GM.h"

#include "Kismet/KismetMathLibrary.h"

uint32 AHD_Manager_Power::GetTypeHash(const FInfoSPECTier5& myStruct)
{
	return FCrc::MemCrc32(&myStruct, sizeof(FInfoSPECTier5));
}

void AHD_Manager_Power::PowerPostInit(UHD_GI* gi, AHD_GM* gm)
{
	_gi = gi;
	_gm = gm;

	/*�� Ư�������� �����մϴ�*/
	int32 i_index = 0;
	for (const EPowerType e_spec_type : _gi->GetDataGame()->GetSPECsActive())
	{
		switch (e_spec_type)
		{
		case EPowerType::SPEC01:
		{
			/*����ü�� �����մϴ�*/
			FInfoPower01 s_info_spec01;
			i_index = _info_specs.Add(s_info_spec01);
			_info_spec_01 = static_cast<FInfoPower01*>(&_info_specs[i_index]);

			/*������ ����ü�� Ư���ڵ带 �߰��մϴ�*/
			for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
			{
				TArray<FString>& arr_code_spec = _info_spec_01->codes_spec_not_own.FindOrAdd(s_data_spec->GetSPECTier());
				if (s_data_spec->GetPowerType() == e_spec_type)
				{
					/*���� Ư���̶�� �ڵ带 �߰��մϴ�*/
					arr_code_spec.AddUnique(s_data_spec->GetCode());
				}
			}
		}
			break;
		case EPowerType::SPEC02:
			//SPECInitInfoSPEC02();
			break;
		case EPowerType::SPEC03:
			//SPECInitInfoSPEC03();
			break;
		default:
			break;
		}
	}

	/*���Ư���� ���� �����մϴ�*/
	for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
	{
		//FInfoSPECTier5 s_info_spec_tier_5_1;
		if (s_data_spec->GetSPECTier() == ESPECTier::TIER_5 && !_info_specs_tier_5_origin.Contains(s_data_spec->GetCode()))
		{
			FInfoSPECTier5 s_info_spec_tier_5;
			s_info_spec_tier_5.code = s_data_spec->GetCode();
			s_info_spec_tier_5.code_spec_need_1 = s_data_spec->GetCodeSPECNeed1();
			s_info_spec_tier_5.code_spec_need_2 = s_data_spec->GetCodeSPECNeed2();
			_info_specs_tier_5_origin.AddUnique(s_info_spec_tier_5);
		}
	}
	for (int32 i = 0, i_len = _info_specs_tier_5_origin.Num(); i < i_len; ++i)
	{
		_info_specs_tier_5_disable.Add(&_info_specs_tier_5_origin[i]);
	}
	//FInfoPower* s_info_spec = nullptr;
	//for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
	//{
	//	if (s_data_spec->GetSPECTier() == ESPECTier::TIER_5)
	//	{
	//		FInfoSPECTier5 s_info_tier_5;
	//		s_info_tier_5.code = s_data_spec->GetCode();
	//		s_info_tier_5.code_spec_need_1 = s_data_spec->GetCodeSPECNeed1();
	//		s_info_tier_5.code_spec_need_2 = s_data_spec->GetCodeSPECNeed2();
	//		//i_index = _info_tier_5_origin.Add(s_info_tier_5);

	//		//s_info_spec = FindInfoSPEC(s_data_spec->GetPowerType());
	//		//s_info_spec->tier_5_info.Add(&_info_tier_5_origin[i_index]);
	//		//s_info_spec = FindInfoSPEC(s_data_spec->GetPowerTypeSub());
	//		//s_info_spec->tier_5_info.Add(&_info_tier_5_origin[i_index]);
	//	}
	//}
}
void AHD_Manager_Power::PowerInit()
{
	/*�� Ư������ �ʱ�ȭ�մϴ�*/
	for (FInfoPower& s_info_spec : _info_specs)
	{
		PowerInitInfoSPEC(s_info_spec);
		PowerCalcRewardSPEC(s_info_spec);
		switch (s_info_spec.power_type)
		{
		case EPowerType::SPEC01:			
			_info_spec_01->InitSPEC01();
		
		break;
		case EPowerType::SPEC02:
			_info_spec_02->InitSPEC02();
			break;
		case EPowerType::SPEC03:
			_info_spec_03->InitSPEC03();
			break;
		default:
			break;
		}
	}

	/*���Ư���� ���� �ʱ�ȭ�մϴ�*/
	_info_specs_tier_5_disable.Append(_info_specs_tier_5_own);
	_info_specs_tier_5_disable.Append(_info_specs_tier_5_enable);
	_info_specs_tier_5_own.Empty(5);
	_info_specs_tier_5_enable.Empty(5);
}
void AHD_Manager_Power::PowerInitInfoSPEC(FInfoPower& s_info_spec)
{
	//s_info_spec.InitPower();

	/*Ư���ڵ带 ȹ������ ���� �ڵ�迭�� ���� �ű�ϴ�*/
	s_info_spec.codes_spec_not_own.Append(s_info_spec.codes_spec_own);
	s_info_spec.codes_spec_own.Empty(5);

	/*Ư���� ȹ�氡��Ư��Ƽ� �ʱ�ȭ�մϴ�*/
	s_info_spec.spec_tier_reward = ESPECTier::TIER_1;
	

	//for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
	//{
	//	if (s_data_spec->GetPowerType() == EPowerType::SPEC01)
	//	{
	//		switch (s_data_spec->GetSPECTier())
	//		{
	//		case ESPECTier::TIER_1:
	//			s_info_spec.tier_1_reward_code.Add(s_data_spec->GetCode());
	//			break;
	//		case ESPECTier::TIER_2:
	//			s_info_spec.tier_2_reward_code.Add(s_data_spec->GetCode());
	//			break;
	//		case ESPECTier::TIER_3:
	//			s_info_spec.tier_3_reward_code.Add(s_data_spec->GetCode());
	//			break;
	//		default:
	//			break;
	//		}

	//	}
	//}

	//for (FInfoSPECTier5* s_info_spec_tier_5 : s_info_spec.tier_5_info)
	//{
	//	s_info_spec_tier_5->can_active = false;
	//}
}
void AHD_Manager_Power::PowerCalcRewardSPEC(FInfoPower& s_info_power)
{
	/*
	* ȹ������ ���� Ư����, �������� ������ Ư���ڵ带 �������� N�� �����ɴϴ�
	* ��������� ���� ������ �ִ� Ư���� ���� ���� Ƽ�������� �ڵ��Դϴ�.
	* �ּ� Ƽ��1 ~ �ִ� Ƽ��3���� �Դϴ�.
	* ex)Ƽ��0�� Ư���� ������ �־ �ּ� Ƽ��� 1�̱� ������ Ƽ��1������ Ư���� �����ϸ�
	* Ƽ��4,5�� Ư���� ������ �־ �ִ� Ƽ��3�� Ư���� �����մϴ�
	*/

	//ȹ������ ���� ��� Ư���ڵ带 �����ϴ� �迭�Դϴ�
	TArray<FString> arr_all_code_spec_not_own;

	//ȹ������ ���� ��� Ư���� �ݺ��ؼ� �����ɴϴ�
	for (auto& map_code_spec_not_own : s_info_power.codes_spec_not_own)
	{
		//Ư���� ������ �� �ִ� Ƽ������ Ȯ���մϴ�
		if (map_code_spec_not_own.Key <= s_info_power.spec_tier_reward)
		{
			//������ �� �ִ� Ƽ���Դϴ�
			arr_all_code_spec_not_own.Append(map_code_spec_not_own.Value);
		}
	}

	/*��� Ư���ڵ忡�� N����ŭ �����ϰ� �������� �����ڵ�迭�� �߰��մϴ�.����3���Դϴ�*/
	s_info_power.code_reward_spec.Empty(3);
	int32 i_index = 0;
	for (int32 i = 0; i < 3; ++i)
	{
		i_index = _gi->GetRandomByInt(0, arr_all_code_spec_not_own.Num() - 1);
		s_info_power.code_reward_spec.Add(arr_all_code_spec_not_own[i_index]);

		//�����ڵ�迭�� �߰������� ������ �ڵ尡 �ߺ����� ������ �ʰ� ��� Ư���ڵ�迭���� �����մϴ�
		arr_all_code_spec_not_own.RemoveAtSwap(i_index);
	}
}
void AHD_Manager_Power::PowerCalcRewardSPECInit(const ERewardType e_reward_spec_type)
{
	FInfoPower* s_info_spec = nullptr;
	switch (e_reward_spec_type)
	{
	case ERewardType::SPEC01:
		s_info_spec = FindInfoSPEC(EPowerType::SPEC01);
		break;
	case ERewardType::SPEC02:
		s_info_spec = FindInfoSPEC(EPowerType::SPEC02);
		break;
	case ERewardType::SPEC03:
		s_info_spec = FindInfoSPEC(EPowerType::SPEC03);
		break;
	default:
		break;
	}

	/*Ư�� ����Ƽ� �°� ȹ���� �� �ִ� ��� Ư���ڵ带 �迭�� ������ �����ϰ� �̽��ϴ�*/
	TArray<FString> arr_code_reward_spec;
	switch (s_info_spec->spec_tier_reward)
	{
	case ESPECTier::TIER_1:
		arr_code_reward_spec.Append(s_info_spec->tier_1_reward_code);
		break;
	case ESPECTier::TIER_2:
		arr_code_reward_spec.Append(s_info_spec->tier_1_reward_code);
		break;
	case ESPECTier::TIER_3:
	case ESPECTier::TIER_MAX:
		arr_code_reward_spec.Append(s_info_spec->tier_1_reward_code);
		break;
	default:
		break;
	}
	//for (FInfoSPECTier5* s_info_tier_5 : s_info_spec->tier_5_info)
	//{
	//	if (s_info_tier_5->can_active)
	//		arr_code_reward_spec.Add(s_info_tier_5->code);
	//}

	//3���� �����ϰ� �̽��ϴ�
	_code_spec_reward.Empty(3);
	for (int32 i = 0; i < 3; ++i)
	{
		if (arr_code_reward_spec.Num() <= 0)
			break;
		_code_spec_reward.Add(arr_code_reward_spec[UKismetMathLibrary::RandomInteger(arr_code_reward_spec.Num())]);
	}
}

void AHD_Manager_Power::PowerCalcInfoSPECTierReward(FInfoPower* s_info_spec, FInfoPlayer& s_info_player)
{
	//�ش�Ư������ ������ ���� �� �ִ� Ƽ� ����մϴ�
	if (s_info_spec->tier_1_reward_code.Num() == s_info_spec->tier_1_count_max)
	{
		s_info_spec->spec_tier_reward = ESPECTier::TIER_1;
	}
	else if (s_info_spec->tier_2_reward_code.Num() == s_info_spec->tier_2_count_max)
	{
		s_info_spec->spec_tier_reward = ESPECTier::TIER_2;
	}
	else if (s_info_spec->tier_3_reward_code.Num() == s_info_spec->tier_3_count_max)
	{
		s_info_spec->spec_tier_reward = ESPECTier::TIER_3;
	}
	else
	{
		s_info_spec->spec_tier_reward = ESPECTier::TIER_MAX;
	}

	////5Ƽ��(���)�� ���� ����մϴ�
	//for (FInfoSPECTier5* s_info_tier_5 : s_info_spec->tier_5_info)
	//{
	//	if (s_info_player.code_obtain_spec.Find(s_info_tier_5->code_spec_need_1) && s_info_player.code_obtain_spec.Find(s_info_tier_5->code_spec_need_2))
	//	{
	//		s_info_tier_5->can_active = true;
	//	}
	//}
}

void AHD_Manager_Power::SPECAdd(const FString& str_code_spec, FInfoPlayer& s_info_player)
{

}
void AHD_Manager_Power::SPECRemove(const FString& str_code_spec, FInfoPlayer& s_info_player)
{

}

FInfoPower* AHD_Manager_Power::FindInfoSPEC(const EPowerType e_spec_type)
{
	for (FInfoPower& s_info_spec : _info_specs)
	{
		if (s_info_spec.power_type == e_spec_type)
		{
			//found
			return &s_info_spec;
		}
	}
	return nullptr;
}