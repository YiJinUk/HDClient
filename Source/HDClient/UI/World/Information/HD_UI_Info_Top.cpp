// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/Information/HD_UI_Info_Top.h"

#include "Components/TextBlock.h"

void UHD_UI_Info_Top::InfoTopInit()
{
	_stage->SetText(FText::AsNumber(1));
	_wave->SetText(FText::AsNumber(1));
}
void UHD_UI_Info_Top::InfoTopSetRound(const int32 i_round_stage, const int32 i_round_wave)
{
	_stage->SetText(FText::AsNumber(i_round_stage));
	_wave->SetText(FText::AsNumber(i_round_wave));
}