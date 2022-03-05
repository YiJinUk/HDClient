// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Top.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info_Top : public UHD_UI_Master
{
	GENERATED_BODY()
	
public:
	void InfoTopInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _stage = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _wave = nullptr;

public:
	void InfoTopSetRound(const int32 i_round_stage, const int32 i_round_wave);
};
