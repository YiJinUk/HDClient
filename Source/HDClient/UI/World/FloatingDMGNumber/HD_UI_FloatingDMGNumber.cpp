// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/FloatingDMGNumber/HD_UI_FloatingDMGNumber.h"
#include "Logic/HD_PC.h"
#include "Logic/HD_FunctionLibrary.h"

#include "Components/TextBlock.h"

void UHD_UI_FloatingDMGNumber::UIBPPostInit()
{
	_pc = Cast<AHD_PC>(GetOwningPlayer());
	AnimationEvent.BindDynamic(this, &UHD_UI_FloatingDMGNumber::AnimFinished);

	BindToAnimationFinished(_anim, AnimationEvent);
}
void UHD_UI_FloatingDMGNumber::PlaySlot(const int32 i_number)
{
	_number->SetText(FText::AsNumber(i_number));
	PlayAnimation(_anim);
}

void UHD_UI_FloatingDMGNumber::AnimFinished()
{
	_pc->PoolInFloatingDMGNum(this);
	RemoveFromViewport();
}