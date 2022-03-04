// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Home.generated.h"

class AHD_GM;
class AHD_PC;
class UButton;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Home : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
protected:
	virtual void NativeConstruct() override;
public:
	void HomePostInit();
private:
	//UPROPERTY()
		//AHD_GM* _gm = nullptr;
	UPROPERTY()
		AHD_PC* _pc = nullptr;

	UPROPERTY(Meta = (BindWidget), Transient)
		UButton* _world_start = nullptr;
#pragma endregion

private:
	UFUNCTION()
		void ClickedWorldStart();
};
