// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/HD_Manager_Power.h"
#include "Logic/HD_GI.h"
#include "Logic/HD_GM.h"

#include "Kismet/KismetMathLibrary.h"

void AHD_Manager_Power::PowerPostInit(UHD_GI* gi, AHD_GM* gm)
{
	_gi = gi;
	_gm = gm;

	/*각 특성정보를 생성합니다*/
	int32 i_index = 0;
	for (const EPowerType e_spec_type : _gi->GetDataGame()->GetSPECsActive())
	{
		switch (e_spec_type)
		{
		case EPowerType::SPEC01:
		{
			FInfoPower01 s_info_spec01;
			i_index = _info_specs.Add(s_info_spec01);
			_info_spec_01 = static_cast<FInfoPower01*>(&_info_specs[i_index]);
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

	/*듀오특성은 따로 생성합니다*/
	FInfoPower* s_info_spec = nullptr;
	for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
	{
		if (s_data_spec->GetSPECTier() == ESPECTier::TIER_5)
		{
			FInfoSPECTier5 s_info_tier_5;
			s_info_tier_5.code = s_data_spec->GetCode();
			s_info_tier_5.code_spec_need_1 = s_data_spec->GetCodeSPECNeed1();
			s_info_tier_5.code_spec_need_2 = s_data_spec->GetCodeSPECNeed2();
			i_index = _info_tier_5_origin.Add(s_info_tier_5);

			s_info_spec = FindInfoSPEC(s_data_spec->GetPowerType());
			s_info_spec->tier_5_info.Add(&_info_tier_5_origin[i_index]);
			s_info_spec = FindInfoSPEC(s_data_spec->GetPowerTypeSub());
			s_info_spec->tier_5_info.Add(&_info_tier_5_origin[i_index]);
		}
	}
}
void AHD_Manager_Power::PowerInit()
{
	for (FInfoPower& s_info_spec : _info_specs)
	{
		PowerInitInfoSPEC(s_info_spec);
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
}
void AHD_Manager_Power::PowerInitInfoSPEC(FInfoPower& s_info_spec)
{
	s_info_spec.InitPower();
	for (const FDataSPEC* s_data_spec : _gi->GetDataSPECs())
	{
		if (s_data_spec->GetPowerType() == EPowerType::SPEC01)
		{
			switch (s_data_spec->GetSPECTier())
			{
			case ESPECTier::TIER_1:
				s_info_spec.tier_1_reward_code.Add(s_data_spec->GetCode());
				break;
			case ESPECTier::TIER_2:
				s_info_spec.tier_2_reward_code.Add(s_data_spec->GetCode());
				break;
			case ESPECTier::TIER_3:
				s_info_spec.tier_3_reward_code.Add(s_data_spec->GetCode());
				break;
			default:
				break;
			}

		}
	}

	for (FInfoSPECTier5* s_info_spec_tier_5 : s_info_spec.tier_5_info)
	{
		s_info_spec_tier_5->can_active = false;
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

	/*특성 보상티어에 맞게 획득할 수 있는 모든 특성코드를 배열에 저장후 랜덤하게 뽑습니다*/
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
	for (FInfoSPECTier5* s_info_tier_5 : s_info_spec->tier_5_info)
	{
		if (s_info_tier_5->can_active)
			arr_code_reward_spec.Add(s_info_tier_5->code);
	}

	//3개만 랜덤하게 뽑습니다
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
	//해당특성으로 보상을 받을 수 있는 티어를 계산합니다
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

	//5티어(듀오)는 따로 계산합니다
	for (FInfoSPECTier5* s_info_tier_5 : s_info_spec->tier_5_info)
	{
		if (s_info_player.code_obtain_spec.Find(s_info_tier_5->code_spec_need_1) && s_info_player.code_obtain_spec.Find(s_info_tier_5->code_spec_need_2))
		{
			s_info_tier_5->can_active = true;
		}
	}
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