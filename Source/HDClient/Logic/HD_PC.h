// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HD_PC.generated.h"

class UHD_UI_Main;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_PC : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void PCPostInit();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void PCBPPostInit();
	UFUNCTION(BlueprintImplementableEvent)
		UHD_UI_Main* PCBPCreateWidgetMain();
private:
#pragma endregion

#pragma region Widget
private:
	UPROPERTY()
		UHD_UI_Main* _ui_main = nullptr;
#pragma endregion
};