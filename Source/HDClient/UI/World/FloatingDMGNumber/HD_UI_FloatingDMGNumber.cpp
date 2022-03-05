// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/FloatingDMGNumber/HD_UI_FloatingDMGNumber.h"
#include "Logic/HD_PC.h"

#include "Components/TextBlock.h"

void UHD_UI_FloatingDMGNumber::NativeConstruct()
{
	Super::NativeConstruct();
	_pc = Cast<AHD_PC>(GetOwningPlayer());
}
void UHD_UI_FloatingDMGNumber::PlaySlot(const int32 i_number)
{
	_number->SetText(FText::AsNumber(i_number));
	PlayAnimation(_anim);
	GetWorld()->GetTimerManager().SetTimer(_timer_TimerAnimationFinished, this, &UHD_UI_FloatingDMGNumber::TimerAnimationFinished, 1.5f, false);
}

void UHD_UI_FloatingDMGNumber::TimerAnimationFinished()
{
	_pc->PoolInFloatingDMGNum(this);
	RemoveFromViewport();
}