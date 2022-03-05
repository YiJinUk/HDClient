// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_GameOver.generated.h"

class UButton;
class AHD_GM;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_GameOver : public UHD_UI_Master
{
	GENERATED_BODY()
	
#pragma region Init
public:
	void UIGameOverPostInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _return_to_home = nullptr;
	UPROPERTY()
		AHD_GM* _gm = nullptr;
#pragma endregion

private:
	UFUNCTION()
		void ClickedReturnToHome();
};
