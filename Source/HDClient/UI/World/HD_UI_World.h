// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_World.generated.h"

class UHD_UI_Info_Bottom;
class UHD_UI_Main;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_World : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void WorldPostInit(UHD_UI_Main* ui_main);
private:
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Info_Bottom* _ui_info_bottom = nullptr;
#pragma endregion

};
