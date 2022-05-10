// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/Select/HD_UI_Info_Select_Slot.h"

#include "Components/TextBlock.h"

void UHD_UI_Info_Select_Slot::SelectSlotInit(const ERewardType e_reward_type, const FString& str_code)
{
	_is_selected = false;

	switch (e_reward_type)
	{
	case ERewardType::SPEC01:
		_text->SetText(FText::FromString(str_code));
		break;
	default:
		break;
	}
}