// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info.generated.h"

class UHD_UI_Main;
class UHD_UI_Info_Bottom;
class UHD_UI_Info_Top;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void UIInfoPostInit(UHD_UI_Main* ui_main);
private:
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Info_Bottom* _ui_info_bottom = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Info_Top* _ui_info_top = nullptr;
#pragma endregion
};
