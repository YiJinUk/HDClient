// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Animation/HD_AM.h"

void UHD_AM::AMPostInit(AHD_Unit* unit_owner)
{
	AMPostInitChild(unit_owner);
}
void UHD_AM::AMPostInitChild(AHD_Unit* unit_owner)
{
	//override;
}