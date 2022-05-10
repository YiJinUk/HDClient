// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/HD_SharedStruct.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_Info_Select_Slot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_Info_Select_Slot : public UHD_UI_Master
{
	GENERATED_BODY()
#pragma region Init
public:
	void SelectSlotInit(const ERewardType e_reward_type, const FString& str_code);
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _text = nullptr;
	UPROPERTY()
		bool _is_selected = false;
#pragma endregion

};
