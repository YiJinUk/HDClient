// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "Engine/GameInstance.h"
#include "HD_GI.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_GI : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UHD_GI();

private:
	UDataTable* _dt_game = nullptr;
	UDataTable* _dt_wave = nullptr;
	UDataTable* _dt_weapon = nullptr;
};
