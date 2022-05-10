// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/Select/HD_UI_Info_Select.h"
#include "HD_UI_Info_Select_Slot.h"
#include "Logic/HD_GM.h"
#include "Logic/Manager/HD_Manager_Power.h"

#include "Components/WrapBox.h"

void UHD_UI_Info_Select::InfoSelectPostInit()
{
	_gm = GetWorld()->GetAuthGameMode<AHD_GM>();

	/*3개의 슬롯을 생성합니다*/
	for (int32 i = 0; i < 3; ++i)
	{
		UHD_UI_Info_Select_Slot* w_slot = CreateWidgetSlot();
		_slots.Add(w_slot);
	}
}
void UHD_UI_Info_Select::InfoSelectInit()
{
	/*
	* 선택보상을 보여줍니다
	* 선택보상의 종류는 Reward매니저에서 이미 결정되었기 때문에 값만 불러와 표시합니다
	*/
}

void UHD_UI_Info_Select::UHD_UI_Info_Select::InfoSelectVisibleSPEC()
{
	//ClearSlotBox();

	//const TArray<FString>& arr_code_reward_spec = _gm->GetManagerPower()->GetCodesSPECReward();

	//UHD_UI_Info_Select_Slot* w_slot = nullptr;
	//for (int32 i = 0; i < arr_code_reward_spec.Num(); ++i)
	//{
	//	const FString& str_code_reward_spec = arr_code_reward_spec[i];
	//	w_slot = _slots[i];
	//	w_slot->SelectSlotInit(ERewardType::SPEC01, str_code_reward_spec);
	//	_slot_box->AddChild(w_slot);
	//}
}

void UHD_UI_Info_Select::ClearSlotBox()
{
	UHD_UI_Info_Select_Slot* w_slot = nullptr;
	for (UWidget* w_child : _slot_box->GetAllChildren())
	{
		w_slot = Cast<UHD_UI_Info_Select_Slot>(w_child);
		_slots.Add(w_slot);
	}
}