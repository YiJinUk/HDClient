// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_PC.h"
#include "UI/HD_UI_Main.h"

void AHD_PC::PCPostInit()
{
	PCBPPostInit();

	_ui_main = PCBPCreateWidgetMain();
}