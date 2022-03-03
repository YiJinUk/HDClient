// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Home/HD_UI_Home.h"
//#include "Logic/HD_GM.h"
#include "Logic/HD_PC.h"

#include "Components/Button.h"

void UHD_UI_Home::NativeConstruct()
{
	Super::NativeConstruct();

	_world_start->OnClicked.AddDynamic(this, &UHD_UI_Home::ClickedWorldStart);
}
void UHD_UI_Home::HomePostInit()
{
	//_gm = GetWorld()->GetAuthGameMode<AHD_GM>();
	_pc = Cast<AHD_PC>(GetOwningPlayer());
}
void UHD_UI_Home::ClickedWorldStart()
{
	_pc->PCWorldStart();
}