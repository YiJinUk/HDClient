// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Main.generated.h"

class UWidgetSwitcher;
class UHD_UI_Home;
class UHD_UI_World;
/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Main : public UHD_UI_Master
{
	GENERATED_BODY()
	
#pragma region Init
protected:
	//virtual void NativeConstruct() override;
public:
	void UIMainPostInit();
private:
	/*
	* index 0 : home
	* index 1 : world
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_Home* _ui_home = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UHD_UI_World* _ui_world = nullptr;
#pragma endregion

public:
	void UIMainWorldStart();
};
