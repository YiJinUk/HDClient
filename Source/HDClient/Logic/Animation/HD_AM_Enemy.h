// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Animation/HD_AM.h"
#include "HD_AM_Enemy.generated.h"

class AHD_Enemy;

/**
 * 
 */
UCLASS()
class HDCLIENT_API UHD_AM_Enemy : public UHD_AM
{
	GENERATED_BODY()
public:
	void AMPostInitChild(AHD_Unit* unit_owner) override;
private:
	UFUNCTION()
		void OnAnimationFinished(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY()
		AHD_Enemy* _owner = nullptr;

public:
	UFUNCTION(BlueprintCallable)
		void AttackBasicNotify();
};
