// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HD_UI_Master.h"
#include "HD_UI_FloatingDMGNumber.generated.h"

class AHD_PC;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_UI_FloatingDMGNumber : public UHD_UI_Master
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
		void UIBPPostInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _number = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _anim = nullptr;
	UPROPERTY()
		AHD_PC* _pc = nullptr;

public:
	void PlaySlot(const int32 i_number);
private:
	FWidgetAnimationDynamicEvent AnimationEvent;
	UFUNCTION()
		void AnimFinished();

};
