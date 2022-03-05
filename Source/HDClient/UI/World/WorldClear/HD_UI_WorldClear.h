// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_WorldClear.generated.h"

class UButton;
class AHD_GM;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_WorldClear : public UHD_UI_Master
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void UIWorldClearPostInit();
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _clear_to_home = nullptr;
#pragma endregion

private:
	UFUNCTION()
		void ClickedClearToHome();
};
