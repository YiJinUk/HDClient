// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_World.generated.h"

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_World : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void WorldPostInit();
#pragma endregion
};
