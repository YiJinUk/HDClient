// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/HD_Object.h"
#include "HD_Portal.generated.h"

class AHD_GM;
class UHD_UI_HeadUp_Portal;

/**
 * 
 */
UCLASS()
class HDCLIENT_API AHD_Portal : public AHD_Object
{
	GENERATED_BODY()
	
#pragma region Init
public:
	AHD_Portal();
	void PortalPostInit();
	void PortalInit(const ERewardType e_reward_type, const FVector& v_loc_spawn);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* _ui_headup = nullptr;
private:
	UPROPERTY()
		AHD_GM* _gm = nullptr;
	UPROPERTY()
		UHD_UI_HeadUp_Portal* _ui_headup_portal = nullptr;

	UPROPERTY()
		ERewardType _reward_type = ERewardType::NO;
#pragma endregion

public:
	UFUNCTION(BlueprintCallable)
		void ClickedPortal();

};
