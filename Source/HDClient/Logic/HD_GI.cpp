// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/HD_GI.h"

UHD_GI::UHD_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Game.HDDT_Game"));
	if (DT_GAME.Succeeded()) { _dt_game = DT_GAME.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WAVE(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Wave.HDDT_Wave"));
	if (DT_WAVE.Succeeded()) { _dt_wave = DT_WAVE.Object; }
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WEAPON(TEXT("/Game/_HDClient/ReadOnly/Data/HDDT_Weapon.HDDT_Weapon"));
	if (DT_WEAPON.Succeeded()) { _dt_weapon = DT_WEAPON.Object; }
}